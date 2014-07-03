/*
Author: Jonathan Worobey
Date: 6/2/2014
*/

//SDL includes
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
//STD lib
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <iostream>//Development only
//Angleball includes
#include "world.h"
#include "ball.h"
#include "Jon_Constants.h"

SDL_Window *window = NULL;

SDL_Event event;

SDL_Renderer *renderer = NULL;

TTF_Font *font = NULL;

SDL_Texture* surfaceTexture = NULL;
SDL_Texture* ballTexture = NULL;
SDL_Texture* textTexture = NULL;

SDL_Surface* textSurface = NULL;

SDL_Color textColor = {0, 0, 0};
SDL_Color textBackgroundColor = {255,255,255};

World *w = NULL;

int screenWidth = NULL;
int screenHeight = NULL;

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

	void apply_surface(int x, int y, int w, int h, SDL_Texture *source, SDL_Renderer *destination)
	{
		SDL_Rect offset;

		offset.x = x;
		offset.y = y;
		offset.w = w;
		offset.h = h;

		SDL_RenderCopy(destination, source, NULL, &offset);
	}

}

bool init()
{
	window = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		return false;

	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ); // testing
	
	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);
	screenWidth = current.w;
	screenHeight = current.h;
	screenHeight = 640;
	screenWidth = 640;

	window = SDL_CreateWindow("Angleball 3.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);//2.0

	if(window == NULL)
		return false;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	if(renderer == NULL)
		return false;

	SDL_SetRenderDrawColor(renderer, 0, 55, 0, 255);

	int imgFlags = IMG_INIT_PNG;
	if(!IMG_Init(imgFlags) & imgFlags)
		return false;

	if(TTF_Init() < 0)
		return false;

	return true;
}
bool load_files()
{
	ballTexture = Jon_SDL_functions::load_image("ball.png", 0, 0, 0);

	font = TTF_OpenFont("Scada-Regular.ttf", 28);
	if(font == NULL)
		return false;

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
	SDL_DestroyTexture(textTexture);
	textTexture = NULL;

	SDL_FreeSurface(textSurface);
	textSurface = NULL;

	TTF_CloseFont(font);
	font = NULL;

	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
void fps_counter(World *w)
{

}
int main(int argc, char *args[])
{
	quit = false;
	int milli_between_frames = floor(1000.0/Jon_Constants::FRAMES_PER_SECOND);
	int stringWidth =  0, stringHeight = 0;
	std::stringstream ss;
	std::string text;
	Uint32 timeSinceLastFpsCheck = 0;
	int x = 0;

	if(init() == false)
		return 1;
	
	if(load_files() == false)
		return 1;

	w = new World(DOWN, screenWidth, screenHeight, 500);
	
	Uint32 oldTime, curTime;
	oldTime = SDL_GetTicks();
	while(quit == false)
	{
		
		while(SDL_PollEvent(&event))
		{
			handle_events();

			if(event.type == SDL_QUIT)
				quit = true;
		}
		
		SDL_RenderClear(renderer);

		
		if(w->getFrameNum() % 100 == 0)// || w->getFrameNum() == 0)
		{
			/*ss << floor((1.0/(w->getCurrentTime() - timeSinceLastFpsCheck)) * 1000 * 100) << std::endl << "Hello, World!" << std::endl;*/
			ss << floor((1.0/(oldTime - timeSinceLastFpsCheck)) * 1000 * 100) << std::endl << "Hello, World!" << std::endl;
			/*timeSinceLastFpsCheck = w->getCurrentTime();*/
			timeSinceLastFpsCheck = oldTime;
			text = ss.str();
			ss.str("");
			SDL_FreeSurface(textSurface);
			SDL_DestroyTexture(textTexture);
			textSurface = NULL;
			textTexture = NULL;
			textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
			textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
			TTF_SizeText(font, text.c_str(), &stringWidth, &stringHeight);
		}
		Jon_SDL_functions::apply_surface(50, 50, stringWidth, stringHeight, textTexture, renderer);
		int t = SDL_GetTicks()-oldTime;
		//std::cout << t << std::endl;
		w->newFrame(t);
		oldTime += t;


		//if(w->getDiffTime() < milli_between_frames)
		if(t < milli_between_frames)
		{
			SDL_Delay(milli_between_frames - t);
		}

		w->showTextures(renderer);

		SDL_RenderPresent(renderer);


		
	}

	clean_up();

	return 0;
}