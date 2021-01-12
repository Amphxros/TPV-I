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

	void render();
	void update();
	void handleEvents(SDL_Event& events);

private:
	void init();
	//std::list<MenuButton*> buttons_;

};

