#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>


namespace cms::transport {

template<typename Type>
class Queue {
public:
    Queue(const std::string &_name) noexcept :
        name{ _name }
    { }

    void push(Type &&_value) {
        std::lock_guard lc{m};

        queue.push(std::move(_value));

        cv.notify_all();
    }

    Type pop() {
        std::unique_lock lc{ m} ;

        cv.wait(lc, [this]() {
            return !queue.empty();
        });


        auto res = queue.front();
        queue.pop();
        return res;
    }

    const std::string &id() const noexcept {
        return name;
    }

private:
    std::string name;
    std::queue<Type> queue;

    std::mutex m;
    std::condition_variable cv;
};

}