#include "World.h"
#include "SDL.h"
#include "SDL_image.h"
//#include "SDL_ttf.h" pre 2.0
#include "Jon_Constants.h"
#include "Jon_SDL_functions.h"
#include "Pos.h"
#include <ctime>
#include <iostream>

World::World(Direction gravityDirection_, int screenWidth_, int screenHeight_, double gravityStrength_)
{
	tempOnTop = false;
	gravityDirection = gravityDirection_;
	gravityStrength = gravityStrength_;
	screenWidth = screenWidth_;
	screenHeight = screenHeight_;
	srand((int) time(0));
	frameNum = 0;
}
void World::newFrame() // Call this to advance the world one tick
{
	int x = balls.size()-1;
	Collision * returnedValue;
	if(tempOnTop)
			x--;
	while(x >= 0)
	{
		returnedValue = balls[x].tick(screenWidth, screenHeight, gravityDirection, gravityStrength, speedControl.getTime());
		
		if(returnedValue != NULL)
			collisions.push_back(returnedValue);

		x--;
	}
	speedControl.reset();
	speedControl.start();

	frameNum++;
}
void World::addBall(Ball * x)
{
	balls.push_back(*x);
}
void World::addTemp(Pos p)
{
	if(!tempOnTop)
	{
		beginMousePos = p;
		currentMousePos = p;
		balls.push_back(Ball(0,0,0, p.x, p.y));
		tempOnTop = true;
	}
}
bool World::deleteTemp()
{
	if(tempOnTop)
	{
		balls.pop_back();

		beginMousePos.x = 0;
		beginMousePos.y = 0;
		currentMousePos.x = 0;
		currentMousePos.y = 0;

		tempOnTop = false;
		return true;
	}
	else
		return false;
}
void World::deleteBall(Pos p)
{
	int x = balls.size() - 1;
	if(tempOnTop)
			x--;
	while(x >= 0)
	{
		if(balls[x].isWithin(p))
			balls.erase(balls.begin() + x);
		x--;
	}
}
void World::showTextures(SDL_Renderer * s)
{
	if(tempOnTop)
	{
		SDL_SetRenderDrawColor(s, 255, 0, 0, 255);
		SDL_RenderDrawLine(s, beginMousePos.x, beginMousePos.y, currentMousePos.x, currentMousePos.y);
		SDL_SetRenderDrawColor(s, 0, 55, 0, 255);
	}
	for(int x = 0; x < getNumberOfBalls(); x++)
	{
		Jon_SDL_functions::apply_surface((int) floor(balls[x].getX()), (int) ceil(balls[x].getY()), 32, 32, balls[x].getFace(), s);
	}
}
void World::moveTempBall(Pos p)
{
	if(tempOnTop)
	{
		currentMousePos = p;
		balls.back().changePos(p);
	}
}