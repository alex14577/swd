#include "handler.hpp"

#include <string>
#include <stdexcept>

namespace game::exceptions {


Handler::Handler(const queue::Interface::Ptr &_queue) :
    queue{ _queue }
{ }

void Handler::execute(const command::Interface::Ptr &_cmd, const std::exception &_ex)
{
    if (auto handler = behaviors.find(_cmd->type()); handler != behaviors.end()) {
        handler->second(_cmd, _ex);
    }
}

void Handler::behavior(command::Type _type, Behavior _behavior) {
    if (auto it = behaviors.find(_type); it == behaviors.end()){
        behaviors.emplace(_type, _behavior);
        return;
    }

    
    using namespace std::string_literals;
    throw std::runtime_error("Behavior for"s + command::toString(_type) + " has already set"s);
}

} // namespace exceptions.