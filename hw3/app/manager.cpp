#include "manager.hpp"


namespace game::app {

void Manager::stop()
{
    stop_.store(true, std::memory_order_relaxed);
}

bool Manager::needStop() const noexcept
{
    return stop_.load(std::memory_order_relaxed);;
}

void Manager::status(State _status) noexcept
{
    state.store(_status, std::memory_order_release);
    statusChanged.test_and_set();
}

auto Manager::status() const noexcept -> State
{
    return state.load(std::memory_order_consume);
}


}