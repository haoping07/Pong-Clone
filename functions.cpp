#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "functions.h"
#include "globals.h"
#include "constants.h"
using namespace std;

//Initialize SDL
bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL_Init(SDL_INIT_VIDEO) failed: " << SDL_GetError() << endl;
	}
	else
	{
		gWindow = SDL_CreateWindow("Pong game clone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			cout << "SDL_CreateWindow(...) failed: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				cout << "SDL_CreateRenderer(...) failed: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "IMG_Init(...) failed: " << SDL_GetError() << endl;
					success = false;
				}
				if (TTF_Init() == -1)
				{
					cout << "TTF init failed" << TTF_GetError() << endl;
					success = false;
				}
			}
		}
	}
	return success;
}

//Load Media
bool loadMedia()
{
	bool success = true;
	if (!gPaddle.loadFromFile("resources/paddle.png"))
	{
		cout << "Load paddle.png failed" << endl;
		success = false;
	}
	if (!gBall.loadFromFile("resources/ball.png"))
	{
		cout << "Load ball.png failed" << endl;
		success = false;
	}
	if (!gBG.loadFromFile("resources/bg.png"))
	{
		cout << "Load bg.png failed" << endl;
		success = false;
	}
	gFont = TTF_OpenFont("resources/OpenSans-Bold.ttf", 50);
	if (gFont == NULL)
	{
		cout << "OpenSans-Bold.ttf cannot be found" << TTF_GetError() << endl;
		success = false;
	}
	else
	{
		if (!gScoreTextLeft.loadFromRenderedText("0"))
		{
			cout << "load score text failed" << endl;
			success = false;
		}
		if (!gScoreTextRight.loadFromRenderedText("0"))
		{
			cout << "load score text failed" << endl;
			success = false;
		}

	}
	return success;
}

//Free the memory
void close()
{
	gPaddle.free();
	gBall.free();
	gScoreTextLeft.free();
	gScoreTextRight.free();
	TTF_CloseFont(gFont);
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gWindow = NULL;
	gRenderer = NULL;
	gFont = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
