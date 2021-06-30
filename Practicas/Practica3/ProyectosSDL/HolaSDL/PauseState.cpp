#include "PauseState.h"
#include "MenuButton.h"

PauseState::PauseState(App* app): 
	GameState(app)
{
	// Deshace la pausa
	MenuButton* button = new MenuButton(Vector2D(WIN_WIDTH / 5, WIN_HEIGHT / 2), 150, 100, app_->getTexture(TextureOrder::BUTTON_RESUME), this, App::resume);
	std::list<GameObject*>::iterator it_ = gObjects_.insert(gObjects_.end(), button);
	std::list<EventHandler*>::iterator ev_ = evHandlers_.insert(evHandlers_.end(), button);

	// Guarda el juego
	MenuButton* button1 = new MenuButton(Vector2D(2 * WIN_WIDTH / 5, WIN_HEIGHT / 2), 150, 100, app_->getTexture(TextureOrder::BUTTON_SAVE), this, App::saveGame);
	std::list<GameObject*>::iterator it1 = gObjects_.insert(gObjects_.end(), button1);
	std::list<EventHandler*>::iterator ev1 = evHandlers_.insert(evHandlers_.end(), button1);

	MenuButton* button2 = new MenuButton(Vector2D(3 * WIN_WIDTH / 5, WIN_HEIGHT / 2), 150, 100, app_->getTexture(TextureOrder::BUTTON_MAIN), this, App::toMainMenu);
	std::list<GameObject*>::iterator it2 = gObjects_.insert(gObjects_.end(), button2);
	std::list<EventHandler*>::iterator ev2 = evHandlers_.insert(evHandlers_.end(), button2);
}

void PauseState::render()
{
	GameState::render();
}

void PauseState::update()
{
	//Los updates de los botones estan vacios 
	//como en este estado solo hay botones 
	//no necesita llamarse al GameState::update
}

void PauseState::handleEvents(SDL_Event& event)
{
	GameState::handleEvents(event);
}
