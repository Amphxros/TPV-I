#include "Pacman.h"
#include "Game.h"

Pacman::Pacman(Point2D pos, double speed, double width, double height, Texture* texture, Game* game, int numVidas):
	GameCharacter(pos,speed,width,height,texture,game), vidas(numVidas)
{
	dir_ = dirs_[directions::LEFT];
	vidas=vidasmax;
}

Pacman::~Pacman()
{
}

void Pacman::render()
{
	SDL_Rect dest;
	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = width_;
	dest.h = height_;

	texture_->renderFrame(dest,0,11);
}

void Pacman::update()
{
	GameCharacter::update(); //mueve y teletransporta si llegamos a los limites del mapa


	//game_->eatFood(pos_);	//aqui come

	//aqui volvemos a comprobar si nos chocamos

	
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