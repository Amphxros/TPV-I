#include "GameStateMachine.h"

GameStateMachine::GameStateMachine(){}

GameStateMachine::~GameStateMachine()
{
	while (!states_.empty()) {
		states_.pop();
	}
}

void GameStateMachine::popState()
{
	if (!states_.empty()){
		states_.pop(); 
	} 
}

void GameStateMachine::changeState(GameState* gs)
{
	popState();
	pushState(gs);
}
