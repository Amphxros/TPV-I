#pragma once
#include "GameState.h"
class EndState :
	public GameState
{
public:
	EndState();
	EndState(App* app);
	virtual ~EndState(){}

	virtual void render();
	virtual void update();
	virtual void handleEvents(SDL_Event & event);
	
};

