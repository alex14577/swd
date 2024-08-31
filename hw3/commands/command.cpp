#include "command.hpp"

#include <string>


namespace game::command {

std::string toString(Type _type) noexcept {
    switch (_type)
    {
    case Type::Retry: return "Retry";
    case Type::WriteLog: return "WriteLog";
    case Type::Throwing: return "Throwing";
    case Type::RetrySecond: return "RetrySecond";
    default: return "Unknown";
    }
}

}