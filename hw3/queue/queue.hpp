#pragma once

#include "iface.hpp"


namespace game::queue {

class Queue : public Interface {
public:
    Queue();

    void push(command::Interface::Ptr _command) override;
    command::Interface::Ptr get() override;

    [[nodiscard]]
    bool empty() const noexcept override;

private:
    std::queue<command::Interface::Ptr> registry;
};

}