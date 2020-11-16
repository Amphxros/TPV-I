#include "Ghost.h"
#include "Game.h"
#include <vector>
#include <cstdlib>
Ghost::Ghost(Point2D pos, Texture* Texture, Game* game, int color):
	pos_(pos),texture_(Texture), game_(game),color_(color)
{
	dir_ = dirs_[directions::LEFT];
}

Ghost::~Ghost()
{
	delete texture_;
	delete game_;
}

void Ghost::render()
{
	SDL_Rect dest;
	dest.x = pos_.getX()* TAM_MAT;
	dest.y = pos_.getY()*TAM_MAT;
	dest.w = TAM_MAT;
	dest.h = TAM_MAT;

	if (game_->isPacmanNyom()) 
		texture_->renderFrame(dest, 0, 13);
	else
		texture_->renderFrame(dest, 0, 2 * color_);
}

void Ghost::update()
{
	Vector2D aux; 
	int direccion=0;
	
	std::vector<Vector2D> choises;
	choises.reserve(NUM_DIRS);
	for (int i = 0 ; i < NUM_DIRS; i++) {
		aux = pos_ + (Vector2D)dirs_[i];
		if(!game_->check_collisionofGhost(aux)){
			choises.push_back(dirs_[i]);
		}	
	}
	if(choises.size()==0){
		throw "no puede moverse";
	}
	else{
		aux = pos_ + choises[rand() % choises.size()];
		pos_ = aux;
		
		if (pos_.getX() <= 0) {
			pos_ = { (int)game_->getSwapX(), (int)pos_.getY() };
		}
		else if (pos_.getX() > game_->getSwapX()) {
			pos_ = { 0, (int)pos_.getY() };
		}

		if (pos_.getY() <= 0) {
			pos_ = { (int)pos_.getX(),(int)game_->getSwapY() };
		}
		else if (pos_.getY() > game_->getSwapY()) {
			pos_ = { (int)pos_.getX(), 0 };
		}
	}
}
