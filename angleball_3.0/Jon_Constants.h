#ifndef __Jon_Constants_h
#define __Jon_Constants_h


extern SDL_Texture* ballTexture;

enum Direction {UP, DOWN, LEFT, RIGHT, NONE};

namespace Jon_Constants
{
const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;
const int SCREEN_BPP = 32;
const double DEFAULT_DAMPING = 0.7;
const int FRAMES_PER_SECOND = 100;
}

#endif