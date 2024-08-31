#pragma once

#include <memory>
#include <queue>

namespace game::logger {

class Interface {
public:
    using Ptr = std::shared_ptr<Interface>;

    Interface() = default;
    virtual ~Interface() = default;

    virtual void push(std::string _msg) = 0;

    [[nodiscard]]
    virtual bool empty() const noexcept = 0;
};

}