#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "globals.h"
#include "classes.h"
using namespace std;

LTexture::LTexture()
{
	//Initialize variables
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Free the memory
	free();
}

//Load the image
bool LTexture::loadFromFile(string path)
{
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		cout << "Load Surface failed: " << SDL_GetError() << endl;
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			cout << "Create Texture From Surface failed: " << SDL_GetError() << endl;
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}

//Load text
bool LTexture::loadFromRenderedText(string str, SDL_Color textColor)
{
	free();
	SDL_Texture* newTextTexture = NULL;
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, str.c_str(), textColor);
	if (textSurface == NULL)
	{
		cout << "Render text failed" << endl;
	}
	else
	{
		newTextTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (newTextTexture == NULL)
		{
			cout << "Create Texture From Surface failed (text)" << endl;
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	mTexture = newTextTexture;
	return mTexture != NULL;
}

//Set the color
void LTexture::setColor(Uint8 red, Uint8 blue, Uint8 green)
{
	SDL_SetTextureColorMod(mTexture, red, blue, green);
}

//Set blend mode
void LTexture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(mTexture, blending);
}

//Set alpha mod
void LTexture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

//Render the texture
void LTexture::render(int x, int y, SDL_Rect* clip)
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

//Free the texture
void LTexture::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

//Get texture width
int LTexture::getWidth()
{
	return mWidth;
}

//Get texture height
int LTexture::getHeight()
{
	return mHeight;
}
