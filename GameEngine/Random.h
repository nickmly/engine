#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>

class Random
{
public:
	Random();
	~Random();
	int GetRangeInt(int low, int high);
	float GetRangeFloat(float low, float high);
	double GetRangeDouble(double low , double high);
};

