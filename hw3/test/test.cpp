#include <gtest/gtest.h>

#include <app/app.hpp>
#include <app/manager.hpp>
#include <queue/queue.hpp>
#include <exceptions/handler.hpp>
#include <logger/logger.hpp>

#include <commands/write_log.hpp>
#include <commands/throw_cmd.hpp>
#include <commands/retry.hpp>
#include <commands/retry_second.hpp>

#include <thread>

using namespace game;
using namespace std::chrono_literals;

class AppTest : public testing::Test {
public:
    void SetUp() override final 
    {
        queue = std::make_shared<queue::Queue>();
        handler = std::make_shared<exceptions::Handler>(queue);

        manager = std::make_shared<app::Manager>();
        app = std::make_shared<app::App>(queue, manager, handler);
        logger = std::make_shared<logger::Logger>();

        app->run();

        EXPECT_TRUE(manager->wait(app::Manager::State::Running, 2s));
    }

    void TearDown() override final {
        manager->stop();
        EXPECT_TRUE(manager->wait(app::Manager::State::Stop, 2s));         
    }

protected:
    app::Interface::Ptr app;
    app::Manager::Ptr manager;
    queue::Interface::Ptr queue;
    std::shared_ptr<exceptions::Handler> handler;
    std::shared_ptr<logger::Logger> logger;

private:
    void initHandler(std::shared_ptr<exceptions::Handler> &);

};


TEST_F(AppTest, CmdLog)
{
    queue->push(std::make_shared<command::WriteLog>(logger, "error"));

    std::this_thread::sleep_for(1s);
    while(!queue->empty());    

    EXPECT_FALSE(logger->empty());
}

TEST_F(AppTest, RetryCmd)
{
    bool executed = false;

    handler->behavior(command::Type::Throwing, [&](const command::Interface::Ptr &_cmd, const std::exception &_ex) {
        auto cmdRetry = std::make_shared<command::Retry>(_cmd);
        queue->push(cmdRetry);
        executed = true;
    });

    queue->push(std::make_shared<command::Throwing>());

    std::this_thread::sleep_for(1s);

    while(!queue->empty());

    EXPECT_TRUE(executed);
}

TEST_F(AppTest, RetryAndWriteLogCmd)
{
    bool executedThrowing = false;
    bool executedRetry = false;

    handler->behavior(command::Type::Throwing, [&](const command::Interface::Ptr &_cmd, const std::exception &_ex) {
        auto cmdRetry = std::make_shared<command::Retry>(_cmd);
        queue->push(cmdRetry);
        executedThrowing = true;
    });

    handler->behavior(command::Type::Retry, [&](const command::Interface::Ptr &_cmd, const std::exception &_ex) {
        auto cmd = std::make_shared<command::WriteLog>(logger, _ex.what());
        queue->push(cmd);
        executedRetry = true;
    });

    queue->push(std::make_shared<command::Throwing>());

    std::this_thread::sleep_for(1s);
    while(!queue->empty());


    EXPECT_TRUE(executedThrowing);
    EXPECT_TRUE(executedRetry);
    EXPECT_FALSE(logger->empty());
}

TEST_F(AppTest, RetryTwiceAndWriteLogCmd)
{
    bool executedThrowing = false;
    bool executedRetry = false;
    bool executedWriteLog = false;

    handler->behavior(command::Type::Throwing, [&](const command::Interface::Ptr &_cmd, const std::exception &_ex) {
        auto cmdRetry = std::make_shared<command::Retry>(_cmd);
        queue->push(cmdRetry);
        executedThrowing = true;
    });

    handler->behavior(command::Type::Retry, [&](const command::Interface::Ptr &_cmd, const std::exception &_ex) {
        auto cmd = std::make_shared<command::RetrySecond>(_cmd);
        queue->push(cmd);
        executedRetry = true;
    });

    handler->behavior(command::Type::RetrySecond, [&](const command::Interface::Ptr &_cmd, const std::exception &_ex) {
        auto cmd = std::make_shared<command::WriteLog>(logger, _ex.what());
        queue->push(cmd);
        executedWriteLog = true;
    });

    queue->push(std::make_shared<command::Throwing>());

    std::this_thread::sleep_for(1s);
    while(!queue->empty());


    EXPECT_TRUE(executedThrowing);
    EXPECT_TRUE(executedRetry);
    EXPECT_TRUE(executedWriteLog);
    EXPECT_FALSE(logger->empty());
}