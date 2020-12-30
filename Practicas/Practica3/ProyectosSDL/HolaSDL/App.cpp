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
		init();
	}
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
	SDL_Event event;
	states_->getCurrentState()->handleEvents(event);
}

void App::quitApp(App* app)
{
	app->quit();
}

void App::resume(App* app)
{
	app->states_->popState();
}
void App::toMainMenu(App* app)
{

}