
#include <ctype.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <rabbitmq-c/amqp.h>
#include <rabbitmq-c/tcp_socket.h>
#include <rabbitmq-c/framing.h>

#include <nlohmann/json.hpp>

#include "config.hpp"

#include "service/mq_service.hpp"

using namespace std;
using json = nlohmann::json;

void die(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fprintf(stderr, "\n");
    exit(1);
}

void die_on_error(int x, char const *context)
{
    if (x < 0)
    {
        fprintf(stderr, "%s: %s\n", context, amqp_error_string2(x));
        exit(1);
    }
}

void die_on_amqp_error(amqp_rpc_reply_t x, char const *context)
{
    switch (x.reply_type)
    {
    case AMQP_RESPONSE_NORMAL:
        return;

    case AMQP_RESPONSE_NONE:
        fprintf(stderr, "%s: missing RPC reply type!\n", context);
        break;

    case AMQP_RESPONSE_LIBRARY_EXCEPTION:
        fprintf(stderr, "%s: %s\n", context, amqp_error_string2(x.library_error));
        break;

    case AMQP_RESPONSE_SERVER_EXCEPTION:
        switch (x.reply.id)
        {
        case AMQP_CONNECTION_CLOSE_METHOD:
        {
            amqp_connection_close_t *m =
                (amqp_connection_close_t *)x.reply.decoded;
            fprintf(stderr, "%s: server connection error %uh, message: %.*s\n",
                    context, m->reply_code, (int)m->reply_text.len,
                    (char *)m->reply_text.bytes);
            break;
        }
        case AMQP_CHANNEL_CLOSE_METHOD:
        {
            amqp_channel_close_t *m = (amqp_channel_close_t *)x.reply.decoded;
            fprintf(stderr, "%s: server channel error %uh, message: %.*s\n",
                    context, m->reply_code, (int)m->reply_text.len,
                    (char *)m->reply_text.bytes);
            break;
        }
        default:
            fprintf(stderr, "%s: unknown server error, method id 0x%08X\n",
                    context, x.reply.id);
            break;
        }
        break;
    }

    exit(1);
}

char *stringify_bytes(amqp_bytes_t bytes)
{
    /* We will need up to 4 chars per byte, plus the terminating 0 */
    char *res = (char *)malloc(bytes.len * 4 + 1);
    uint8_t *data = (uint8_t *)bytes.bytes;
    char *p = res;
    size_t i;

    for (i = 0; i < bytes.len; i++)
    {
        if (data[i] >= 32 && data[i] != 127)
        {
            *p++ = data[i];
        }
        else
        {
            *p++ = '\\';
            *p++ = '0' + (data[i] >> 6);
            *p++ = '0' + (data[i] >> 3 & 0x7);
            *p++ = '0' + (data[i] & 0x7);
        }
    }

    *p = 0;
    return res;
}

MQService::MQService()
{
    char const *hostname = MQ_HOST;
    int port = MQ_PORT;

    conn = amqp_new_connection();

    socket = amqp_tcp_socket_new(conn);
    if (!socket)
    {
        die("creating TCP socket");
    }

    int status = amqp_socket_open(socket, hostname, port);
    if (status)
    {
        die("opening TCP socket");
    }

    die_on_amqp_error(amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, MQ_ID, MQ_PW), "Logging in");
    amqp_channel_open(conn, 1);
    die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel");

    // amqp_exchange_declare(conn, 1, amqp_cstring_bytes(MQ_EXCHANGE), amqp_cstring_bytes("direct"), 0, 1, 0, 0, amqp_empty_table);
    // amqp_exchange_declare(conn, 1, amqp_cstring_bytes(MQ_REPLY), amqp_cstring_bytes("direct"), 0, 1, 0, 0, amqp_empty_table);

    // amqp_queue_declare(conn, 1, amqp_cstring_bytes(MQ_QUEUE), 0, 1, 0, 0, amqp_empty_table);
    // amqp_queue_declare(conn, 1, amqp_cstring_bytes(MQ_REPLY), 0, 1, 0, 0, amqp_empty_table);

    amqp_queue_purge(conn, 1, amqp_cstring_bytes(MQ_QUEUE));
    amqp_queue_purge(conn, 1, amqp_cstring_bytes(MQ_REPLY));

    amqp_queue_bind(conn, 1, amqp_cstring_bytes(MQ_QUEUE), amqp_cstring_bytes(MQ_EXCHANGE), amqp_cstring_bytes(MQ_ROUTING_KEY), amqp_empty_table);
    die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring exchange");
}

void MQService::sendMessage(const char *filename)
{
    amqp_bytes_t message_bytes;

    message_bytes = amqp_cstring_bytes(filename);

    amqp_basic_properties_t properties = {
        ._flags = AMQP_BASIC_REPLY_TO_FLAG,
        .reply_to = amqp_cstring_bytes(MQ_REPLY),
    };

    die_on_error(amqp_basic_publish(conn, 1, amqp_cstring_bytes(MQ_EXCHANGE), amqp_cstring_bytes(MQ_ROUTING_KEY), 0, 0, &properties, message_bytes), "Publishing");

    amqp_basic_consume(conn, 1, amqp_cstring_bytes(MQ_REPLY), amqp_empty_bytes, 0, 0, 0, amqp_empty_table);
    die_on_amqp_error(amqp_get_rpc_reply(conn), "Consuming");

    {
        amqp_rpc_reply_t res;
        amqp_envelope_t envelope;

        amqp_maybe_release_buffers(conn);

        res = amqp_consume_message(conn, &envelope, NULL, 0);

        amqp_message_t message = envelope.message;

        json j = json::parse(stringify_bytes(message.body));

        this->dataQueue.push_back(j);

        amqp_basic_ack(conn, 1, (unsigned)envelope.delivery_tag, 0);

        amqp_destroy_envelope(&envelope);
    }
}

MQService::~MQService()
{
    die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
    die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
    die_on_error(amqp_destroy_connection(conn), "Ending connection");
}