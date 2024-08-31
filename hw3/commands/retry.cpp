#include "retry.hpp"


namespace game::command {

Retry::Retry(const Interface::Ptr &_cmd) :
    Interface{ Type::Retry },
    cmd{ _cmd }
{ }

void Retry::execute()
{
    cmd->execute();
}

}