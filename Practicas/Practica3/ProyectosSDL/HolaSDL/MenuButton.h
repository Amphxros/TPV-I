#pragma once
#include "GameObject.h"
#include "EventHandler.h"
#include "App.h"

#include "checkML.h"

using CallBack = void(App * app);

enum ButtonState { NORMAL, HIGHLIGHT, PRESSED};

class MenuButton :
	public GameObject, public EventHandler
{
public:
	MenuButton();
	MenuButton(Point2D pos, double width, double height, Texture* texture, GameState* game_,CallBack* callback);
	virtual ~MenuButton();

	void render();
	void update();
	void handleEvents(SDL_Event& event);

private:
	CallBack* callback_;
	ButtonState state;
};

