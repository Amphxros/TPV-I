#pragma once
#include <string>
#include <SDL.h>

#include "Vector2D.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GameMap.h"
#include "checkML.h"

const int WIN_WIDTH=800;
const int WIN_HEIGHT=600;

const int NUM_TEXTURES=4;
const int NUM_GHOSTS=4;
const int TAM_MAT=20;
const int NUM_DIRS = 4;

// Tanto Fantasma como Ghost usan el enum de Directions
enum directions { LEFT, RIGHT, UP, DOWN };
const Vector2D dirs_[NUM_DIRS] = {Vector2D(-1,0),Vector2D(1,0),Vector2D(0,-1),Vector2D(0,1)};
	
struct TextureData
{
	std::string filename;
	int rows, cols;
};
enum TextureOrder {INIT,MAP_SPRITESHEET, CHAR_SPRITESHEET,DIGITS };
const TextureData textures_data_[NUM_TEXTURES] = {
	//{"filename",n,m}
	{"../images/digits2.jpeg",3,4},
	{"../images/BlueWallsEtc.png",3,10},
	{"../images/characters1.png",4,14},
	{"../images/digits2.jpeg",3,4}
};

class Game
{
public:
	Game();
	~Game();

	void init();
	void load(std::string filename);
	void createPacman(Vector2D pos);
	void createGhost(Vector2D pos,int color);
	void run();

	// Las colisiones con la pared
	bool check_collisionofPacman(Vector2D pos);
	bool check_collisionofGhost(Vector2D pos);
	// Las colisiones entre Pacman y Ghost
	bool check_collisionGhostPacman();
	
	// Diferencia entre comida normal y la Hamburguesa
	void eatFood(Vector2D pos);
	bool isPacmanNyom() { return pacman_->getNyom(); };	//Nyom es la comida


private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	GameMap* map_;
	Pacman* pacman_;
	Ghost* ghost_[NUM_GHOSTS];
	Texture* textures[NUM_TEXTURES];

	void render();
	void update();
	void handleEvents();

	bool exit_ = false;
	int food_left = 0;
};

