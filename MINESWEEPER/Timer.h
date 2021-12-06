#ifndef _TIMER_H
#define _TIMER_H

#include <chrono>

namespace EngineUtils
{
	class Timer
	{
	private:
		static Timer* sInstance;

		std::chrono::system_clock::time_point mStartTime;
		std::chrono::duration<float> mDeltaTime;
		float mTimeScale;

	public:

		static Timer* Instance();	// Retrieve Instance and clear it
		static void Release();

		void Reset();	// Reset Timer

		float DeltaTime();	// Returns Delta Time

		void TimeScale(float t = 1.0f);

		float TimeScale();	// In case wanna check in what TimeScale we're running at

		void Tick();	// Takes our Timer forward as we loop thru Game loop

	private:

		Timer();
		~Timer();

	};
}

#endif // !_TIMER_H
