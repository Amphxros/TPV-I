#pragma once
#include "GameState.h"
#include <fstream>
#include <iostream>
#include <map>



#include "checkML.h"

struct Date {
	int d, m, a;
	Date(int day, int mo, int ye):
		d(day), m(mo), a(ye){}
};
struct User {
	std::string name;
	int points;
	Date d;
	User(std::string n, int p, int d,int m,int a) :
		name(n), points(p), d(d,m,a) {}
};

class EndState :
	public GameState
{
public:
	EndState();
	EndState(App* app);
	virtual ~EndState(){}
	void loadFile();
	void writeFile();

	virtual void render();
	virtual void update();
	virtual void handleEvents(SDL_Event & event);

private:
	std::map<User,int> puntuaciones;
	
};

