#pragma once

#include "object/humun_object.hpp"

#include "manager/base_manager.hpp"

class RutineManager : public BaseManager
{
private:
    int step = 0;
    int turn = 0;
    int phase = 0;

    bool init = false;
    bool inGoal = false;

    HumunObject *humun;

    // void MoveHumun();
    void Capture();

    /*

    1. 랜덤 등장
    2. 랜덤 골 등장
    3. 15턴간 이동
        3-1. 캡쳐
        3-2. 요청
        3-3. 대기 -> 이동
        3-4. 캡쳐 사진 + 실제 결과 + 예측 결과 저장
        3-5. 턴 차감
        3-6. 골에 들어갔다면 페이즈 차감

    */

public:
    void run() override;
};
