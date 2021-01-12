#pragma once
#include "GameObject.h"
#include "EventHandler.h"

#include "checkML.h"

class App;
using CallBack = void(App * app);

enum ButtonState { NORMAL, HIGHLIGHT, PRESSED};

class MenuButton :
	public GameObject, public EventHandler
{
public:
	MenuButton();
	MenuButton(Point2D pos, double width, double height, Texture* texture, GameState* game_, CallBack* callback);
	virtual ~MenuButton();

	virtual void render();
	virtual void update();
	virtual void handleEvents(SDL_Event& event);

private:
	CallBack* callback_;
	ButtonState state;
};

