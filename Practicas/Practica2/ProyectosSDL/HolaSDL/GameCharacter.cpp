#include "GameCharacter.h"

GameCharacter::~GameCharacter()
{
}

void GameCharacter::render()
{
	texture_->render(getdest());
}

void GameCharacter::update()
{
	pos_ = pos_ + dir_;
}

GameCharacter::GameCharacter(Point2D pos, double width, double height, Texture* texture, Game* game):
	GameObject(pos, width, height, texture, game), pos_init(pos_)
{
	dir_ = dirs_[directions::LEFT];
}
