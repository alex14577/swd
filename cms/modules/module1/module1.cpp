#include "module1.hpp"
#include "modules/module.hpp"

#include <iostream>


namespace cms::module {

Module1::Module1() :
    name_{ "module1" }
{ }

auto Module1::execute(const std::string &_input) -> Output
{
    std::cout << "Hello from Module " << _input << std::endl;

    return {};
}

std::string &Module1::name() 
{
    return name_;
}

}

BOOST_DLL_ALIAS(
    (cms::module::Module1::create),
    (create_plugin)
)