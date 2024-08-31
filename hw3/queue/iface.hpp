#pragma once

#include <commands/command.hpp>

#include <memory>
#include <queue>

namespace game::queue {

class Interface {
public:
    using Ptr = std::shared_ptr<Interface>;

    virtual ~Interface() = default;

    virtual void push(command::Interface::Ptr _command) = 0; 

    [[nodiscard]]
    virtual command::Interface::Ptr get() = 0;

    [[nodiscard]]
    virtual bool empty() const noexcept = 0;
};

}