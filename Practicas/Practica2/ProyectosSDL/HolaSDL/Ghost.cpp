#include "Ghost.h"
#include "Game.h"
#include <vector>

Ghost::Ghost(Point2D pos, double speed,double width, double height, Texture* texture, Game* game, int color):
	GameCharacter(pos,speed,width,height,texture,game),color_(color)
{
	dir_ = dirs_[directions::LEFT];
}

Ghost::~Ghost()
{
	//delete texture_; //texture_ = nullptr;
}

void Ghost::render()
{
	SDL_Rect dest=getdest();
	
	if (game_->isPacmanNyom()) 
		texture_->renderFrame(dest, 0, 13);
	else
		texture_->renderFrame(dest, 0, 2 * color_);
}

void Ghost::update()
{
	Vector2D aux; 
	
	//// Usamos el vector de choises para comprobar las direcciones antes de movernos
	std::vector<Vector2D> choises;
	choises.reserve(NUM_DIRS);
	//
	for (int i = 0 ; i < NUM_DIRS; i++) {
		aux = pos_ + (Vector2D)dirs_[i];	// Direcciones del enum de la clase Game
		if(game_->tryMove(getdest(),(Vector2D)(dirs_[i]),Point2D(aux))){
			
			choises.push_back(dirs_[i]);	
		}	
	}
	if(choises.size()==0){	// Esto es malo
	//	throw "no puede moverse";
	}
	else {	// Elige un random de las posibles
		dir_ = choises[rand() % choises.size()];
		pos_ = pos_ + (dir_ * speed_);
	}
}

