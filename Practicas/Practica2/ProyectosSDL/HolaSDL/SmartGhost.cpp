#include "SmartGhost.h"
#include "Game.h"
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
	//if (age_ == Age::ADULT) {
	//	if (game_->CollisionWithGhosts(this) && !game_->tryMove(getdest(), dir_, pos_ + (dir_*speed_))) {
	//		game_->createSmartGhost(pos_);
	//	}
	//}
	//else {
	//	time_--;
	//	if(time_<=0){
	//		age_ = Age::ADULT;
	//	}
	//}
	Ghost::update();
}
