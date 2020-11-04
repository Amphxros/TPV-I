#include "Ghost.h"

Ghost::Ghost(Point2D pos, Vector2D speed, double width, double height, Texture* Texture, Game* game_, int color)
{
}

Ghost::~Ghost()
{
	delete texture_;
}

void Ghost::render() const
{
	SDL_Rect dest;
	dest.x = pos_.getX();
	dest.y = pos_.getY();
	dest.w = width_;
	dest.h = height_;

	texture_->renderFrame(dest,GHOST_ROW,GHOST_COL);
}

void Ghost::update()
{
	///while (colision inminente(dir)) genera dir aleatoria
	pos_ = { pos_.getX() + speed_.getX(), pos_.getY() + speed_.getY() };
}
