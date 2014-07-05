#ifndef __ball_h
#define __ball_h

#include "SDL.h"
#include "Pos.h"
#include "collision.h"
#include "SDL_image.h"
#include "Jon_Constants.h"

#include <deque>

class Ball{
public:
	Ball(double xVel_, double yVel_, double damping, double x_, double y_);
	Collision * tick(int screenWidth, int screenHeight, Direction gravityDirection, double gravityStrength, int timeDiff);
	bool isStill();
	void bounce();
	void changePos(Pos xy);
	void changeVel(double x, double y);
	bool isWithin(Pos mouse);

	int getRadius() {return radius;}
	SDL_Texture * getFace() {return face;}
	double getX() {return p.x - radius;}
	double getY() {return p.y - radius;}
	
	Pos p;
	double xVel;
	double yVel;
	double damping;
	int radius;
private:
	
	int lastMovement;
	SDL_Texture *face;
	std::deque<Pos> historyPos;
};

#endif