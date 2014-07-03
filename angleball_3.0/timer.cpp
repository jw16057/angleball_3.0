#include "timer.h"

Timer::Timer()
{
	startTime = SDL_GetTicks();
	totalAmountOfPausedTime = 0;
	tempPausedTime = 0;

	paused = true;
	tempPausedTime = startTime;
}
void Timer::startTimer()
{
	paused = false;
	totalAmountOfPausedTime += SDL_GetTicks() - tempPausedTime;
	tempPausedTime = 0;
}
Uint32 Timer::pauseTimer()
{
	paused = true;
	tempPausedTime = SDL_GetTicks();
}
void Timer::resetTimer()
{
	Timer();
}
Uint32 Timer::getTime()
{
	return (SDL_GetTicks() - startTime) - totalAmountOfPausedTime;
}