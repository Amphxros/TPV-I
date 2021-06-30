#include "GameStateMachine.h"

GameStateMachine::GameStateMachine() {
	states_ = stack<GameState*>();
}

GameStateMachine::~GameStateMachine()
{
	while (!states_.empty()) { states_.pop(); }
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
	if (!states_.empty()) {
		delete states_.top();
		states_.pop();
	}
}

void GameStateMachine::changeState(GameState* gs)
{
	popState();
	pushState(gs);
}
