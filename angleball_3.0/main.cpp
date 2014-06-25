/*
Author: Jonathan Worobey
Date: 6/2/2014
*/

//SDL includes
#include "SDL.h"
#include "SDL_image.h"
//#include "SDL_ttf.h" pre 2.0
//STD lib
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>//Development only
//Angleball includes
#include "world.h"
#include "ball.h"
#include "Jon_Constants.h"

SDL_Window *window = NULL;

SDL_Event event;

SDL_Renderer* renderer;

SDL_Texture* surfaceTexture;
SDL_Texture* ballTexture = NULL;

World *w = NULL;
int screenWidth;
int screenHeight;

bool quit;

double symmetric_round(double x)
{
	if(x > 0)
		return floor(x + 0.5);
	else
		return ceil(x - 0.5);
}

namespace Jon_SDL_functions
{
	SDL_Texture * load_image(char s[], int r, int g, int b)
	{
		SDL_Surface *loadedImage = NULL;
		SDL_Texture *optimizedImage = NULL;

		loadedImage = IMG_Load(s);

		if(loadedImage != NULL)
		{
			Uint32 colorkey = SDL_MapRGB(loadedImage->format, r,g,b);
			SDL_SetColorKey(loadedImage, SDL_TRUE, colorkey);

			optimizedImage = SDL_CreateTextureFromSurface(renderer, loadedImage);

			SDL_FreeSurface(loadedImage);
		}
	
		return optimizedImage;
	}

	SDL_Texture * load_image(char s[])
	{
		SDL_Surface *loadedImage = NULL;
		SDL_Texture *optimizedImage = NULL;

		loadedImage = IMG_Load(s);

		if(loadedImage != NULL)
		{
			optimizedImage = SDL_CreateTextureFromSurface(renderer, loadedImage);

			SDL_FreeSurface(loadedImage);	
		}
	
		return optimizedImage;
	}

	void apply_surface(int x, int y, SDL_Texture *source, SDL_Renderer *destination)
	{
		SDL_Rect offset;

		offset.x = x;
		offset.y = y;
		offset.w = 32;
		offset.h = 32;

		SDL_RenderCopy(destination, source, NULL, &offset);
	}

}

bool init()
{
	window = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		return false;
	
	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);
	screenWidth = current.w;
	screenHeight = current.h;

	window = SDL_CreateWindow("Angleball 3.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_FULLSCREEN);//2.0

	if(window == NULL)
		return false;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	if(renderer == NULL)
		return false;

	SDL_SetRenderDrawColor(renderer, 0, 55, 0, 255);

	int imgFlags = IMG_INIT_PNG;
	if(!IMG_Init(imgFlags) & imgFlags)
		return false;

	return true;
}
bool load_files()
{
	ballTexture = Jon_SDL_functions::load_image("ball.png", 0, 0, 0);

	return true;
}
void handle_events()
{
	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		if(event.button.button == SDL_BUTTON_LEFT)
		{
			w->addTemp(Pos(event.button.x, event.button.y));
		}
		else if(event.button.button == SDL_BUTTON_RIGHT)
		{
			w->deleteBall(Pos(event.button.x, event.button.y));
		}
	}
	if(event.type == SDL_MOUSEBUTTONUP)
	{
		if(event.button.button == SDL_BUTTON_LEFT)
		{
			Ball * ptr;
			double xVel = (w->getBeginMousePos().x - event.button.x) * 10;
			double yVel = (w->getBeginMousePos().y - event.button.y) * 10;
			if(w->deleteTemp())
			{
				ptr = new Ball(xVel, yVel, 0.7, event.button.x, event.button.y);
				w->addBall(ptr);
			}
		}
	}
	if(event.type == SDL_MOUSEMOTION)
	{
		if(w->tempIsOnTop() == true)
		{
			w->moveTempBall(Pos(event.motion.x, event.motion.y));
		}
	}
	if(event.type == SDL_KEYDOWN)
	{
		if(event.key.keysym.sym == SDLK_ESCAPE)
			quit = true;
	}
	if(event.type == SDL_QUIT)
		quit = true;
}
void clean_up()
{
	SDL_DestroyTexture(ballTexture);
	ballTexture = NULL;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	IMG_Quit();
	SDL_Quit();
}
int main(int argc, char *args[])
{
	quit = false;
	int milli_between_frames = floor(1000.0/Jon_Constants::FRAMES_PER_SECOND);
	Uint32 mainLastTime = SDL_GetTicks();
	int diff;
	if(init() == false)
		return 1;
	
	if(load_files() == false)
		return 1;

	w = new World(DOWN, screenWidth, screenHeight, 500);
	
	while(quit == false)
	{
		while(SDL_PollEvent(&event))
		{
			handle_events();

			if(event.type == SDL_QUIT)
				quit = true;
		}

		SDL_RenderClear(renderer);
		w->newFrame();
		w->showTextures(renderer);
		SDL_RenderPresent(renderer);

		/*diff = SDL_GetTicks() - mainLastTime;
		if(diff < milli_between_frames)
		{
			SDL_Delay(milli_between_frames - diff);
		}
		mainLastTime = SDL_GetTicks();*/
	}

	clean_up();

	return 0;
}