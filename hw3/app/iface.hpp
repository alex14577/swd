#pragma once

#include <exceptions/iface.hpp>
#include <commands/command.hpp>

#include <memory>
#include <unordered_map>

namespace game::app {

class Interface {
public: 
    using Ptr = std::shared_ptr<Interface>;

    virtual ~Interface() = default;

    virtual void run() = 0; 

    virtual void inject(const exceptions::Interface::Ptr &) {};

private:

};

}