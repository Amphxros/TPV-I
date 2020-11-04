#include "Game.h"
#include <iostream>

Game::Game()
{
	window_ = nullptr;
	renderer_ = nullptr;
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (window_ == nullptr || renderer_ == nullptr)
		std::cout << "Error cargando SDL" << std::endl;
	else {
		init();
		
		SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
		SDL_RenderClear(renderer_);
		SDL_RenderPresent(renderer_);
		SDL_Delay(5000);
	}
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
}

void Game::init()
{
	for (int i = 0; i < NUM_TEXTURES; i++) { 
		textures[i] = new Texture(renderer_,textures_data_[i].filename, textures_data_[i].rows, textures_data_[i].cols);
	}
	map_ = new GameMap(30, 30, textures[TextureOrder::MAP_SPRITESHEET], this);
	map_->load("...");
}

void Game::createPacman(Vector2D pos)
{
	pacman_ = new Pacman(pos, textures[TextureOrder::CHAR_SPRITESHEET], this);
}

void Game::createGhost(Vector2D pos, int color)
{
	ghost_[color] = new Ghost(pos, textures[TextureOrder::CHAR_SPRITESHEET], this, color);
}

void Game::run()
{
	while (!exit_)
	{
		render();
		update();
		handleEvents();
	}
}

void Game::render()
{
}

void Game::update()
{
}

void Game::handleEvents()
{
}
