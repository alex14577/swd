#pragma once

#include "command.hpp"

#include <logger/iface.hpp>

namespace game::command {

class WriteLog : public Interface  {
public:
    WriteLog(const logger::Interface::Ptr &_logger, std::string _msg);

    void execute() override;

private:
    logger::Interface::Ptr logger;
    std::string msg;
};

}