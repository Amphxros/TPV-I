
#include "PlayState.h"

Pacman::Pacman(Point2D pos, double speed, double width, double height, Texture* texture, GameState* game, int numVidas):
	GameCharacter(pos,speed,width,height,texture,game), vidas(numVidas),EventHandler()
{
	dir_ = Vector2D(0,0);
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
	if (!game_state->CollisionWithGhosts(this)) {
		GameCharacter::update(); 
	}
	if (game_state->eatFood(getdest(), pos_)){
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
bool Pacman::handleEvents(SDL_Event& event)
{
	bool ev = false;
	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_UP) {
			dir_ = dirs_[directions::UP];
			ev = true;
		}

		else if (event.key.keysym.sym == SDLK_DOWN) {
			dir_ = dirs_[directions::DOWN];
			ev = true;
		}

		else if (event.key.keysym.sym == SDLK_LEFT) {
			dir_ = dirs_[directions::LEFT];
			ev = true;
		}

		else if (event.key.keysym.sym == SDLK_RIGHT) {
			dir_ = dirs_[directions::RIGHT];
			ev = true;
		}
		break;
	
	default:
		break;
	}

	return ev;
}

