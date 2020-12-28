#include "GameStateMachine.h"

GameStateMachine::GameStateMachine(){}

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
