#pragma once
#include "GameState.h"

const int WIDTH_BUTTON = 300;
const int HEIGHT_BUTTON = 100;

class PauseState :
	public GameState
{
public:
	PauseState(App* app) : GameState(app_) { init(); };
	virtual ~PauseState();

	void render();
	void update();
	void handleEvents(SDL_Event& events);

private:
	void init();
};

