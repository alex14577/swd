#pragma once

#include <modules/module.hpp>


namespace cms::module {

class In : public Module {
public:
    In();
    ~In() = default;

    Output execute(const std::string &_input) override;

    std::string &name() override;

    static Plugin create() {
        return std::make_shared<In>();
    }

private:
    std::string name_;
};

}

