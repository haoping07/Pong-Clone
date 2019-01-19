#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include "classes.h"

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;

extern LTexture gPaddle;
extern LTexture gBall;
extern LTexture gBG;
extern LTexture gScoreTextLeft;
extern LTexture gScoreTextRight;


#endif
