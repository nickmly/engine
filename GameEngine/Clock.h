#pragma once
#include <Windows.h>

class Clock
{
private:
	__int64 prevTime, currTime;
	double secondsPerCount, deltaTime;
public:
	Clock();
	~Clock();
	double GetDeltaTime();
	void Tick();
};

