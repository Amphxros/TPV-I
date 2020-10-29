#pragma once
#include "Texture.h"
class Dog
{
public:
	Dog();
	Dog(int posX, int posY,int speed, int width, int height, Texture* texture);

	void render();
	void update();
private:
	Texture* texture_;
	int pos_x, pos_y;
	int width, height;
	int frame_=0;
	int speed = 0;
};

