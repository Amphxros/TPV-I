#include "MainMenuState.h"

MainMenuState::MainMenuState(App* app): 
	GameState(app)
{
	init();
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::render()
{
	GameState::render();
}

void MainMenuState::update()
{
	GameState::update();
}

void MainMenuState::handleEvents(SDL_Event& events)
{
	GameState::handleEvents(events);
}

void MainMenuState::init()
{
    // Inicia el juego
	MenuButton* b = new MenuButton(Vector2D(WIN_WIDTH / 2, WIN_HEIGHT/4), WIDTH_BUTTON, HEIGHT_BUTTON, 
                        app_->getTexture(TextureOrder::BUTTONS_PLAY), this, App::playGame);
	std::list<GameObject*>::iterator it= gObjects_.insert(gObjects_.end(), b);
	b->setItList(it);

	std::list <EventHandler*>::iterator ev = hEvents_.insert(hEvents_.end(), b);
	b->setItHandler(ev);

    // Carga la partida
    // Hay que corregir el metodo cuando tengamos el load
    b = new MenuButton(Vector2D(WIN_WIDTH / 2, WIN_HEIGHT/2), WIDTH_BUTTON, HEIGHT_BUTTON, 
                        app_->getTexture(TextureOrder::BUTTON_LOAD), this, App::pauseGame);
	it= gObjects_.insert(gObjects_.end(), b);
	b->setItList(it);
	
	ev = hEvents_.insert(hEvents_.end(), b);
	b->setItHandler(ev);

    // Sale del juego
	b = new MenuButton(Vector2D(WIN_WIDTH / 2, 3*WIN_HEIGHT/4), WIDTH_BUTTON, HEIGHT_BUTTON, 
                        app_->getTexture(TextureOrder::BUTTONS_QUIT), this, App::quitApp);
	it= gObjects_.insert(gObjects_.end(), b);
	b->setItList(it);

	ev = hEvents_.insert(hEvents_.end(), b);
	b->setItHandler(ev);

	delete b;
}
