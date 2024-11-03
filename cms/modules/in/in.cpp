#include "in.hpp"
#include "modules/module.hpp"

#include <iostream>


namespace cms::module {

In::In() :
    name_{ "in" }
{ }

auto In::execute(const std::string &_input) -> Output
{
    std::cout << "Hello from Module in:\n" << _input << std::endl;

    return {};
}

std::string &In::name() 
{
    return name_;
}

}

BOOST_DLL_ALIAS(
    (cms::module::In::create),
    (create_plugin)
)