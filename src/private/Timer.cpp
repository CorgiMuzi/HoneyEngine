#include "Timer.h"

Timer::Timer(float length) : mLength(length), mElapsedTime(0), bTimeout(false)
{

}

Timer::~Timer()
{

}

void Timer::step(const float deltaTime)
{
    mElapsedTime += deltaTime;
    if (mElapsedTime >= mLength) {
        mElapsedTime -= mLength;
        bTimeout = true;
    }
}

void Timer::reset()
{
    mElapsedTime = 0;
    bTimeout = false;
}
