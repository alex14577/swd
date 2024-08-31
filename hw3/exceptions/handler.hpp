#pragma once

#include "iface.hpp"

#include <queue/iface.hpp>

#include <functional>
#include <version>


namespace game::exceptions {

class Handler : public Interface {
public:

    using Behavior = std::function<void(const command::Interface::Ptr &, const std::exception &)>;

    Handler(const queue::Interface::Ptr &_queue);
    ~Handler() = default;

    void execute(const command::Interface::Ptr &, const std::exception &) override;

    void behavior(command::Type, Behavior);

private:
    queue::Interface::Ptr queue;

    std::unordered_map<command::Type, Behavior> behaviors;
};

}