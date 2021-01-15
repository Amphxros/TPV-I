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
}

void GameState::handleEvents(SDL_Event& event)
{
	bool handled = false;
	list<EventHandler*>::iterator ev = evHandlers_.begin();
	while (!handled && ev != evHandlers_.end())
	{
		if ((*ev)->handleEvents(event)) {
			handled = true;
		}
		ev++;
	}
}
