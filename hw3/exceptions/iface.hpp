#pragma once

#include <commands/command.hpp>

#include <memory>


namespace game::exceptions {

class Interface {
public:
    using Ptr = std::shared_ptr<Interface>;

    Interface() = default;
    virtual ~Interface() = default;

    virtual void execute(const command::Interface::Ptr &, const std::exception &) = 0;
};

}