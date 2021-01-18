#pragma once
#include <SDL.h>
#include <list>
#include "GameObject.h"
#include "EventHandler.h"
#include "PacmanError.h"
#include "checkML.h"
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

	App* getApp() { return app_; }

protected:
	std::list<GameObject*> gObjects_;
	std::list<EventHandler*> evHandlers_;

	App* app_;
};

