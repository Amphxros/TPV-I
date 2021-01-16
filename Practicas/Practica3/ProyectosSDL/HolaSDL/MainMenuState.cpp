#include "MainMenuState.h"
#include "MenuButton.h"

MainMenuState::MainMenuState(App* app):
	GameState(app)
{
	MenuButton* button = new MenuButton(Vector2D(WIN_WIDTH / 5, WIN_HEIGHT / 2), 150, 100, app_->getTexture(TextureOrder::BUTTON_PLAY), this, App::playGame);
	std::list<GameObject*>::iterator it_ = gObjects_.insert(gObjects_.end(), button);
	std::list<EventHandler*>::iterator ev_ = evHandlers_.insert(evHandlers_.end(), button);

	button = new MenuButton(Vector2D(2* WIN_WIDTH/5,WIN_HEIGHT/2), 150, 100, app_->getTexture(TextureOrder::BUTTON_RESTART), this, App::loadGame);
	it_ = gObjects_.insert(gObjects_.end(), button);
	ev_ = evHandlers_.insert(evHandlers_.end(), button);

	button = new MenuButton(Vector2D(3* WIN_WIDTH / 5, WIN_HEIGHT / 2), 150, 100, app_->getTexture(TextureOrder::BUTTON_EXIT), this, App::quitApp);
	it_ = gObjects_.insert(gObjects_.end(), button);
	ev_ = evHandlers_.insert(evHandlers_.end(), button);

}

void MainMenuState::render()
{
	GameState::render();
}

void MainMenuState::update()
{
	GameState::update();
}

void MainMenuState::handleEvents(SDL_Event& event)
{
	GameState::handleEvents(event);
}
