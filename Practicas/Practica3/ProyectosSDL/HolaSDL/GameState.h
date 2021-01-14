#pragma once
#include <SDL.h>
#include <list>
#include "GameObject.h"
#include "EventHandler.h"
class App;
class GameState
{
public:
	GameState(App* app);
	virtual ~GameState();
	virtual void render();
	virtual void update();
	virtual void handleEvents(SDL_Event& event);

protected:
	std::list<GameObject*> gObjects;
	std::list<std::list<GameObject*>::iterator> gObjectsToErase;
	std::list<EventHandler*> evHandlers;



};

