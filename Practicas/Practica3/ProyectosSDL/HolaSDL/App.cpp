#include "App.h"

App::App()
{
}

void App::run()
{
	while (!exit) {
		handleEvents();
		update();		
		render();
	}
}
void App::quitApp(App* app)
{
	app->quit();
}
void App::playGame(App* app)
{
	app->states_->pushState(new GameState(app)); //cambiar esto por un playstate
}
void App::resume(App* app)
{
	app->states_->popState();
}
void App::pauseGame(App* app)
{
	app->states_->pushState(new GameState(app)); //cambiar esto por un pausestate
}
void App::toMainMenu(App* app)
{
	
}
void App::init()
{
}

void App::render()
{
	states_->getCurrentState()->render();
}

void App::update()
{
	states_->getCurrentState()->update();
}

void App::handleEvents()
{
	states_->getCurrentState()->handleEvents();
}

