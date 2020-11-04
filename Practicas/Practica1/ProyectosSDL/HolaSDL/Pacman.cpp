#include "Pacman.h"
Pacman::Pacman(Point2D pos, Vector2D speed,double width,double height, Texture* texture, Game* game):
pos_(pos), speed_(speed), width_(width), height_(height),texture_(texture),game_(game){

}

void Pacman::render() const
{
	SDL_Rect dest;
	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = width_;
	dest.h = height_;

	texture_->renderFrame(dest,1,10);
}

void Pacman::update()
{
	//if(!colision con la matriz)
	pos_ = { pos_.getX() + dir_.getX(), pos_.getY()+ dir_.getY() };
	//if colisionconHamburguesa -> bool nyom true
	//if nyom && ha pasao tiempo de cooldown bool nyom false

}

void Pacman::handleEvents(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_UP)
		{
			dir_ = { 0,-speed_.getY() };
		}

		else if (event.key.keysym.sym == SDLK_DOWN)
		{
			dir_ = { 0,speed_.getY() };
		}

		else if (event.key.keysym.sym == SDLK_LEFT) 
		{
			dir_ = {-speed_.getY(),0 };
		}

		else if (event.key.keysym.sym == SDLK_RIGHT)
		{
			dir_ = { 0,speed_.getY() };
		}
		break;
	default:
		break;
	}
}
