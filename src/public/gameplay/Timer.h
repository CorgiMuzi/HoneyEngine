#pragma once

namespace HoneyEngine
{
	class Timer {
	public:
		explicit Timer(float length);
		~Timer();

		void step(float deltaTime);
		void reset();

		float getLength() const { return mLength; }
		float getElapsedTime() const { return mElapsedTime; }
		bool isTimeout() const { return bTimeout; }
	private:
		float mLength;
		float mElapsedTime;
		bool bTimeout;
	};
}