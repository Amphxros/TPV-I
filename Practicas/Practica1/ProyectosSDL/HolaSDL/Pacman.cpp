#include "Pacman.h"
#include "Game.h"

Pacman::Pacman(Point2D pos, Texture* texture, Game* game):
pos_(pos),texture_(texture),game_(game) {}

void Pacman::render()
{
	SDL_Rect dest;
	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = TAM_MAT;
	dest.h = TAM_MAT;

	texture_->renderFrame(dest,1,10);
}

void Pacman::update()
{
	//if(!colision con la matriz)
	pos_ = { (int)(pos_.getX() + dir_.getX()*TAM_MAT), (int)(pos_.getY() + dir_.getY()*TAM_MAT) };
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
			dir_ = { 0,-1 };
		}

		else if (event.key.keysym.sym == SDLK_DOWN)
		{
			dir_ = { 0,1 };
		}

		else if (event.key.keysym.sym == SDLK_LEFT) 
		{
			dir_ = {-1,0 };
		}

		else if (event.key.keysym.sym == SDLK_RIGHT)
		{
			dir_ = { 1,0 };
		}
		break;
	default:
		break;
	}
}
