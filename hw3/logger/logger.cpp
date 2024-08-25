#include "logger.hpp"


namespace game::logger {

void Logger::push(std::string _msg)
{   
    registry.push(_msg);
}

bool Logger::empty() const noexcept
{
    return registry.empty();
}


}