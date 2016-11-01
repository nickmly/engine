#pragma once
#include "SDL.h"
#include <Windows.h>

class Clock
{
private:
	int prevTime, currTime;
	double deltaTime;
public:
	Clock();
	~Clock();
	double GetDeltaTime();
	void Tick();
};

