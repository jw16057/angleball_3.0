#ifndef __ball_h
#define __ball_h

#include "SDL.h"
#include "Pos.h"
#include "SDL_image.h"

#include <deque>

class Ball{
public:
	Ball(double xVel_, double yVel_, double xAccel_, double yAccel_, double damping, double x_, double y_);
	void tick(int screenWidth, int screenHeight);
	bool isStill();
	void bounce();
	void changePos(Pos xy);
	void changeVel(double x, double y);

	double getX() {return p.x;}
	double getY() {return p.y;}
	int getRadius() {return radius;}
	SDL_Texture * getFace() {return face;};
private:
	Pos p;
	int lastMovement;
	int radius;
	double xVel;
	double yVel;
	double xAccel;
	double yAccel;
	double damping;
	SDL_Texture *face;
	std::deque<Pos> historyPos;
};

#endif