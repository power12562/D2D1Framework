#include "TimeSystem.h"

namespace TimeSystem
{
	QPCTime Time;
}

MyTime::MyTime()
{
	deltaTime_ms = 0;
	previousTime = currentTime = GetTickCount64();
}

void MyTime::UpdateTime()
{
	previousTime = currentTime;
	currentTime = GetTickCount64();
	deltaTime_ms = currentTime - previousTime;
}

QPCTime::QPCTime() :
	timeScale(1.0f)
{
	previousTime = { 0 };
	currentTime = { 0 };
	frequency = { 0 };
	deltaTime_ms = 0.f;

	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&previousTime);
}

void QPCTime::UpdateTime()
{
	previousTime = currentTime;
	QueryPerformanceCounter(&currentTime);

	deltaTime_ms = float(currentTime.QuadPart - previousTime.QuadPart) / float(frequency.QuadPart / 1000.0); //ms
}

float QPCTime::GetDeltatime_ms(bool isScale) const
{
	if (isScale)
	{
		return deltaTime_ms * timeScale;
	}
	else
	{
		return deltaTime_ms;
	}
	
}
