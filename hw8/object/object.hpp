#pragma once

#include <any>
#include <string>
#include <unordered_map>
#include <utility>

namespace game::object {

class Object {
public:

    template<typename Type>
    void set(std::string _property, Type &_value)
    {
        values[_property] = std::forward(_value);
    }

    template<typename Type>
    Type &get(std::string _property)
    {
        return values.at(_property);
    }

private:
    std::unordered_map<std::string, std::any> values;

};

}