#include "GameState.h"
#include "App.h"

GameState::~GameState()
{
	//borrado de objetos
	for (auto g = gObjects_.begin(); g != gObjects_.end();) {
		auto aux = g;
		g++;
		delete* aux;
	}
	gObjects_.clear();
	hEvents_.clear();
}

void GameState::render()
{
	for (auto it = gObjects_.begin(); it != gObjects_.end();) {
		(*(it++))->render();
	}
}

void GameState::update()
{
	for (auto it = gObjects_.begin(); it != gObjects_.end();) {
		(*(it++))->update();
	}

	//limpiamos los que no nos sirven
	for (auto g = gObjectsToErase_.begin(); g != gObjectsToErase_.end();) {
		auto aux = g;
		g++;
		delete** aux;
	}
	gObjectsToErase_.clear();
}

void GameState::handleEvents(SDL_Event & event)
{
	for (auto it = hEvents_.begin(); it != hEvents_.end();) {
		(*(it++))->handleEvents(event);
	}
}

void GameState::addGameObject(GameObject* go)
{
	std::list<GameObject*>::iterator it = gObjects_.insert(gObjects_.end(), go);
	go->setItList(it);
}

void GameState::addEventHandler(EventHandler* ev)
{
	std::list<EventHandler*>::iterator it = hEvents_.insert(hEvents_.end(), ev);
	ev->setItHandler(it);
}
