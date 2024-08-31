#include "app.hpp"

#include <thread>

namespace game::app {

App::App(const queue::Interface::Ptr &_queue,const Manager::Ptr &_manager, const exceptions::Interface::Ptr &_exceptionsHandler) :
    queue{ _queue },
    manager{ _manager },
    exceptionsHandler{ _exceptionsHandler }
{
    manager->status(Manager::State::NotStarted);    
}
 
void App::inject(const exceptions::Interface::Ptr &_exceptionsHandler) 
{
    exceptionsHandler = _exceptionsHandler;
}

  
void App::run()
{
    std::thread([&](){        
        manager->status(Manager::State::Running);

        while(!manager->needStop()) {
            auto cmd = queue->get();
            try
            {
                if (cmd) {
                    cmd->execute();
                }
            }
            catch(const std::exception& e)
            {
                if(exceptionsHandler) {
                    exceptionsHandler->execute(cmd, e);
                }
            }            
        }

        manager->status(Manager::State::Stop);

    }).detach();
}

}