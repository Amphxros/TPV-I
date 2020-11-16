#include "Pacman.h"
#include "Game.h"

Pacman::Pacman(Point2D pos, Texture* texture, Game* game):
pos_(pos),texture_(texture),game_(game) {
	dir_ = dirs_[directions::LEFT];;
}

Pacman::~Pacman()
{
	delete texture_; texture_ = nullptr;
	delete game_; game_ = nullptr;
}

void Pacman::render()
{
	SDL_Rect dest;
	dest.x = pos_.getX()*TAM_MAT;
	dest.y = pos_.getY()*TAM_MAT;
	dest.w = TAM_MAT;
	dest.h = TAM_MAT;

	texture_->renderFrame(dest,0,11);
}

void Pacman::update()
{
	//Vector2D aux = { (int)(pos_.getX() + dir_.getX()), (int)(pos_.getY() + dir_.getY()) };
	Vector2D aux = getPos();

	if (game_->check_collisionGhostPacman()) {
		

	}	
	if (!game_->check_collisionofPacman(aux)) {
		//aqui se mueve
		pos_ = aux;	
		if (pos_.getX() <= 0) {
			pos_ = {(int) game_->getSwapX(), (int)pos_.getY() };
		}
		else if (pos_.getX() >= game_->getSwapX()) {
			pos_ = { 0, (int)pos_.getY() };
		}

		if (pos_.getY() <= 0) {
			pos_ = { (int)pos_.getX(),(int)game_->getSwapY() };
		}
		else if (pos_.getY() >= game_->getSwapY()) {
			pos_ = { (int)pos_.getX(), 0 };
		}

		

		//aqui come
		game_->eatFood(pos_);
		
		//aqui volvemos a comprobar si nos chocamos
		if (game_->check_collisionGhostPacman()) {
		
		}	
	}
	
	//if nyom && ha pasao tiempo de cooldown bool nyom false
	if(nyom){
	//... restar tiempo
		//if(time_>0) nyom=false
	
	}

}

void Pacman::handleEvents(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_UP)
		{
			dir_ = dirs_[directions::UP];
		}

		else if (event.key.keysym.sym == SDLK_DOWN)
		{
			dir_ = dirs_[directions::DOWN];
		}

		else if (event.key.keysym.sym == SDLK_LEFT) 
		{
			dir_ = dirs_[directions::LEFT];
		}

		else if (event.key.keysym.sym == SDLK_RIGHT)
		{
			dir_ = dirs_[directions::RIGHT];
		}
		break;
	default:
		break;
	}
}
