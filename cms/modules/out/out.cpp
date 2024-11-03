#include "out.hpp"
#include "modules/module.hpp"

#include <iostream>


namespace cms::module {

Out::Out() :
    name_{ "out" }
{ }

auto Out::execute(const std::string &_input) -> Output
{
    // std::cout << "Hello from Module " << name() << std::endl;
    return  {};
}

std::string &Out::name() 
{
    return name_;
}

}

BOOST_DLL_ALIAS(
    (cms::module::Out::create),
    (create_plugin)
)