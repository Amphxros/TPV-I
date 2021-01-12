#include "PauseState.h"
#include "MenuButton.h"

PauseState::~PauseState()
{
}

void PauseState::render()
{
	GameState::render();
}

void PauseState::update()
{
	GameState::update();
}

void PauseState::handleEvents(SDL_Event& events)
{
	GameState::handleEvents(events);
}

void PauseState::init()
{
	// Inicia el juego
	MenuButton* b = new MenuButton(Vector2D(WIN_WIDTH / 2, WIN_HEIGHT/4), WIDTH_BUTTON, HEIGHT_BUTTON,
		app_->getTexture(TextureOrder::BUTTONS_PLAY), this, App::resume);
	std::list<GameObject*>::iterator it = gObjects_.insert(gObjects_.end(), b);
	b->setItList(it);

	std::list <EventHandler*>::iterator ev = hEvents_.insert(hEvents_.end(), b);
	b->setItHandler(ev);

	// Guarda la partida
	// Hay que corregir el metodo cuando tengamos el load
	b = new MenuButton(Vector2D(WIN_WIDTH / 2, WIN_HEIGHT/2), WIDTH_BUTTON, HEIGHT_BUTTON,
		app_->getTexture(TextureOrder::BUTTON_SAVE), this, App::pauseGame);
	it = gObjects_.insert(gObjects_.end(), b);
	b->setItList(it);

	ev = hEvents_.insert(hEvents_.end(), b);
	b->setItHandler(ev);

	// Vuelve al menu CREAR COSO
	b = new MenuButton(Vector2D(WIN_WIDTH / 2, 3*WIN_HEIGHT/4), WIDTH_BUTTON, HEIGHT_BUTTON,
		app_->getTexture(TextureOrder::BUTTON_MAIN), this, App::quitApp);
	it = gObjects_.insert(gObjects_.end(), b);
	b->setItList(it);

	ev = hEvents_.insert(hEvents_.end(), b);
	b->setItHandler(ev);

	delete b;
}
