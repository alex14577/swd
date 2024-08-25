#pragma once

#include <cassert>
#include <memory>


namespace game::command {

enum class Type {
    Unknown = 0U,
    WriteLog,
    Throwing,
    Retry,
    RetrySecond
};

std::string toString(Type _type) noexcept;

class Interface {
public:
    using Ptr = std::shared_ptr<Interface>;

    Interface(Type _type) noexcept :
        type_{ _type }
    {
        assert(type_ != Type::Unknown);
    }

    virtual ~Interface() = default;

    virtual void execute() = 0;

    [[nodiscard]]
    Type type() const noexcept {
        return type_;
    }

private:
    Type type_;
};

}