#include "Pacman.h"
Pacman::Pacman(Point2D pos, Vector2D speed,double width,double height, Texture* texture, Game* game):
pos_(pos), speed_(speed), width_(width), height_(height),texture_(texture),game_(game){

}

void Pacman::render() const
{
	SDL_Rect dest;
	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = width_;
	dest.h = height_;

	texture_->renderFrame(dest,1,10);
}

void Pacman::update()
{
//if(colision con la matriz)
	pos_ = { pos_.getX() + speed_.getX(), pos_.getY()+ speed_.getY() };


}

void Pacman::handleEvents(SDL_Event& event)
{
}
