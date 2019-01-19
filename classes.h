#ifndef CLASSES_H
#define CLASSES_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
using namespace std;

//Collision stats
enum collisionStat {
	NONE = 0,
	EDGE_TOP,
	EDGE_BOTTOM,
	NORMAL
};

//Texture handler
class LTexture
{
public:
	LTexture();
	~LTexture();
	bool loadFromFile(string path);
	bool loadFromRenderedText(string str, SDL_Color textColor = { 255, 255, 255 });
	void setColor(Uint8 red, Uint8 blue, Uint8 green);
	void setAlpha(Uint8 alpha);
	void setBlendMode(SDL_BlendMode blending);
	void render(int x, int y, SDL_Rect* clip = NULL);
	void free();
	int getWidth();
	int getHeight();
private:
	SDL_Texture* mTexture;
	int mWidth, mHeight;
};

class paddle
{
public:
	paddle();
	static const int PADDLE_WIDTH = 13;
	static const int PADDLE_HEIGHT = 64;
	static const int PADDLE_VEL = 10;
	void move();
	void render();
	void handleEventForLeft(SDL_Event& e);
	void handleEventForRight(SDL_Event& e);
	void initLeft();
	void initRight();
	int getPosX();
	int getPosY();
private:
	int mPosX, mPosY;
	int mVelY;
};

class ball
{
public:
	ball();
	static const int BALL_WIDTH = 10;
	static const int BALL_HEIGHT = 10;
	static const int BALL_VEL = 4;
	collisionStat checkLeftCollision(paddle& leftPaddle);
	collisionStat checkRightCollision(paddle& rightPaddle);
	int mVelX, mVelY;
	int leftScore = 0, rightScore = 0;
	void reset();
	void move(paddle& leftPaddle, paddle& rightPaddle);
	void render();
private:
	int mPosX, mPosY;
};

#endif
