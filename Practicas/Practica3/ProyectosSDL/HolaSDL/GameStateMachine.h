#pragma once
#include <stack>
#include "GameState.h"

#include "checkML.h"
class GameStateMachine
{
public:
	GameStateMachine();
	~GameStateMachine();

	//devuelve el estado actual (pila)
	GameState* getCurrentState();
	//pone un nuevo estado actual
	void pushState(GameState* gs);
	//quita el estado actual
	void popState();
	void changeState(GameState* gs);

private:
	std::stack <GameState*> states_; //pila de estados
};

