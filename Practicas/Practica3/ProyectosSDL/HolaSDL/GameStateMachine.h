#pragma once
#include <stack>
#include "GameState.h"

#include "checkML.h"
class GameStateMachine
{
public:
	GameStateMachine();
	virtual ~GameStateMachine();


	GameState* getCurrentState();	//devuelve el estado actual (tope de la pila)
	void pushState(GameState* gs);//pone un nuevo estado actual al tope de la pila
	void popState();	//quita el estado actual y hace delete
	void changeState(GameState* gs);

private:

	std::stack <GameState*> states_; //pila de estados

};

