#include "PauseState.h"
#include "MenuButton.h"

PauseState::PauseState(App* app): 
	GameState(app)
{
	MenuButton* button = new MenuButton(Vector2D(WIN_WIDTH / 5, WIN_HEIGHT / 2), 150, 100, app_->getTexture(TextureOrder::BUTTON_RESUME), this, App::resume);
	std::list<GameObject*>::iterator it_ = gObjects_.insert(gObjects_.end(), button);
	std::list<EventHandler*>::iterator ev_ = evHandlers_.insert(evHandlers_.end(), button);

	button = new MenuButton(Vector2D(2 * WIN_WIDTH / 5, WIN_HEIGHT / 2), 150, 100, app_->getTexture(TextureOrder::BUTTON_PLAY), this, App::saveGame);
	it_ = gObjects_.insert(gObjects_.end(), button);
	ev_ = evHandlers_.insert(evHandlers_.end(), button);

	button = new MenuButton(Vector2D(3 * WIN_WIDTH / 5, WIN_HEIGHT / 2), 150, 100, app_->getTexture(TextureOrder::BUTTON_MAIN), this, App::toMainMenu);
	it_ = gObjects_.insert(gObjects_.end(), button);
	ev_ = evHandlers_.insert(evHandlers_.end(), button);
}

void PauseState::render()
{
	GameState::render();
}

void PauseState::handleEvents(SDL_Event& event)
{
	GameState::handleEvents(event);
}
