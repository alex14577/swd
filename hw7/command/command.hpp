#pragma once

#include <atomic>
#include <cstdint>
#include <string_view>


namespace command {

class Icommand {
public:
    virtual ~Icommand() = default;  
    virtual void execute() = 0;

};

class Print : public Icommand {
public:
    Print(std::string_view _message);

    void execute() override;

private:
    std::string_view message;
};

class Changer : public Icommand {
public:
    Changer(uint64_t &_number, uint64_t _targetValue);

    void execute() override;

private:
    uint64_t &number;
    uint64_t targetValue;
};

class Increment : public Icommand {
public:
    Increment(std::atomic_size_t &_number);

    void execute() override;

private:
    std::atomic_size_t &number;
};

}