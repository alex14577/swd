#include "throw_cmd.hpp"

#include <iostream>
#include <exception>

namespace game::command {

Throwing::Throwing() :
    Interface{ Type::Throwing }
{ }

void Throwing::execute() 
{
    throw std::runtime_error("Cmd Throw Exception !!!");
}

}