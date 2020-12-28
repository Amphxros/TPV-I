#pragma once
#include <list>
#include "GameObject.h"
class App;
class GameState
{
public:
	GameState(App* app);

	virtual void render();
	virtual void update();
	virtual void handleEvents();


protected:
	App* app_;

	std::list<GameObject*> gObjects_;
	std::list<std::list<GameObject*>::iterator> gObjectsToErase_;
};

