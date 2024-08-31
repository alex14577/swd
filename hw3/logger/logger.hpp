#pragma once

#include "iface.hpp"

#include <string>


namespace game::logger {

class Logger : public Interface {
public:
    void push(std::string _msg) override;

    [[nodiscard]]
    bool empty() const noexcept override;

private:
    std::queue<std::string> registry;
};

}