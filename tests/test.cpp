#include <iostream>

#include <gtest/gtest.h>

#include <iostream>

#include <service/mq_service.hpp>

TEST(Basic, GTest_test)
{
    EXPECT_EQ(3, 3);
}

TEST(MQ, GTest_test)
{
    MQService *mq = new MQService();

    std::string x = "\"testfile.jpg\"";

    mq->sendMessage(x.c_str(), x.size());

    delete mq;

    mq = new MQService();

    mq->sendMessage(x.c_str(), x.size());

    delete mq;
}