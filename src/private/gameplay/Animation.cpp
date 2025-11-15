#include "gameplay/Animation.h"

namespace HoneyEngine
{
	Animation::Animation(int frameCount, float length) : mTimer(length), mFrameCount(frameCount)
	{

	}

	Animation::~Animation() {}
}