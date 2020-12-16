#include "SmartGhost.h"
#include "Game.h"
#include <iostream>
SmartGhost::SmartGhost(Point2D pos, double speed, double width, double height, Texture* texture, Game* game, int color):
	Ghost(pos,speed,width,height,texture,game,color), age_(Age::CHILD)
{
}

void SmartGhost::render()
{
	Ghost::render();
}

void SmartGhost::update()
{
	if (age_ == Age::ADULT) {
		if (game_->CollisionBetweenGhosts(this)) {
			std::cout << "add ghost";
		
		}
	}
	else {
		time_--;
		if(time_<=0){
			age_ = Age::ADULT;
		}
	}
	Ghost::update();
}
