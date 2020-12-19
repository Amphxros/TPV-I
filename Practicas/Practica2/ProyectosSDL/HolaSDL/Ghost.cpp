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
	if (time_per_election < 0) {
		if (chooseDirection()) {
			GameCharacter::update();
		}
		time_per_election = 5;
	}
	else{
		time_per_election--;
		if(!game_->tryMove(getdest(),(Vector2D)(dir_),Point2D(pos_ + ((Vector2D)dir_*speed_)))){
			chooseDirection();
		}
		GameCharacter::update();
	}
}

bool Ghost::chooseDirection()
{
	Vector2D aux; 
		
	//// Usamos el vector de choises para comprobar las direcciones antes de movernos
	std::vector<Vector2D> choises;
	choises.reserve(NUM_DIRS);
	//
	for (int i = 0 ; i < NUM_DIRS; i++) {
		aux = pos_ + ((Vector2D)dirs_[i]*speed_);	// Direcciones del enum de la clase Game
		if(game_->tryMove(getdest(),(Vector2D)(dirs_[i]),Point2D(aux))){
			
			choises.push_back(dirs_[i]);	
		}	
	}
	if(choises.size()==0){	// Esto es malo
	//	throw "no puede moverse";
		return false;
	}
	else {	// Elige un random de las posibles
		dir_ = choises[rand() % choises.size()];
		return true;
	}
}
void Ghost::saveToFile(std::ofstream& file) {
	GameCharacter::saveToFile(file);
	file <<" "<< (to_string)(color_);
}
void Ghost::LoadFromFile(std::ifstream& file) {

	int x, y, x0, y0, w, h,c;
	file >> x >> y >> x0 >> y0 >> w >> h>>c;
	pos_ = { (int)x,(int)y };
	pos_init = { (int)x0,(int)y0 };
	width_ = w;
	height_ = h;
	color_ = c;
}