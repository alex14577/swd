#pragma once

#include <boost/dll/alias.hpp> 
#include <boost/shared_ptr.hpp>
#include <memory>

namespace cms::module {

class Module {
public:
    virtual ~Module() = default;

    using Output = std::pair<std::vector<std::string>, std::vector<std::string>>;
    virtual Output execute(const std::string &_input) = 0;

    virtual std::string &name() = 0;
};

using Plugin = std::shared_ptr<cms::module::Module>;
using Creator = Plugin();

}


