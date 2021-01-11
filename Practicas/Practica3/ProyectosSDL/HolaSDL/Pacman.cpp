#include "Pacman.h"
#include "Game.h"
#include "PlayState.h"

Pacman::Pacman(Point2D pos, double speed, double width, double height, Texture* texture, GameState* game, int numVidas):
	GameCharacter(pos,speed,width,height,texture,game),EventHandler(), vidas(numVidas)
{
	dir_ = dirs_[directions::LEFT];
}

Pacman::~Pacman()
{
}

void Pacman::render()
{
	SDL_Rect dest = getdest();
	texture_->renderFrame(dest,0,11);
}

void Pacman::update()
{
	
	if (static_cast<PlayState*>(game_)->CollisionWithGhosts(this)) {
		GameCharacter::update(); 
	}
	if (static_cast<PlayState*>(game_)->eatFood(getdest(), pos_)){
		nyom = true;
		cool_nyom = COOLNYOM;
	}
	
	//if nyom && ha pasao tiempo de cooldown bool nyom= false
	if(nyom){

		cool_nyom --;
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

