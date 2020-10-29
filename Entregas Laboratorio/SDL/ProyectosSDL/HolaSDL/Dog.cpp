#include "Dog.h"

Dog::Dog(): 
	pos_x(0),pos_y(0),width(0),height(0),texture_(nullptr)
{
	throw "Perro muerto";
}

Dog::Dog(int posX, int posY, int speed, int width, int height, Texture* texture):
pos_x(posX),pos_y(posY),width(width),height(height),texture_(texture),speed(speed) { }

void Dog::render()
{
	SDL_Rect dest;
	dest.x = pos_x;
	dest.y = pos_y;
	dest.w = width;
	dest.h = height;

	frame_ = width / 6 * (SDL_GetTicks() / 60 % 6);

	texture_->render(dest, SDL_FLIP_NONE);
	texture_->renderFrame(dest, 1, frame_,0, SDL_FLIP_NONE);
}

void Dog::update()
{
	pos_x+=speed;

	if (pos_x - width>= 600) {
		pos_x = 0;
	}
}
