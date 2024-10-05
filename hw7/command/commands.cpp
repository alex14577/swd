#include "command.hpp"
#include <iostream>


namespace command {

Print::Print(std::string_view _message) : 
    message{ _message }
{ }
void Print::execute()
{
    std::cout << message << std::endl;
}

Changer::Changer(uint64_t &_number, uint64_t _targetValue) :
    number{ _number },
    targetValue{ _targetValue }
{ }
void Changer::execute()
{
    number = targetValue;
}

Increment::Increment(std::atomic_size_t &_number) :
    number{ _number }
{ }
void Increment::execute()
{
    number++;
}

}