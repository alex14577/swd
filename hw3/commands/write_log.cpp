#include "write_log.hpp"

#include <iostream>

namespace game::command {

WriteLog::WriteLog(const logger::Interface::Ptr &_logger, std::string _msg) :
    Interface{ Type::WriteLog },
    logger{ _logger },
    msg{ std::move(_msg) }
{ }

void WriteLog::execute() 
{
    logger->push(msg);
}

}