#include "Game.h"

#include <iostream>
#include <fstream>
#include <cstdlib>	// Para el random

Game::Game()
{
	srand(NULL);
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
	delete map_;
	for (Ghost* g : ghost_)
		delete g;
	for (int i = 0; i < NUM_TEXTURES; i++)
		delete textures[i];

	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
}

void Game::init()
{
	for (int i = 0; i < NUM_TEXTURES; i++) {
		textures[i] = new Texture(renderer_, textures_data_[i].filename, textures_data_[i].rows, textures_data_[i].cols);
	}
	map_ = new GameMap(30, 30, textures[TextureOrder::MAP_SPRITESHEET], this);
	load("../Mapas/level04.dat");
}

void Game::load(std::string filename)
{
	std::ifstream file;
	file.open(filename);

	if (file.is_open()) {
		
		file >> dim_map_x >> dim_map_y;	//Tama�o del mapa
		
		for (int i = 0; i < dim_map_x; i++) {
			for (int j = 0; j < dim_map_y; j++) {
				int d;
				file >> d;

				switch (d) {
				case 0:case 1:case 2:case 3:
					map_->write(j, i, (MapCell)d); 
					if (d == 2) food_left++;	// Caso 2 es la comida, el resto son el mapa
					break;

					// Los fantasmas se codifican del 0 (5) al 3 (8) 
				case 5:case 6:case 7:case 8:
					map_->write(j, i, (MapCell)0);
					createGhost(Vector2D(j, i), d - 5);
					break;

				case 9:
					map_->write(j, i, (MapCell)0);
					createPacman(Vector2D(j, i));
					break;

				default:
					map_->write(j, i, (MapCell)0);
					break;
				}
			}
		}
	}
	else
		throw "Archivo no encontrado";
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
	while (!exit_||food_left==0)
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
	return false;
}
bool Game::check_collisionofGhost(Vector2D pos){
	if (map_->isCellWall(pos.getX(), pos.getY())) {
		return true;
	}
	return false;
}

bool Game::check_collisionGhostPacman() {
	for(Ghost* g:ghost_){
		// GetPos devuelve pos_ + dir_
	if(g->getPos()==pacman_->getPos()){
	//...
		return true;
		}
	}
	return false;
}

void Game::eatFood(Vector2D pos)
{
	if (map_->isCellFood(pos.getX(), pos.getY())) {
		map_->setMapCellEmpty(pos.getX(), pos.getY());
		food_left--;
	}
	else if (map_->isCellVitamin(pos.getX(), pos.getY())) {
		map_->setMapCellEmpty(pos.getX(), pos.getY());
		pacman_->setNyom(true);
	}
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
