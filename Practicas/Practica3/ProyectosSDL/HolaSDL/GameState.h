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
	//constructora
	GameState();
	GameState(App* app);
	//destructora
	virtual ~GameState();

	virtual void render();
	virtual void update();
	virtual void handleEvents(SDL_Event& event);

	App* getApp() { return app_; }

protected:
	std::list<GameObject*> gObjects_; //lista de GameObjects para renderizar y actualizar 
	std::list<EventHandler*> evHandlers_; //lista de manejo de eventos

	App* app_; //puntero a app
};

