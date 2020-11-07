#include "Ghost.h"
#include "Game.h"
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
	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = TAM_MAT;
	dest.h = TAM_MAT;
	//if (pacman hamburgueseado) -> renderiza frames azules
	//else los del color correspondiente
	texture_->renderFrame(dest,GHOST_ROW,GHOST_COL);
}

void Ghost::update()
{
	///while (colision inminente(this)) genera dir aleatoria
	//if(colisionPacmanFantasma && pacman ha comiu hamburguesas)
	pos_ = { (int)(pos_.getX() + (dir_.getX()*TAM_MAT)), (int)(pos_.getY() + (dir_.getY()*TAM_MAT)) };
}
