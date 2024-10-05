#include "command/command.hpp"
#include "invoker/invoker.hpp"
#include <cstdint>
#include <gtest//gtest.h>
#include <memory>

class HardStop : public command::Icommand {
public:
    HardStop(engine::Invoker &_invoker) :
        invoker{ _invoker }
    { }
    
    void execute() override {
        invoker.hardStop();
    }

private:
    engine::Invoker &invoker;
};

class SoftStop : public command::Icommand {
public:
    SoftStop(engine::Invoker &_invoker) :
        invoker{ _invoker }
    { }
    
    void execute() override {
        invoker.softStop();
    }

private:
    engine::Invoker &invoker;
};

TEST(CmdTest, CommandsExecutes)
{
    auto q = std::make_shared<engine::Queue>();
    engine::Invoker invoker(q, std::make_unique<engine::Invoker::BehaviourCounted>(2));
    invoker.start();

    uint64_t value = 5;
    uint64_t expectedValue = 10;
    q->push(std::make_unique<command::Print>("Hello World!"));
    q->push(std::make_unique<command::Changer>(value, expectedValue));

    invoker.wait();
    EXPECT_EQ(value, expectedValue);
}

TEST(CmdTest, CommonBehaviour)
{
    auto q = std::make_shared<engine::Queue>();
    engine::Invoker invoker(q);

    uint64_t value = 5;
    uint64_t expectedValue = 10;
    for(std::size_t i = 0; i < 1000U; ++i) {
        q->push(std::make_unique<command::Changer>(value, expectedValue));
    }

    invoker.start();

    while(q->size() > 0);
    invoker.stop();

    invoker.wait();

    EXPECT_EQ(q->size(), 0);
}

TEST(CmdTest, CommandHardStop)
{
    auto q = std::make_shared<engine::Queue>();
    engine::Invoker invoker(q);
    invoker.start();

    std::atomic_size_t value = 0;
    for(std::size_t i = 0; i < 100000U; ++i) {
        q->push(std::make_unique<command::Increment>(value));
    }
    q->push(std::make_unique<HardStop>(invoker));
    for(std::size_t i = 0; i < 1000U; ++i) {
        q->push(std::make_unique<command::Increment>(value));
    }


    invoker.wait();

    EXPECT_EQ(q->size(), 1000U);
}

TEST(CmdTest, CommandSoftStop)
{
    auto q = std::make_shared<engine::Queue>();
    engine::Invoker invoker(q);


    std::atomic_size_t value = 0;
    for(std::size_t i = 0; i < 100000U; ++i) {
        q->push(std::make_unique<command::Increment>(value));
    }
    q->push(std::make_unique<SoftStop>(invoker));
    for(std::size_t i = 0; i < 1000U; ++i) {
        q->push(std::make_unique<command::Increment>(value));
    }

    invoker.start();
    invoker.start();

    invoker.wait();
    EXPECT_EQ(q->size(), 0);
    EXPECT_EQ(value.load(), 100000U + 1000);
}