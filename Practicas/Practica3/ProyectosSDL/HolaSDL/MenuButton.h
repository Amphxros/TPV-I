#pragma once
#include "GameObject.h"
#include "EventHandler.h"
#include "App.h"

#include "checkML.h"
using CallBack = void(App * app);

enum State {NORMAL, HIGHLIGHTED, CLICKED};

class MenuButton :
	public GameObject, public EventHandler
{
public:
	MenuButton();
	MenuButton(Point2D pos, double width, double height, Texture* texture, GameState* game, CallBack* cb);
	virtual ~MenuButton();

	virtual void render();
	virtual void update();
	virtual bool handleEvents(SDL_Event& event);

private:
	CallBack* call_back_=nullptr;
	State click;
};

