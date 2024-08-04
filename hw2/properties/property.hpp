#pragma once

#include <memory>
#include <string>

namespace game {


template <std::size_t Id>
struct Number {
    static constexpr std::size_t id = Id;
};

class Property {
public:
    using Pointer = std::unique_ptr<Property>;

    virtual ~Property() = default;

    virtual double asDouble() const { throw std::runtime_error("Property does not support 'DOUBLE' values"); };
    virtual void set(double) { throw std::runtime_error("Property does not support 'DOUBLE' values"); };

    virtual std::size_t asNumeric() const { throw std::runtime_error("Property does not support 'UNSIGNED' values"); };
    virtual void set(std::size_t) { throw std::runtime_error("Property does not support 'UNSIGNED' values"); };

    virtual int asInt() const { throw std::runtime_error("Property does not support 'INT' values"); };
    virtual void set(int) { throw std::runtime_error("Property does not support 'INT' values"); };
    
    virtual std::string asString() const { throw std::runtime_error("Property does not support 'STRING' values"); };
    virtual void set(std::string) { throw std::runtime_error("Property does not support 'STRING' values"); };
};

}