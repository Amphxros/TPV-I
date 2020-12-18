#pragma once

#include "checkML.h"
#include "GameCharacter.h"
class Game;
class Ghost:
	public GameCharacter
{
public:
	//constructor
	Ghost(Point2D pos, double speed,double width, double height, Texture* texture, Game* game,int color);
	//destructor
	virtual ~Ghost();
	//render
	void render();
	//update
	void update();

	void saveToFile(std::ofstream& file);
	void LoadFromFile(std::ifstream& file);

	bool chooseDirection();

	
protected:
	int color_; //color del fantasma
	int time_per_election = 5;
};

