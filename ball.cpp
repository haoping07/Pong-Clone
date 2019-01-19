#include <iostream>
#include "classes.h"
#include "constants.h"
#include "globals.h"
using namespace std;

ball::ball()
{
	//Initialize variables
	mPosX = SCREEN_WIDTH / 2;
	mPosY = SCREEN_HEIGHT / 2;
	mVelX = BALL_VEL;
	mVelY = BALL_VEL;
}

void ball::move(paddle& leftPaddle, paddle& rightPaddle)
{
	//Move the ball
	mPosX += mVelX;
	mPosY += mVelY;

	//Reflect the ball when hitting the Wall (screen boundary)
	if (mPosY + mVelY < 0)
	{
		mVelY *= -1;
		mPosY = 0;
	}
	if (mPosY + BALL_HEIGHT + mVelY > SCREEN_HEIGHT)
	{
		mVelY *= -1;
		mPosY = SCREEN_HEIGHT - BALL_HEIGHT;
	}

	//Check right paddle normal & edge collision
	if (checkRightCollision(rightPaddle))
	{
		cout << "right|" << endl;

		//If the ball hit the front side of paddle
		if (checkRightCollision(rightPaddle) == NORMAL)
		{
			cout << "NORMAL" << endl;
			mVelX *= -1;
			mPosX = rightPaddle.getPosX() - BALL_WIDTH;
		}

		//If the ball hit the bottom side of paddle
		else if (checkRightCollision(rightPaddle) == EDGE_BOTTOM)
		{
			cout << "EDGE_BOTTOM|" << endl;
			mVelY *= -1;
			mPosY = rightPaddle.getPosY() + rightPaddle.PADDLE_HEIGHT + 2;
		}

		//If the ball hit the top side of paddle
		else if (checkRightCollision(rightPaddle) == EDGE_TOP)
		{
			cout << "EDGE_TOP|" << endl;
			mVelY *= -1;
			mPosY = rightPaddle.getPosY() - BALL_HEIGHT - 2;
		}
	}
	//Check left paddle normal & edge collision
	if (checkLeftCollision(leftPaddle))
	{
		cout << "left|" << endl;

		//If the ball hit the front side of paddle
		if (checkLeftCollision(leftPaddle) == NORMAL)
		{
			cout << "NORMAL" << endl;
			mVelX *= -1;
			mPosX = leftPaddle.getPosX() + leftPaddle.PADDLE_WIDTH;
		}

		//If the ball hit the bottom side of paddle
		else if (checkLeftCollision(leftPaddle) == EDGE_BOTTOM)
		{
			cout << "EDGE_BOTTOM|" << endl;
			mVelY *= -1;
			mPosY = leftPaddle.getPosY() + leftPaddle.PADDLE_HEIGHT + 2;
		}

		//If the ball hit the top side of paddle
		else if (checkLeftCollision(leftPaddle) == EDGE_TOP)
		{
			cout << "EDGE_TOP|" << endl;
			mVelY *= -1;
			mPosY = leftPaddle.getPosY() - BALL_HEIGHT - 2;
		}
	}

	//Right paddle gets point when ball passes through left screen boundary
	if (mPosX < 0)
	{
		rightScore++;
		reset();
	}

	//Left paddle gets point when ball passes through right screen boundary
	if (mPosX + BALL_WIDTH > SCREEN_WIDTH)
	{
		leftScore++;
		reset();
	}
}

//Render the ball
void ball::render()
{
	gBall.render(mPosX, mPosY);
}

//Reset the ball
void ball::reset()
{
	mPosX = SCREEN_WIDTH / 2;
	mPosY = SCREEN_HEIGHT / 2;
	mVelX = BALL_VEL;
	mVelY = BALL_VEL;
}

//Check collision area between ball and paddle, then update the ball movement
collisionStat ball::checkLeftCollision(paddle& leftPaddle)
{
	int leftPaddleLeft = leftPaddle.getPosX();
	int leftPaddleRight = leftPaddle.getPosX() + leftPaddle.PADDLE_WIDTH;
	int leftPaddleTop = leftPaddle.getPosY();
	int leftPaddleBottom = leftPaddle.getPosY() + leftPaddle.PADDLE_HEIGHT;
	int ballLeft = mPosX;
	int ballRight = mPosX + BALL_WIDTH;
	int ballTop = mPosY;
	int ballBottom = mPosY + BALL_HEIGHT;

	if (!(ballLeft + mVelX < leftPaddleRight))
	{
		return NONE;
	}
	if (ballRight < leftPaddleLeft)
	{
		return NONE;
	}
	if (ballLeft > leftPaddleRight && ballLeft + mVelX < leftPaddleRight && ballTop + mVelY < leftPaddleBottom && ballBottom + mVelY > leftPaddleTop)
	{
		return NORMAL;
	}
	if (ballTop + mVelY < leftPaddleBottom && ballBottom > leftPaddleTop + leftPaddle.PADDLE_HEIGHT / 2 && ballLeft < leftPaddleRight)
	{
		return EDGE_BOTTOM;
	}
	if (ballBottom + mVelY > leftPaddleTop && ballTop < leftPaddleTop + leftPaddle.PADDLE_HEIGHT / 2 && ballLeft < leftPaddleRight)
	{
		return EDGE_TOP;
	}
	return NONE;
}

//Check collision area between ball and paddle, then update the ball movement
collisionStat ball::checkRightCollision(paddle& rightPaddle)
{
	int rightPaddleLeft = rightPaddle.getPosX();
	int rightPaddleRight = rightPaddle.getPosX() + rightPaddle.PADDLE_WIDTH;
	int rightPaddleTop = rightPaddle.getPosY();
	int rightPaddleBottom = rightPaddle.getPosY() + rightPaddle.PADDLE_HEIGHT;
	int ballLeft = mPosX;
	int ballRight = mPosX + BALL_WIDTH;
	int ballTop = mPosY;
	int ballBottom = mPosY + BALL_HEIGHT;

	if (!(ballRight + mVelX > rightPaddleLeft))
	{
		return NONE;
	}
	if (ballLeft > rightPaddleRight)
	{
		return NONE;
	}
	if (ballRight < rightPaddleLeft && ballRight + mVelX > rightPaddleLeft && ballTop + mVelY < rightPaddleBottom && ballBottom + mVelY > rightPaddleTop)
	{
		return NORMAL;
	}
	if (ballTop + mVelY < rightPaddleBottom && ballBottom + mVelY > rightPaddleTop + rightPaddle.PADDLE_HEIGHT / 2 && ballRight > rightPaddleLeft)
	{
		return EDGE_BOTTOM;
	}
	if (ballBottom + mVelY > rightPaddleTop && ballTop + mVelY < rightPaddleTop + rightPaddle.PADDLE_HEIGHT / 2 && ballRight > rightPaddleLeft)
	{
		return EDGE_TOP;
	}
	return NONE;
}