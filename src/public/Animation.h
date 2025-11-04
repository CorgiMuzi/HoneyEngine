#pragma once
#include "Timer.h"

class Animation {
public:
    Animation() : mTimer(0), mFrameCount(0) {}
    Animation(int frameCount, float length);
    ~Animation();

    void step(const float deltaTime) { mTimer.step(deltaTime); }
    float getLength() const { return mTimer.getLength(); }
    int getCurrentFrame() const { return static_cast<int>(mTimer.getElapsedTime() / mTimer.getLength()) * mFrameCount; }

private:
    Timer mTimer;
    int mFrameCount;
};
