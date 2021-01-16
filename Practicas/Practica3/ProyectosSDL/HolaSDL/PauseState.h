#pragma once
#include "GameState.h"
class PauseState :
	public GameState
{
public:
	PauseState(): GameState() {};
	PauseState(App* app);

	virtual void render();
	virtual void update() {};
	virtual void handleEvents(SDL_Event& event);

};

