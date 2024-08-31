#include "retry_second.hpp"


namespace game::command {

RetrySecond::RetrySecond(const Interface::Ptr &_cmd) :
    Interface{ Type::RetrySecond },
    cmd{ std::move(_cmd) }
{ }

void RetrySecond::execute()
{
    cmd->execute();
}

}