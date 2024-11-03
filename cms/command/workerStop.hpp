#pragma once

#include "command.hpp"
#include "worker/worker.hpp"

namespace cms::worker {
class Worker;
}

namespace cms::command {

class WorkerStop final : public Interface {
public:
    WorkerStop(worker::Worker *_worker);
    ~WorkerStop() = default;
    void execute() override;

private:
    worker::Worker *worker;
};

}