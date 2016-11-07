#include "Random.h"



Random::Random()
{
	srand(time(NULL)); // Seed the randomizer with the current time (this way it is a different seed every time)
}


Random::~Random()
{
}

int Random::GetRangeInt(int low, int high)
{
	return rand() % high + low;
}

float Random::GetRangeFloat(float low, float high)
{
	float num = (float)rand() / RAND_MAX;
	return low + num  * (high - low);
}

double Random::GetRangeDouble(double low, double high)
{
	double num = (double)rand() / RAND_MAX;
	return low + num  * (high - low);
}

