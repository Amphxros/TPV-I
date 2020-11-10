#include "Game.h"
#include <iostream>
#include <cstdlib>
Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("ManPac", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (window_ == nullptr || renderer_ == nullptr)
		throw "Error cargando SDL";
	else {
		init();
	}
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
}

void Game::init()
{
	srand(NULL);
	for (int i = 0; i < NUM_TEXTURES; i++) {
		textures[i] = new Texture(renderer_, textures_data_[i].filename, textures_data_[i].rows, textures_data_[i].cols);
	}
	map_ = new GameMap(30, 30, textures[TextureOrder::MAP_SPRITESHEET], this);
	map_->load("../Mapas/level01.dat");
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
		handleEvents();
		update();
		render();
		SDL_Delay(200);
	}
}

bool Game::check_collisionofPacman(Vector2D pos)
{
	if (map_->isCellWall(pos.getX(), pos.getY())) {
		return true;
	}
	else {
		if (map_->isCellFood(pos.getX(), pos.getY())) {
			map_->setMapCellEmpty(pos.getX(), pos.getY());
		}
		else if (map_->isCellVitamin(pos.getX(), pos.getY())) {
			map_->setMapCellEmpty(pos.getX(), pos.getY());
			//set nyom true
			pacman_->setNyom(true);
		}

		return false;
	}
}
bool Game::check_collisionofGhost(Vector2D pos){
	if (map_->isCellWall(pos.getX(), pos.getY())) {
		return true;
	}
	return false;
}

bool Game::check_collisionGhostPacman() {
	for(Ghost* g:ghost_){
	if(g->getPos()==pacman_->getPos()){
	//....
		return true;
		}
	}
	return false;
}

void Game::render()
{
	SDL_RenderClear(renderer_);
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
	map_->render();
	for (Ghost* g : ghost_) {
		g->render();
	}
	pacman_->render();
	SDL_RenderPresent(renderer_);
}

void Game::update()
{
	pacman_->update();
	for(Ghost* g:ghost_){
		g->update();
	}

}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			exit_ = true;
		}
		else
		{
		pacman_->handleEvents(event);
		}
	}
}
