#pragma once

#include <thread>
#include <string>

#include "object/humun_object.hpp"
#include "object/goal_object.hpp"

#include "manager/base_manager.hpp"

#include "service/mq_service.hpp"

#include "scenario/base_scenario.hpp"

using namespace std;

class GoalScenario : public BaseScenario
{
private:
    int step = 0;
    int turn = 0;
    int phase = 0;

    HumunObject *humun;
    GoalObject *goal;

    string json;

    string uuid;

    string phase_id;

    string fileName;

    thread *t;

    float angle = 0.;
    int frame = 0;

    float moveBefore = 0.;
    float moveAfter = 0.;
    string moveAmount = "";

    bool inGoal = false;

    MQService *mqService = nullptr;

    void startTurn();
    void capture();
    void mqProduceChoose();
    void waitForResponse();
    void changeAngle();
    void movePosition();
    void mqProduceResult();
    void waitForResponseDoNothing();

public:
    void initialize() override;
    void run() override;
};
