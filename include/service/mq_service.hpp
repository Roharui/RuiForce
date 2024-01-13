#pragma once

#include <string>
#include <thread>
#include <vector>

#include <rabbitmq-c/amqp.h>
#include <rabbitmq-c/tcp_socket.h>

class MQService
{
private:
    amqp_connection_state_t conn;
    amqp_socket_t *socket = NULL;

public:
    std::vector<char *> dataVec;

    MQService();

    void sendMessage(const char *filename, int len);

    bool isResponsed();

    ~MQService();
};