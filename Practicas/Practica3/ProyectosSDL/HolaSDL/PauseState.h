#pragma once
#include "GameState.h"


const int WIDTH_BUTTON = 300;
const int HEIGHT_BUTTON = 100;

class App;
class PauseState :
	public GameState
{
public:
	PauseState(App* app) : GameState(app_) { init(); };
	virtual ~PauseState();

	virtual void render();
	virtual void update();
	virtual void handleEvents(SDL_Event& events);

private:
	void init();
};

