#include "Clock.h"
#include <iostream>

Clock::Clock() 
{ 
	prevTime = 0.0;
	currTime = 0.0;

	deltaTime = -1.0;
	//__int64 countsPerSecond = 0;
	//QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSecond); // Get the ticks per second
	//secondsPerCount = 1.0 / countsPerSecond;
}

Clock::~Clock()
{

}

double Clock::GetDeltaTime() 
{
	return deltaTime;
}

void Clock::Tick() 
{
	currTime = SDL_GetTicks();
	deltaTime = (double)(currTime - prevTime) / 1000;
	prevTime = currTime;
	//QueryPerformanceCounter((LARGE_INTEGER*)&currTime); // Get the current number of clock ticks

	//deltaTime = (currTime - prevTime) * secondsPerCount;

	//prevTime = currTime;
}

