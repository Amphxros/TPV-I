#pragma once
#include <string>
#include <SDL.h>
#include "Pacman.h"

const int WIN_WIDTH;
const int WIN_HEIGHT;

const int NUM_TEXTURES=5;
struct TextureData
{
	std::string filename;
	int rows, cols;
};

const TextureData textures_data_[NUM_TEXTURES] = {
	//{"filename",n,m}
	{"wall.png",1,1},
	{"wall.png",1,1}
};

class Game
{
public:
	Game();
	~Game();

	void init();
	void run();
	

private:
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	Pacman* pacman_;

	void render();
	void update();
	void handleEvents();

	bool exit_ = false;
};

