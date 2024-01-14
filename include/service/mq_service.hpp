#pragma once

#include <string>
#include <thread>
#include <deque>

#include <rabbitmq-c/amqp.h>
#include <rabbitmq-c/tcp_socket.h>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class MQService
{
private:
    amqp_connection_state_t conn;
    amqp_socket_t *socket = NULL;

public:
    std::deque<json> dataQueue;

    MQService();

    void sendMessage(const char *filename);

    ~MQService();
};