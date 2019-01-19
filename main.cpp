#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cmath>
#include <string>
#include "globals.h"
#include "classes.h"
#include "functions.h"
#include "constants.h"
using namespace std;

int main(int argc, char* args[])
{
	if (!init())
	{
		cout << "Initialize SDL failed!" << endl;
	}
	else
	{
		if (!loadMedia())
		{
			cout << "Load Media failed!" << endl;
		}
		else
		{
			bool quit = false;
			SDL_Event e;
			paddle paddleLeft, paddleRight;
			paddleLeft.initLeft();
			paddleRight.initRight();
			ball ball;
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					//Detect keyboard input
					paddleLeft.handleEventForLeft(e);
					paddleRight.handleEventForRight(e);
				}

				//Move the paddles
				paddleLeft.move();
				paddleRight.move();
				ball.move(paddleLeft, paddleRight);

				//Clear and reset render before render
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				gBG.render(0, 0);

				//Calculate the scores
				gScoreTextLeft.loadFromRenderedText(to_string(ball.leftScore));
				gScoreTextRight.loadFromRenderedText(to_string(ball.rightScore));

				//Render the score board
				gScoreTextLeft.render(SCREEN_WIDTH / 2 - 140, SCREEN_HEIGHT / 7);
				gScoreTextRight.render(SCREEN_WIDTH / 2 + 120, SCREEN_HEIGHT / 7);

				//Render paddles
				paddleLeft.render();
				paddleRight.render();

				//Render ball
				ball.render();

				//Show everything
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	close();
	return 0;
}
