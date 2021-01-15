#include "App.h"

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
	}
}

App::~App()
{
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
	states_->pushState(nullptr);
}

void App::pause()
{

	states_->pushState(nullptr);
}

void App::resume()
{
	states_->popState();
}

void App::toMainMenu()
{

	states_->popState();
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

void App::render()
{
}

void App::update()
{
}

void App::handleEvents()
{
}
