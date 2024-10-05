#include "invoker.hpp"
#include "command/command.hpp"
#include <cstddef>
#include <memory>
#include <mutex>
#include <thread>


namespace engine {
    
bool Queue::tryPop(std::unique_ptr<command::Icommand> &_command)
{
    std::lock_guard lc{m};

    if(queue.empty()) {
        return false;
    } 

    _command = std::move(queue.front());
    queue.pop();

    return true;
}

std::unique_ptr<command::Icommand> Queue::pop()
{
    std::unique_lock lc{m};

    cv.wait(lc, [this](){ return !queue.empty();});

    auto res = std::move(queue.front());
    queue.pop();
     
    return res;
}


bool Queue::tryPush(std::unique_ptr<command::Icommand> _command)
{
    std::lock_guard lc{m};

    queue.push(std::move(_command));

    cv.notify_one();

    return true;
}

void Queue::push(std::unique_ptr<command::Icommand> _command)
{
    tryPush(std::move(_command));
}

std::size_t Queue::size() const noexcept
{
    std::lock_guard lc{m};
    return  queue.size();
}

Invoker::BehaviourCounted::BehaviourCounted(uint64_t _times) :
    times{ _times },
    cnt{ 0 }
{ }

Invoker::Invoker(const std::shared_ptr<Queue> &_queue, std::unique_ptr<Behaviour> _behaviour) :
    queue{ _queue },
    curBehaviour{_behaviour ? std::move(_behaviour) : std::make_unique<BehaviourCommon>()}
{

}

void Invoker::loop()
{
    while(!needStop.test()) {
        checkBehaviour();
        if( curBehaviour->execute(*queue) ) {
            needStop.test_and_set();
        }
    }
    stopped.test_and_set();
    stopped.notify_all();
}

void Invoker::checkBehaviour()
{
    std::lock_guard lc(m);

    if(nextbehaviour) {
        std::swap(curBehaviour, nextbehaviour);
        nextbehaviour.reset();
    }
}

void Invoker::start()
{
    std::thread(&Invoker::loop, this).detach();
}

void Invoker::wait()
{
    stopped.wait(false);
}

void Invoker::stop()
{
    needStop.test_and_set();
    needStop.notify_all();
}

void Invoker::hardStop()
{
    nextbehaviour = std::make_unique<BehaviourHardStop>();
}

void Invoker::softStop()
{
    nextbehaviour = std::make_unique<BehaviourSoftStop>();
}

bool Invoker::BehaviourCommon::execute(Queue &_queue)
{
    std::unique_ptr<command::Icommand> command;
    if(auto res = _queue.tryPop(command); res != false ) {
        command->execute();
    }
    return false;
}

bool Invoker::BehaviourHardStop::execute(Queue &)
{
    return true;
}

bool Invoker::BehaviourSoftStop::execute(Queue &_queue)
{
    std::unique_ptr<command::Icommand> command;
    if(auto res = _queue.tryPop(command); res != false ) {
        command->execute();
    } else {
        return true;
    }
    return false;
}

bool Invoker::BehaviourCounted::execute(Queue &_queue)
{
    cnt++;
    std::unique_ptr<command::Icommand> command  = _queue.pop();    
    command->execute();
    return cnt == times ? true : false;
}

}