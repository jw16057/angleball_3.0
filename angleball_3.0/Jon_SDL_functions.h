#ifndef __Jon_SDL_functions_h
#define __Jon_SDL_functions_h

#include "SDL.h"

namespace Jon_SDL_functions
{
	SDL_Texture * load_image(char s[], int r, int g, int b);
	SDL_Texture * load_image(char s[]);
	void apply_surface(int x, int y, int w, int h, SDL_Texture *source, SDL_Renderer *destination);
}

#endif