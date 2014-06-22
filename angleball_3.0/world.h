#ifndef __world_h
#define __world_h
#include <vector>
#include "ball.h"
#include "Pos.h"

enum Direction {UP, DOWN, LEFT, RIGHT, NONE};

class World{
public:
	World(Direction gravityDirection_, int screenWidth_, int screenHeight, double gravityStrength_ = 0.01);
	void newFrame(); // Call this to advance the world one tick
	void addBall(Ball * x);
	void addTemp(Pos p);
	bool deleteBall(Pos p);
	bool deleteTemp();
	void showTextures(SDL_Renderer * s);
	void moveTempBall(Pos p);

	Direction getGravityDirection() {return gravityDirection;}
	double getGravityStrength() {return gravityStrength;}
	int getNumberOfBalls() {return balls.size();}
	Pos getBeginMousePos() {return beginMousePos;}
	const bool tempIsOnTop() {return tempOnTop;}
private:
	int screenWidth;
	int screenHeight;
	long frameNum;
	bool tempOnTop;
	Pos beginMousePos;
	Pos currentMousePos;

	Direction gravityDirection;
	double gravityStrength;

	std::vector <Ball> balls;
};

#endif
