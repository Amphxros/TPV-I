#include "Ghost.h"
#include "PlayState.h"
#include <vector>

Ghost::Ghost(Point2D pos, double speed, double width, double height, Texture* texture, GameState* game, int color) :
	GameCharacter(pos, speed, width, height, texture, game), color_(color), time_per_election(TIME_PER_ELECTION)
{
	dir_ = dirs_[directions::LEFT];
}

Ghost::~Ghost(){ }

void Ghost::render()
{
	SDL_Rect dest=getdest();
	
	if (game_state->isPacmanNyom()) 
		texture_->renderFrame(dest, 0, 13);
	else
		texture_->renderFrame(dest, 0, 2 * color_);
}

void Ghost::update()
{
	//si puede elegir una nueva direccion
	if (time_per_election < 0) {
		if (chooseDirection()) { //cambia su direccion y comprueba que no esta encerrado
			GameCharacter::update(); //actualiza pos y demas
		}
		time_per_election = TIME_PER_ELECTION; //restaura su tiempode eleccion
	}
	else{ //si no puede cambiar de direccion
		time_per_election--;
		if(!game_state->tryMove(getdest(),(Vector2D)(dir_),Point2D(pos_ + ((Vector2D)dir_*speed_)))){ //si hay colision tambien cambia de direccion
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
		aux = pos_ + ((Vector2D)dirs_[i]*speed_);	// Direcciones del enum de la clase padre
		if(game_state->tryMove(getdest(),(Vector2D)(dirs_[i]),Point2D(aux))){ //si es posible el movimiento en esa direccion lo añade como posibilidad
			
			choises.push_back(dirs_[i]);	
		}	
	}

	if(choises.size()==0){	// Esto es  porque estaria encerrado entre muros
		throw "no puede moverse";
		return false;
	}

	// Elige un random de las posibles
	else if (choises.size() > 2){	
		Vector2D aux = dir_;
		do {
			dir_ = choises[rand() % choises.size()];
		} while (aux == dir_);
		
		return true;
	}
	else {

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