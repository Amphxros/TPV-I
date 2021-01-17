#pragma once
#include <stack>
#include "GameState.h"

#include "checkML.h"
class GameStateMachine
{
public:
	GameStateMachine();
	~GameStateMachine();

	GameState* getCurrentState();
	void pushState(GameState* gs);
	void popState();
	void changeState(GameState* gs);

private:
	std::stack <GameState*> states_;
};

