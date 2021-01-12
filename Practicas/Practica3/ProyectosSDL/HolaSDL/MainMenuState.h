#pragma once
#include "GameState.h"
#include "MenuButton.h"

const int WIDTH_BUTTON = 300;
const int HEIGHT_BUTTON = 100;

class MainMenuState :
	public GameState
{
public:
	MainMenuState(App* app);
	virtual ~MainMenuState();

	virtual void render();
	virtual void update();
	virtual void handleEvents(SDL_Event& events);

private:
	//std::list<MenuButton*> buttons_;

};

