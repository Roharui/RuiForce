#pragma once

#include <string>
#include <thread>
#include <deque>

#include <rabbitmq-c/amqp.h>
#include <rabbitmq-c/tcp_socket.h>

class MQService
{
private:
    amqp_connection_state_t conn;
    amqp_socket_t *socket = NULL;

public:
    std::deque<float> dataQueue;

    MQService();

    void sendMessage(const char *filename, int len);

    ~MQService();
};