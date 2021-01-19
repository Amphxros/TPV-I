#pragma once
#include "Ghost.h"
#include "checkML.h"
class PlayState;
// La edad determinará si se puede reproducir, tiene que esperar o tiene que morir
enum class Age{CHILD, ADULT, QUARANTINE}; //edad

class SmartGhost :
	public Ghost
{
public:
    SmartGhost() : Ghost() {	throw PacmanError("SmartFantasma nulo (Not so smart now)"); }
	SmartGhost(Point2D pos, double speed, double width, double height, Texture* texture, GameState* game, int color);
	virtual ~SmartGhost() {};
	
	void render();
	void update();
	void handleState(); //cambia la fase del fantasma si es necesario
	inline Age getAge() { return age_; } //deuelve la edad

	void saveToFile(std::ofstream& file);
	void loadFromFile(std::ifstream& file);

private:
	Age age_; //edad del fantasma
	int time_; //tiempo de fase
	int reproduction_time; //cooldwn para reproducirse

};

