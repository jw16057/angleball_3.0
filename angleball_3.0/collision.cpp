#include "collision.h"
#include <math.h>


Collision::Collision(double xVel_, double yVel_)
{
	xVel = xVel_;
	yVel = yVel_;
}

double Collision::GetVelocity()
{
	return sqrt(xVel*xVel + yVel*yVel);
}