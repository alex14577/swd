#pragma once

#include "iface.hpp"
#include "manager.hpp"

#include <queue/iface.hpp>

namespace game::app {

class App : public Interface {
public: 
    App(const queue::Interface::Ptr &_queue, const Manager::Ptr &_manager, const exceptions::Interface::Ptr &_exceptionsHandler);

    void run() override final;

    virtual void inject(const exceptions::Interface::Ptr &) final;
 
private:
    queue::Interface::Ptr queue; 
    Manager::Ptr manager;
    exceptions::Interface::Ptr exceptionsHandler;
};

}