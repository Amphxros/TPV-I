#include "Ghost.h"
#include "Game.h"
#include <cstdlib>
Ghost::Ghost(Point2D pos, Texture* Texture, Game* game, int color):
	pos_(pos),texture_(Texture), game_(game),color_(color)
{
	dir_ = { 0,-1 };
}

Ghost::~Ghost()
{
	delete texture_;
}

void Ghost::render()
{
	SDL_Rect dest;
	dest.x = pos_.getX()* TAM_MAT;
	dest.y = pos_.getY()*TAM_MAT;
	dest.w = TAM_MAT;
	dest.h = TAM_MAT;
	if (game_->isPacmanNyom()) 
		texture_->renderFrame(dest, 0, 13);
	else
		texture_->renderFrame(dest, 0, 2 * color_);
}

void Ghost::update()
{
	Vector2D aux = pos_ + dir_;

	int direccion=0;
	
	do {
		direccion = rand() % 4;	//Genera entre 0 y 3
		switch (direccion)
		{
		case 0:
			dir_ = { 0, -1 };
			break;
		case 1:
			dir_ = { 0, 1 };
			break;
		case 2:
			dir_ = { 1, 0 };
			break;
		case 3:
			dir_ = { -1, 0 };
			break;
		default:
			break;
		}

		aux = { (int)(pos_.getX() + dir_.getX()), (int)(pos_.getY() + dir_.getY()) };
	} while (game_->check_collisionofGhost(aux));
	pos_ = aux;


	//if(colisionPacmanFantasma && pacman ha comiu hamburguesas)
	//pos_ = { (int)(pos_.getX() + (dir_.getX()*TAM_MAT)), (int)(pos_.getY() + (dir_.getY()*TAM_MAT)) };
}
