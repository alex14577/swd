#include "worker.hpp"
#include <atomic>
#include <exception>
#include <iostream>
#include <thread>


namespace cms::worker {

Worker::Worker(const module::Plugin &_plugin, const command::QueuePtr &_queueIn, const std::vector<command::QueuePtr> &_queuesOut) noexcept : 
    plugin{ _plugin },
    queueIn{ _queueIn },
    cmdFactory{ plugin, this, _queuesOut}
{ 
}

void Worker::start()
{
    thread = std::thread(&Worker::runner, this);
}

void Worker::runner()
{
    pthread_setname_np(pthread_self(), name().c_str());

    while(1) {
        if (needStop.test()) {
            break;
        }

        try {
            auto message = queueIn->pop();
            auto cmd = cmdFactory.create(message);
            if (cmd) {
                cmd->execute();
            }
        } catch (const std::exception &_ex) {
            std::cerr << "Worker '" << name() << "' caught exception: " << _ex.what() << std::endl;
        }

        // plugin->execute();
    }

    stopped.test_and_set();
    stopped.notify_all();
}

void Worker::stop()
{
    needStop.test_and_set();
}

std::string &Worker::name() const noexcept
{
    return plugin->name();
}

void Worker::wait()
{
    stopped.wait(false);
    if(thread.joinable()){
        thread.join();
    }
}


}