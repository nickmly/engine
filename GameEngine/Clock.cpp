#include "Clock.h"
#include <iostream>

Clock::Clock() 
{
	prevTime = 0.0;
	currTime = 0.0;

	deltaTime = -1.0;

	__int64 countsPerSecond = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSecond); // Get the ticks per second
	secondsPerCount = 1.0 / countsPerSecond;
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
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime); // Get the current number of clock ticks

	deltaTime = (currTime - prevTime) * secondsPerCount;

	prevTime = currTime;
}

