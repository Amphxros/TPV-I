#pragma once
#include <stack>
#include "GameState.h"
class GameStateMachine
{
public:
	GameStateMachine();
	~GameStateMachine();
	
	GameState* getCurrentState() { return states_.top(); }
	void pushState(GameState* gs) { states_.push(gs); };
	void popState();
	void changeState(GameState* gs);

private:
	std::stack<GameState*> states_;
};

