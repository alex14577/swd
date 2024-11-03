#pragma once

#include <memory>
#include <optional>
#include <string>
#include <transport/queue.hpp>

#include <unordered_map>

namespace cms::command {

class Interface {
public:
    virtual ~Interface() = default;
    virtual void execute() = 0;
};

using Field = std::optional<std::string>;

struct Context {

};

struct Message {
    std::string name;

    std::optional<Context> ctx;
    std::optional<std::string> data;
};

using Queue = transport::Queue<Message>;
using QueuePtr = std::shared_ptr<Queue>;
using QueueStorage = std::unordered_map<std::string, QueuePtr>;

struct Settings {
    std::vector<QueuePtr> queueIn;
    std::vector<QueuePtr> queueOut;
};

}