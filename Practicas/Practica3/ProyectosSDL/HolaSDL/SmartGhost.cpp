#include "SmartGhost.h"
#include "PlayState.h"
#include <iostream>

SmartGhost::SmartGhost(Point2D pos, double speed, double width, double height, Texture* texture, GameState* game, int color):
	Ghost(pos,speed,width,height,texture,game,color), age_(Age::CHILD), time_(TIME_PER_PHASE), reproduction_time(TIME_PER_REPRODUCTION) { }

void SmartGhost::render()
{
	if (age_ == Age::CHILD) {

		SDL_Rect dest;
		dest.x = pos_.getX();
		dest.y = pos_.getY();
		dest.w = width_ / 2;
		dest.h = height_ / 2;
		if (game_state->isPacmanNyom())
			texture_->renderFrame(dest, 0, 13);
		else
			texture_->renderFrame(dest, 0, 2* color_);
	}
	else {
		Ghost::render();
	}
}

void SmartGhost::update()
{
	time_--;
	if (age_ == Age::ADULT) {
		//si hay colision con fantasmas adultos o normales se crea un fantasma
		if (reproduction_time <= 0) {
			if (game_state->CollisionBetweenGhosts(this)) {

				reproduction_time = TIME_PER_REPRODUCTION; //cambiar todo esto por constantes
			}
		}
		else {
			reproduction_time--;
		}
	}
	Ghost::update();
	handleState();
	if (age_ == Age::QUARANTINE) {
		game_state->deleteGhost(it_, ghost_it); //salta un error al intentar borrarlo que no entendemos la razon ya que es el mismo metodo que se usa cuando el pacman come a este tipo de fantasma
	}
}

void SmartGhost::handleState()
{
	if (time_ <= 0) {
		switch (age_)
		{
		case Age::CHILD:
			age_ = Age::ADULT;
			time_ = TIME_PER_PHASE;
			break;
		case Age::ADULT:
			age_ = Age::QUARANTINE;
			break;
		default:
			break;
		}
	}
}
