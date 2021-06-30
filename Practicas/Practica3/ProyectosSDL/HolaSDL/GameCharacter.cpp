#include "GameCharacter.h"
#include "PlayState.h"

GameCharacter::~GameCharacter(){
}

void GameCharacter::render()
{
	texture_->render(getdest());
}

void GameCharacter::update()
{

	// Comprobamos los puntos en los que se puede salir por otro lado del mapa
	int x = pos_.getX() + dir_.getX(); int y = pos_.getY() + dir_.getX();
	if (pos_.getX() <= 0)
		pos_ = { (int)TAM_TILE * ((int)game_state->getSwapX() - 1), (int)pos_.getY() };

	else if (pos_.getX() >= (TAM_TILE * (game_state->getSwapX()) -width_))
		pos_ = { 1, (int)pos_.getY() };

	if (pos_.getY() <= 0)
		pos_ = { (int)pos_.getX(), (int)TAM_TILE * (int)game_state->getSwapY() };

	else if (pos_.getY() > TAM_TILE * game_state->getSwapY())
		pos_ = { (int)pos_.getX(), 0 };

	// Intenta cambiar la dirección
	if (game_state->tryMove(getdest(), dir_, pos_ + (dir_ * speed_))) {
		pos_ = pos_ + (dir_ * speed_);
	}
	// Si no lo consigue la direccion permanece como estaba
}

// El saveToFile es comun a Ghost y Pacman
void GameCharacter::saveToFile(std::ofstream& file)
{
	std::string data = to_string((int)pos_.getX()) + " " + to_string((int)pos_.getY()) + " " +
		to_string((int)pos_init.getX()) + " " + to_string((int)pos_init.getY()) + " ";
	file << data;
}

void GameCharacter::loadFromFile(std::ifstream& file)
{
	float x, y, x0, y0; 
	file >> x >> y >> x0>>y0;
	pos_ = { (int)x,(int)y };
	pos_init = { (int)x0,(int)y0 };

}

GameCharacter::GameCharacter() :
	GameObject(), speed_(0), pos_init(Vector2D()) {

	throw PacmanError("character null");
}

GameCharacter::GameCharacter(Point2D pos, double speed, double width, double height, Texture* texture, GameState* game):
	GameObject(pos, width, height, texture, game),speed_(speed), pos_init(pos_),game_state(static_cast<PlayState*>(game))
{
	dir_ = dirs_[directions::UP];
}
