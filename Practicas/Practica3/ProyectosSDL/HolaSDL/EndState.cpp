#include "EndState.h"
#include "MenuButton.h"
#include <iostream>

EndState::EndState():
	GameState()
{
}

EndState::EndState(App* app): GameState(app)
{
	MenuButton* button = new MenuButton(Vector2D((WIN_WIDTH / 2)-75, (WIN_HEIGHT / 2)-100), 150, 100, app_->getTexture(TextureOrder::BUTTON_MAIN), this, App::toMainMenu);
	std::list<GameObject*>::iterator it_ = gObjects_.insert(gObjects_.end(), button);
	std::list<EventHandler*>::iterator ev_ = evHandlers_.insert(evHandlers_.end(), button);

}

void EndState::render()
{
	GameState::render();
}

void EndState::update()
{
	//Los updates de los botones estan vacios 
	//como en este estado solo hay botones 
	//no necesita llamarse al GameState::update
}

void EndState::handleEvents(SDL_Event& event)
{
	GameState::handleEvents(event);
}
