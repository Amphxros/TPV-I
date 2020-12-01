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
	SDL_Rect dest;
	dest.x = (pos_.getX()) + OFFSET;
	dest.y = (pos_.getY()) + OFFSET;
	dest.w = width_;
	dest.h = height_;

	if (game_->isPacmanNyom()) 
		texture_->renderFrame(dest, 0, 13);
	else
		texture_->renderFrame(dest, 0, 2 * color_);
}

void Ghost::update()
{
	Vector2D aux; 
	int direccion=0;
	
	// Usamos el vector de choises para comprobar las direcciones antes de movernos
	std::vector<Vector2D> choises;
	choises.reserve(NUM_DIRS);
	
	for (int i = 0 ; i < NUM_DIRS; i++) {
		aux = pos_ + (Vector2D)dirs_[i];	// Direcciones del enum de la clase Game
		//if(!game_->check_collisionofGhost(aux)){
			// Cargamos solo las disponibles en todo momento
			// Esto permite que el fantasma de la vuelta por un pasillo
			choises.push_back(dirs_[i]);	
		//}	
	}
	if(choises.size()==0){	// Esto es malo
		// Para la ejecución del juego si un fantasma esta sandwichado entre muros
		// Lo cual sería extremadamente raro but still
		throw "no puede moverse";
	}
	else{	// Elige un random de las posibles
		dir_ =  choises[rand() % choises.size()];
		GameCharacter::update();
	}
}
