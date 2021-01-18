#pragma once
#include "GameState.h"
#include <map>
#include "checkML.h"


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

	void saveScores();
	void loadScores();

private:

};

