#include "transport/message.hpp"
#include <gtest/gtest.h>


TEST(MSTest, Create)
{
    game::Message msgIn;
    
    auto cmd = builder.create(msgIn);
}