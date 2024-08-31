#include "queue.hpp"

namespace game::queue {

Queue::Queue()
{ }

void Queue::push(command::Interface::Ptr _command)
{   
    registry.push(_command);
}

auto Queue::get() -> command::Interface::Ptr 
{
    if(!registry.empty()){
        auto result = std::move(registry.back());
        registry.pop();
        return result;
    } 
    return nullptr;
}

bool Queue::empty() const noexcept
{
    return registry.empty();
}


}