#pragma once
#include "GameState.h"
#include "MenuButton.h"
#include "checkML.h"

class MainMenuState :
	public GameState
{
public:
	MainMenuState(): GameState(){
	}
	MainMenuState(App* app = nullptr);
	virtual ~MainMenuState() {};

	virtual void render();
	virtual void update();
	virtual void handleEvents(SDL_Event & event);

private:

};