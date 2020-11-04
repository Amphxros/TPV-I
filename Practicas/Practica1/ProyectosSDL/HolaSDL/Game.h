#pragma once
#include <string>
#include <SDL.h>
#include "Pacman.h"

const int WIN_WIDTH=800;
const int WIN_HEIGHT=600;

const int NUM_TEXTURES=5;
const int TAM_MAT;
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
	void createPacman(Vector2D pos);
	void createGhost(Vector2D pos);
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

