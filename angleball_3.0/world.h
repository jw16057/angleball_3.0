#ifndef __world_h
#define __world_h
#include <vector>
#include "ball.h"
#include "Pos.h"
#include "collision.h"
#include "Jon_Constants.h"
#include "timer.h"

class World{
public:
	World(Direction gravityDirection_, int screenWidth_, int screenHeight, double gravityStrength_ = 0.01);
	void newFrame(); // Call this to advance the world one tick
	void addBall(Ball * x);
	void addTemp(Pos p);
	void deleteBall(Pos p);
	bool deleteTemp();
	void showTextures(SDL_Renderer * s);
	void moveTempBall(Pos p);
	Collision * popCollision();
	void setDeleteKeyPressed(Pos mousePos);
	void resetDeleteKeyPressed();

	Direction getGravityDirection() {return gravityDirection;}
	double getGravityStrength() {return gravityStrength;}
	int getNumberOfBalls() {return balls.size();}
	Pos getBeginMousePos() {return beginMousePos;}
	Uint32 getFrameNum() {return frameNum;}
	const bool tempIsOnTop() {return tempOnTop;}
private:
	int screenWidth;
	int screenHeight;
	Uint32 frameNum;
	Timer speedControl;
	bool tempOnTop;
	bool poppedOnTop;
	bool deleteKeyPressed;
	Pos beginMousePos;
	Pos currentMousePos;

	Direction gravityDirection;
	double gravityStrength;

	std::vector <Ball> balls;
	std::vector <Collision *> collisions;
};

#endif
