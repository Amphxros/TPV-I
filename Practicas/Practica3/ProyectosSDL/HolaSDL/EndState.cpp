#include "EndState.h"
#include "MenuButton.h"
#include <iostream>

EndState::EndState()	:	GameState()
{
}

EndState::EndState(App* app): GameState(app)
{
	MenuButton* button = new MenuButton(Vector2D((WIN_WIDTH / 2)-75, (WIN_HEIGHT / 2)-100), 150, 100, app_->getTexture(TextureOrder::BUTTON_MAIN), this, App::toMainMenu);
	gObjects_.push_back(button);
	evHandlers_.push_back(button);

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
