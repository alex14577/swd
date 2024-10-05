#pragma once

#include <atomic>
#include <command/command.hpp>

#include <condition_variable>
#include <cstdint>
#include <memory>
#include <mutex>
#include <queue>


namespace engine {

class Queue {
public:

    bool tryPop(std::unique_ptr<command::Icommand> &_command);
    std::unique_ptr<command::Icommand> pop();
    bool tryPush(std::unique_ptr<command::Icommand> _command);
    void push(std::unique_ptr<command::Icommand> _command);

    std::size_t size() const noexcept;

private:
    std::queue<std::unique_ptr<command::Icommand>> queue;
    mutable std::mutex m;
    std::condition_variable cv;
};

class Invoker {
public:
    class Behaviour {
    public:
        Behaviour() = default;

        virtual ~Behaviour() = default;
        virtual bool execute(Queue &_queue) = 0;
    };

    class BehaviourCounted : public Behaviour {
    public:
        BehaviourCounted(uint64_t _times);
        bool execute(Queue &_queue);

    private:
        uint64_t times;
        uint64_t cnt;
    };

    class BehaviourCommon : public Behaviour {
    public:
        bool execute(Queue &_queue) override;
    };

    class BehaviourHardStop : public Behaviour {
    public:
        bool execute(Queue &_queue);
    };
    
    class BehaviourSoftStop : public Behaviour {
    public:
        bool execute(Queue &_queue);
    };

    Invoker(const std::shared_ptr<Queue> &_queue, std::unique_ptr<Behaviour> _behaviour = nullptr);

    void loop();
    void start();
    void stop();
    void wait();

    void hardStop();
    void softStop();

private:
    void checkBehaviour();

    std::shared_ptr<Queue> queue;
    std::unique_ptr<Behaviour> nextbehaviour;
    std::unique_ptr<Behaviour> curBehaviour;
    std::atomic_flag needStop{ false };
    std::atomic_flag stopped{ false };
    std::mutex m;
};

}