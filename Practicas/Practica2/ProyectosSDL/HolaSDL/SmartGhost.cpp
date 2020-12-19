#include "SmartGhost.h"
#include "Game.h"
#include <iostream>
SmartGhost::SmartGhost(Point2D pos, double speed, double width, double height, Texture* texture, Game* game, int color):
	Ghost(pos,speed,width,height,texture,game,color), age_(Age::CHILD) { }

void SmartGhost::render()
{
	if (age_ == Age::CHILD) {

		SDL_Rect dest;
		dest.x = pos_.getX();
		dest.y = pos_.getY();
		dest.w = width_ / 2;
		dest.h = height_ / 2;
		if (game_->isPacmanNyom())
			texture_->renderFrame(dest, 0, 13);
		else
			texture_->renderFrame(dest, 0, color_+1);
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
			if (game_->CollisionBetweenGhosts(this)) {

				reproduction_time = 10; //cambiar todo esto por constantes
			}
		}
		else {
			reproduction_time--;
		}
	}
	Ghost::update();
	handleState();
	if (age_ == Age::QUARANTINE) {
		game_->deleteGhost(this);
	}
}

void SmartGhost::handleState()
{
	if (time_ <= 0) {
		switch (age_)
		{
		case Age::CHILD:
			age_ = Age::ADULT;
			time_ = 100;
			break;
		case Age::ADULT:
			age_ = Age::QUARANTINE;
			break;
		default:
			break;
		}
	}
}
