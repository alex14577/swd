#pragma once

#include <atomic>
#include <chrono>
#include <memory>
#include <thread>

namespace game::app {

class Manager {
public:
    using Ptr = std::shared_ptr<Manager>;

    enum class State {
        NotStarted = 0U,
        Running,
        Stopping,
        Stop
    };

    Manager() noexcept = default;

    void stop();

    [[nodiscard]]
    bool needStop() const noexcept;

    void status(State status) noexcept;
    State status() const noexcept;

    template <typename Period>
    [[nodiscard]]
    bool wait(State status, Period _timeout) const noexcept;

private:
    std::atomic_bool stop_;
    std::atomic<State> state;
    std::atomic_flag statusChanged;
};

template <typename Period>
bool Manager::wait(State _status, Period _timeout) const noexcept
{   
    auto start{ std::chrono::steady_clock::now() };

    do {
        if(status() == _status) {
            return true;
        }

        std::this_thread::yield();

    } while (std::chrono::steady_clock::now() - start < _timeout);

    return false;
}

}