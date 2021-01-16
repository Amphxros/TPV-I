#pragma once
#include "GameState.h"
class MainMenuState :
	public GameState
{
public:
	MainMenuState(): GameState(){}
	MainMenuState(App* app);

	virtual void render();
	virtual void update();
	virtual void handleEvents(SDL_Event& event);

private:
};

