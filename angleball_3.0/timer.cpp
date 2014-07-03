#include "timer.h"

Timer::Timer()
{
	reset();
}
void Timer::start()
{
	if(paused)
	{
		paused = false;
		totalAmountOfPausedTime += SDL_GetTicks() - tempPausedTime;
		tempPausedTime = 0;
	}
}
void Timer::pause()
{
	if(!paused)
	{
		paused = true;
		tempPausedTime = SDL_GetTicks();
	}
}
void Timer::reset()
{
	startTime = SDL_GetTicks();
	totalAmountOfPausedTime = 0;
	tempPausedTime = 0;

	paused = true;
	tempPausedTime = startTime;
}
Uint32 Timer::getTime()
{
	return (SDL_GetTicks() - startTime) - totalAmountOfPausedTime;
}