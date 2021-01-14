#include "GameStateMachine.h"

GameStateMachine::GameStateMachine() {}

GameStateMachine::~GameStateMachine()
{
}

GameState* GameStateMachine::getCurrentState()
{
	return states_.top(); //si no hay esto sera nullptr
}

void GameStateMachine::pushState(GameState* gs)
{
	states_.push(gs);
}

void GameStateMachine::popState()
{
	states_.pop();
}

void GameStateMachine::changeState(GameState* gs)
{
	states_.pop();
	states_.push(gs);
}
