#pragma once

#include <memory>
#include <modules/module.hpp>


namespace cms::module {

class Out : public Module {
public:
    Out();
    ~Out() = default;

    Output execute(const std::string &_input) override;

    std::string &name() override;

    static Plugin create() {
        return std::make_shared<Out>();
    }

private:
    std::string name_;
};

}

