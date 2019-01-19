#include <SDL.h>
#include "globals.h"
#include "constants.h"
#include "classes.h"

paddle::paddle()
{
	//Initialize variables
	mPosX = 0;
	mPosY = 0;
	mVelY = 0;
}

//Limit the paddles inside the screen
void paddle::move()
{
	mPosY += mVelY;
	if (mPosY < 0 || mPosY + PADDLE_HEIGHT > SCREEN_HEIGHT)
	{
		mPosY -= mVelY;
	}
}

//Render paddles
void paddle::render()
{
	gPaddle.render(mPosX, mPosY);
}

//Keypress event for left paddle
void paddle::handleEventForLeft(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			mVelY -= PADDLE_VEL;
			break;
		case SDLK_s:
			mVelY += PADDLE_VEL;
			break;
		}
	}
	if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			mVelY += PADDLE_VEL;
			break;
		case SDLK_s:
			mVelY -= PADDLE_VEL;
			break;
		}
	}
}

//Keypress event for right paddle
void paddle::handleEventForRight(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			mVelY -= PADDLE_VEL;
			break;
		case SDLK_DOWN:
			mVelY += PADDLE_VEL;
			break;
		}
	}
	if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			mVelY += PADDLE_VEL;
			break;
		case SDLK_DOWN:
			mVelY -= PADDLE_VEL;
			break;
		}
	}
}

//Reset the left padddle
void paddle::initLeft()
{
	mPosX = 20;
	mPosY = SCREEN_HEIGHT / 2;
}

//Reset the right padddle
void paddle::initRight()
{
	mPosX = SCREEN_WIDTH - 40;
	mPosY = SCREEN_HEIGHT / 2;
}

//Get x position of paddle
int paddle::getPosX()
{
	return mPosX;
}

//Get y position of paddle
int paddle::getPosY()
{
	return mPosY;
}