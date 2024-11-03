#include "workerStop.hpp"

#include <cassert>
#include <worker/worker.hpp>

namespace cms::command {

WorkerStop::WorkerStop(worker::Worker *_worker) : 
    worker{ _worker }
{ 
    assert(worker != nullptr);
}

void WorkerStop::execute() 
{
    worker->stop();
}

}