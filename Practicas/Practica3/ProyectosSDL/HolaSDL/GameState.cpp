#include "GameState.h"

GameState::GameState(): 
	app_(nullptr)
{
}

GameState::GameState(App* app): 
	app_(app)
{
}

GameState::~GameState()
{
	for (auto it = gObjects_.begin(); it != gObjects_.end();) {
		auto aux = it;
		it++;
		delete* aux;
	};
	evHandlers_.clear(); //como los objetos que hereden de evHandler seran de herencia multiple no necesito otro bucle
}

void GameState::render()
{
	for (auto it = gObjects_.begin(); it != gObjects_.end();) //update		
		(*(it++))->render();
}

void GameState::update()
{
	for (auto it = gObjects_.begin(); it != gObjects_.end();) //update		
		(*(it++))->update();

	for (auto it = gObjectsToErase_.begin(); it != gObjectsToErase_.end();) {
		auto aux = it;
		gObjects_.erase(*aux);
		it++;
	}

	gObjectsToErase_.clear();
}

void GameState::handleEvents(SDL_Event& event)
{
	bool handled = false;
	
	for (list<EventHandler*>::iterator ev = evHandlers_.begin(); ev != evHandlers_.end() && !handled; ev++)
	{
		if ((*(ev))->handleEvents(event)) {
			return;
		}

	}
	
}
