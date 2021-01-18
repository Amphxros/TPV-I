#include "App.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "EndState.h"
#include <iostream>
App::App()
{
	srand(NULL);
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("ManPac", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (window_ == nullptr || renderer_ == nullptr)
		throw "Error cargando SDL";
	else {
		for (int i = 0; i < NUM_TEXTURES; i++) {
			textures[i] = new Texture(renderer_, textures_data_[i].filename, textures_data_[i].rows, textures_data_[i].cols);
		}
		states_ = new GameStateMachine();
		states_->pushState(new MainMenuState(this));
	}
}

App::~App()
{
	delete states_;
	for (int i = 0; i < NUM_TEXTURES; i++) {
		delete textures[i];
	}

	//destruccion de cosas de sdl
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void App::run()
{
	while (!exit_) {
		render();
		update();
		handleEvents();
		SDL_Delay(DELAY);
	}
}

void App::play()
{
	states_->pushState(new PlayState(this));
}

void App::pause()
{

	states_->pushState(new PauseState(this));
}

void App::resume()
{
	states_->popState();
}

void App::saveGame()
{
	states_->popState();
	
	if (dynamic_cast<PlayState*>(states_->getCurrentState() )!= nullptr) {
	
		static_cast<PlayState*>(states_->getCurrentState())->saveToFile();
	}
}

void App::loadGame()
{
	///pillar el nº de archivo
	Uint32 flag=0;
	int seed = -1;
	do {
		std::cout <<"Introduce nombre de archivo: ";
		std::cin >> seed;
	} while (seed < 0 || seed > 9999);
	
	//SDL_ShowSimpleMessageBox(flag, "", "cargando fichero" , window_);
	states_->pushState(new PlayState(this));
	static_cast<PlayState*>(states_->getCurrentState())->loadFromFile(seed);
}

void App::toMainMenu()
{
	while (dynamic_cast<MainMenuState*>(states_->getCurrentState()) == nullptr) {
		states_->popState();
	}
}

void App::endGame()
{
	states_->pushState(new EndState(this));
}

void App::quitApp(App* app)
{
	app->quit();
}

void App::playGame(App* app)
{
	app->play();
}

void App::resume(App* app)
{
	app->resume();
}

void App::pauseGame(App* app)
{
	app->pause();
}

void App::toMainMenu(App* app)
{
	app->toMainMenu();
}

void App::saveGame(App* app)
{
	app->saveGame();
}

void App::loadGame(App* app)
{
	app->loadGame();
}

void App::render()
{
	SDL_RenderClear(renderer_);
	states_->getCurrentState()->render();
	SDL_RenderPresent(renderer_);
}

void App::update()
{
	states_->getCurrentState()->update();

}

void App::handleEvents()
{
	SDL_Event event_;
	while(SDL_PollEvent(&event_))
	states_->getCurrentState()->handleEvents(event_);

}
