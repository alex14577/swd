#pragma once

#include <memory>
#include <modules/module.hpp>


namespace cms::module {

class Module1 : public Module {
public:
    Module1();
    ~Module1() = default;

    Output execute(const std::string &_input) override;

    std::string &name() override;

    static Plugin create() {
        return std::make_shared<Module1>();
    }

private:
    std::string name_;
};

}

