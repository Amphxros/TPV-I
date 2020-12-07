#include "GameCharacter.h"
#include "Game.h"

GameCharacter::~GameCharacter(){}

void GameCharacter::render()
{
	texture_->render(getdest());
}

void GameCharacter::update()
{
	
		pos_ = pos_ + (dir_ * speed_);
	//comprobamos los puntos en los que se puede salir por otro lado del mapa
	if (pos_.getX() <= 0)
		pos_ = { TAM_MAT * ((int)game_->getSwapX() - 1), (int)pos_.getY() };

	else if (pos_.getX() >= (TAM_MAT *game_->getSwapX()-1))
		pos_ = { 1, (int)pos_.getY() };

	if (pos_.getY() <= 0)
		pos_ = { (int)pos_.getX(), TAM_MAT *(int)game_->getSwapY() };

	else if (pos_.getY() > TAM_MAT* game_->getSwapY())
		pos_ = { (int)pos_.getX(), 0 };

	
}

GameCharacter::GameCharacter(Point2D pos, double speed, double width, double height, Texture* texture, Game* game):
	GameObject(pos, width, height, texture, game),speed_(speed), pos_init(pos_)
{
	dir_ = dirs_[directions::LEFT];
}
