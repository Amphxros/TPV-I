#pragma once
#include <SDL.h>
#include <list>
#include "GameObject.h"
#include "EventHandler.h"
class App;
class GameState
{
public:
	GameState();
	GameState(App* app);
	virtual ~GameState();
	virtual void render();
	virtual void update();
	virtual void handleEvents(SDL_Event& event);

protected:
	std::list<GameObject*> gObjects_;
	std::list<std::list<GameObject*>::iterator> gObjectsToErase_;
	std::list<EventHandler*> evHandlers_;

	App* app_;
};

