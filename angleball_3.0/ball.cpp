#ifndef __ball_cpp
#define __ball_cpp

#include "world.h"
#include "ball.h"
#include "Pos.h"
#include "Jon_Constants.h"
#include "Jon_SDL_functions.h"



double symmetric_round(double);

Ball::Ball(double xVel_, double yVel_, double damping_, double x_, double y_)
{
	radius = 16;
	lastMovement = 0;
	p.x = x_ - radius;
	p.y = y_ - radius;

	historyPos.push_back(Pos(p.x, p.y));

	xVel = xVel_;
	yVel = yVel_;
	damping = damping_;

	face = ballTexture;

	if(face == NULL)
		exit(1);
}

void Ball::tick(int screenWidth, int screenHeight, Direction gravityDirection, double gravityStrength, int timeDiff)
{
	double seconds = timeDiff/1000.0;
	p.x += xVel * seconds;
	p.y += yVel * seconds;

	switch(gravityDirection)
	{
	case UP:
		yVel -= gravityStrength * seconds;
		break;
	case DOWN:
		yVel += gravityStrength * seconds;
		break;
	case LEFT:
		xVel += gravityStrength * seconds;
		break;
	case RIGHT:
		xVel -= gravityStrength * seconds;
		break;
	}

	if(p.y > screenHeight-radius*2)
	{
		int displacement = (int) p.y - (screenHeight-radius*2);
		p.y = (screenHeight-radius*2) - displacement;
		yVel = -yVel * damping;
		xVel = xVel * damping;
	}
	if(p.x > screenWidth-radius*2)
	{
		int displacement = (int) p.x - (screenWidth-radius*2);
		p.x = (screenWidth-radius*2) - displacement;
		yVel = yVel * damping;
		xVel = -xVel * damping;
		
	}
	if(p.x < 0)
	{
		p.x = -p.x;
		yVel = yVel * damping;
		xVel = -xVel * damping;
	}

	Pos current(p.x, p.y);

	if(current == historyPos.back())
		lastMovement++;
	else
		lastMovement = 0;

	historyPos.push_back(current);
	if(historyPos.size() >= 5)
		historyPos.pop_front();
}

bool Ball::isStill()
{
	return false; ////////////////////////////////////////NOTICE
	if(lastMovement > 10)
		return true;
	else
		return false;
}

void Ball::bounce()
{
	xVel = rand()%5;
	yVel = rand()%5;
	if(rand() < RAND_MAX/2)
		xVel = -xVel;
	//if(rand() < RAND_MAX/2)
		yVel = -yVel;
}

void Ball::changePos(Pos xy)/// Used for mouse commands
{
	p.x = xy.x - radius;
	p.y = xy.y - radius;
}

#endif