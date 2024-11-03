#include <command/command.hpp>
#include <filesystem>
#include <modules/module.hpp>
#include <string>
#include <worker/worker.hpp>
#include <loader/loader.hpp>

#include <exception>
#include <iostream>
#include <iterator>
#include <memory>
#include <ranges>
#include <unordered_map>
#include <vector>
#include <csignal>
#include <fstream>

using namespace cms;

constexpr auto InPutServiceQueue = "InputService";
constexpr auto OutPutServiceQueue = "OutputService";

using WorkerInit = std::tuple<module::Plugin, command::QueuePtr, std::vector<command::QueuePtr>>;

std::atomic_flag needExit{ false };

void signalHandler( int signum ) {

    std::cout << "Received signal : " << signum << std::endl;

    needExit.test_and_set();
    needExit.notify_all();
}

std::string readFile(const std::filesystem::path &_path)
{
    std::ifstream in(_path);

    std::string res;
    if(in.is_open()) {
        while(in) {
            std::string buf;
            std::getline(in, buf);
            res += buf;
        }
    } else {
        std::cerr << "No such file: " << _path << std::endl;
    }
    return res;
}

WorkerInit createIn(loader::Loader &_loader, const cms::command::QueueStorage &_queues)
{
    WorkerInit res;
    auto &[plugin, queueIn, queuesOut] = res;

    plugin = _loader.create("in");

    auto itQueueIn = _queues.find(InPutServiceQueue);;
    if(itQueueIn == _queues.end()) {
        using namespace std::string_literals;
        throw std::runtime_error("No "s + InPutServiceQueue + " queue"s);
    };
    queueIn = itQueueIn->second;

    auto filter = [](const command::QueuePtr &_queue) {
        return _queue->id() != "in";
    };
    
    std::ranges::copy(_queues | std::ranges::views::all | std::ranges::views::elements<1> | std::views::filter(filter),
                     std::back_inserter(queuesOut));

    return res;
}

WorkerInit createOut(loader::Loader &_loader, const cms::command::QueueStorage &_queues)
{
    WorkerInit res;
    auto &[plugin, queueIn, queuesOut] = res;

    plugin = _loader.create("out");

    auto itQueueIn = _queues.find("out");;
    if(itQueueIn == _queues.end()) {
        using namespace std::string_literals;
        throw std::runtime_error("No out queue"s);
    };
    queueIn = itQueueIn->second;


    auto itQueueOut = _queues.find(OutPutServiceQueue);;
    if(itQueueOut == _queues.end()) {
        using namespace std::string_literals;
        throw std::runtime_error("No "s + OutPutServiceQueue + " queue"s);
    };

    queuesOut.push_back(itQueueOut->second);
    return res;
}

WorkerInit createModule(const std::string &_name, loader::Loader &_loader, const cms::command::QueueStorage &_queues)
{
    WorkerInit res;
    auto &[plugin, queueIn, queuesOut] = res;

    plugin = _loader.create(_name);
    auto queueInIt = _queues.find(_name);
    if(queueInIt == _queues.end()) {
        using namespace std::string_literals;
        throw std::runtime_error("No "s + _name + " queue"s);
    };

    queueIn = queueInIt->second;

    auto queueOutIt = _queues.find("out");
    if(queueOutIt == _queues.end()) {
        throw std::runtime_error("No out queue");
    };
    queuesOut.emplace_back(queueOutIt->second);

    return res;
}


int main(int argc, const char **argv)
{
    try {
        loader::Loader loader(argv[1]);

        auto plugins = loader.plugins();

        command::QueueStorage queues;
        for(const auto &pluginName : plugins) {
            auto queue = std::make_shared<command::Queue>(pluginName);
            queues.emplace(pluginName, queue);
        }

        queues.emplace(InPutServiceQueue, std::make_shared<command::Queue>(InPutServiceQueue));
        queues.emplace(OutPutServiceQueue, std::make_shared<command::Queue>(OutPutServiceQueue));

        std::vector<std::shared_ptr<worker::Worker>> workers;
        {
            auto [plugin, queueIn, queuesOut] = createIn(loader, queues);
            workers.emplace_back(std::make_shared<worker::Worker>(plugin, queueIn, queuesOut))->start();
        }
        {
            auto [plugin, queueIn, queuesOut] = createOut(loader, queues);
            workers.emplace_back(std::make_shared<worker::Worker>(plugin, queueIn, queuesOut))->start();
        }

        auto modules = loader.plugins() | std::views::all | std::views::filter([](const std::string &_name) {
            return _name != "out" && _name != "in";
        });

        for(const auto &name : modules) {
            auto [plugin, queueIn, queuesOut] = createModule(name, loader, queues);
            auto &worker = workers.emplace_back(std::make_shared<worker::Worker>(plugin, queueIn, queuesOut));
            worker->start();
        }

        signal(SIGINT, signalHandler);

        std::filesystem::path fileIn{argv[2]};

        auto queueIn = queues.find(InPutServiceQueue);
        // auto queueOut = queues.find(OutPutServiceQueue);

        auto str = readFile(fileIn);
        queueIn->second->push(command::Message{.name = "construct", .data = str});
        

        needExit.wait(false);

        std::ranges::for_each(std::ranges::views::elements<1>(queues), [](const auto &_queue) { 
            _queue->push(command::Message{.name = "stop"}); 
            }
        );

        std::cout << "Workers stopped" << std::endl;
        std::ranges::for_each(workers, [](const auto &_worker) { 
            _worker->wait();
            }
        );


    } catch (const std::exception &_ex) {
        std::cout << _ex.what() << std::endl;
    }

}