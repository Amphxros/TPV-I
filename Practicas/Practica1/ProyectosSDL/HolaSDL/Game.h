#pragma once
#include <string>
#include <SDL.h>
#include "Pacman.h"
#include "Ghost.h"
#include "GameMap.h"
const int WIN_WIDTH=800;
const int WIN_HEIGHT=600;

const int NUM_TEXTURES=5;
const int NUM_GHOSTS=4;
const int TAM_MAT=50;
struct TextureData
{
	std::string filename;
	int rows, cols;
};
enum TextureOrder {CHAR_SPRITESHEET,MAP_SPRITESHEET };
const TextureData textures_data_[NUM_TEXTURES] = {
	//{"filename",n,m}
	{"../images/characters1.png",4,14},
	{"../images/BlueWallsEtc.png",3,8},
	{"../images/characters1.png",4,14},	//Pacman y ghosts
	{"../images/digits2.png",3,4}
};

class Game
{
public:
	Game();
	~Game();

	void init();
	void createPacman(Vector2D pos);
	void createGhost(Vector2D pos,int color);
	void run();
	

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
};

