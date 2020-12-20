#pragma once
#include "Ghost.h"
class Game;

enum Age{CHILD, ADULT, QUARANTINE, OLD}; //edad
class SmartGhost :
	public Ghost
{
public:
	SmartGhost(Point2D pos, double speed, double width, double height, Texture* texture, Game* game, int color);
	virtual ~SmartGhost() {};
	
	void render();
	void update();
	void handleState();
	inline Age getAge() { return age_; }

private:
	Age age_;
	int time_;
	int reproduction_time;

};

