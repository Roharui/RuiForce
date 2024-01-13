#pragma once

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

#define GAME_TITLE "WORLD SIMULATOR"

#define CAMERA_INTERVAL 30.0f

#define FPS 60

#define HUMUN_SIZE 2.5f
#define HUMUN_SIZE_R HUMUN_SIZE / 2

#define MAP_BLOCK_COUNT 10
#define MAP_SIZE HUMUN_SIZE *MAP_BLOCK_COUNT

#define HUMUN_MOVE_SPEED 0.1f
#define ANGLE_MOVE_SPEED 0.1f

#define DEFAULT_PHASE 5
#define DEFAULT_TURN 15

#define MQ_HOST "localhost"
#define MQ_PORT 5672
#define MQ_ID "guest"
#define MQ_PW "guest"
#define MQ_EXCHANGE "test"
#define MQ_ROUTING_KEY "test"
#define MQ_QUEUE "test"
#define MQ_REPLY "reply"