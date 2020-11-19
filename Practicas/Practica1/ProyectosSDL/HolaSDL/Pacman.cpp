#include "Pacman.h"
#include "Game.h"

Pacman::Pacman(Point2D pos, Texture* texture, Game* game, int numVidas):
pos_(pos),texture_(texture),game_(game), vidasmax(numVidas) {
	dir_ = dirs_[directions::LEFT];
	vidas=vidasmax;
}

Pacman::~Pacman()
{
}

void Pacman::render()
{
	SDL_Rect dest;
	dest.x = (pos_.getX() * TAM_MAT) + OFFSET;
	dest.y = (pos_.getY() * TAM_MAT) + OFFSET;
	dest.w = TAM_MAT;
	dest.h = TAM_MAT;

	texture_->renderFrame(dest,0,11);
}

void Pacman::update()
{
	if (!game_->check_collisionGhostPacman()) {		// si no hay colision, nos movemos

		if (!game_->check_collisionofPacman(getPos())) {
			//aqui se mueve
			pos_ = getPos();

			//comprobamos los puntos en los que se puede salir por otro lado del mapa
			if (pos_.getX() <= 0)
				pos_ = { (int)game_->getSwapX()-1, (int)pos_.getY() };

			else if (pos_.getX() >= game_->getSwapX()) 
				pos_ = { 1, (int)pos_.getY() };

			if (pos_.getY() <= 0) 
				pos_ = { (int)pos_.getX(),(int)game_->getSwapY() };
			
			else if (pos_.getY() > game_->getSwapY()) 
				pos_ = { (int)pos_.getX(), 0 };

			game_->eatFood(pos_);	//aqui come

			//aqui volvemos a comprobar si nos chocamos
			game_->check_collisionGhostPacman();
		}
	}
	//if nyom && ha pasao tiempo de cooldown bool nyom false
	if(nyom){

		cool_nyom -= SDL_GetTicks() % TIME_PER_FRAME;
		if (cool_nyom < 0) {
			nyom = false;
		}
	}

}

// Actualiza la direccion actual de PacMan al presionar una tecla
void Pacman::handleEvents(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_UP)
			dir_ = dirs_[directions::UP];

		else if (event.key.keysym.sym == SDLK_DOWN)
			dir_ = dirs_[directions::DOWN];

		else if (event.key.keysym.sym == SDLK_LEFT) 
			dir_ = dirs_[directions::LEFT];

		else if (event.key.keysym.sym == SDLK_RIGHT)
			dir_ = dirs_[directions::RIGHT];
		break;
	
	default:
		break;
	}
}

void Pacman::setNyom(bool comer)
{
	nyom = comer; 
	cool_nyom = COOLNYOM; // Variable global de tiempo de duracion del powerup
}
