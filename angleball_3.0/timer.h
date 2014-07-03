#ifndef __timer_h
#define __timer_h

#include "SDL.h"
#include "Pos.h"
#include "SDL_image.h"
#include "Jon_Constants.h"

class Timer{
public:
	Timer();
	void startTimer();
	Uint32 pauseTimer();
	void resetTimer();
	Uint32 getTime();
private:
	Uint32 startTime;
	Uint32 totalAmountOfPausedTime;//amount of time the timer has been paused
	Uint32 tempPausedTime;//time between each pause

	bool paused;
};

#endif