#pragma once
#include <string>
#include <SDL.h>
#include "Vector2D.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GameMap.h"
#include "checkML.h"

const int WIN_WIDTH=800;	//ancho de ventana
const int WIN_HEIGHT=800;	//alto de ventana

const int NUM_TEXTURES=4;	//numero de texturas
const int NUM_GHOSTS=4;		//numero de fantasmas
const int TAM_MAT=WIN_HEIGHT/30;	//tamaño de tile
const int NUM_DIRS = 4;		//numero de direcciones

const int OFFSET = WIN_HEIGHT / 15;
enum directions { LEFT, RIGHT, UP, DOWN };		//enum para las posibles direcciones
	const Vector2D dirs_[NUM_DIRS] = {			//posibles direcciones
		Vector2D(-1,0),		//izquierda
		Vector2D(1,0),		//derecha
		Vector2D(0,-1),		//arriba
		Vector2D(0,1)		//abajo
	};
	
enum TextureOrder {INIT,MAP_SPRITESHEET, CHAR_SPRITESHEET,DIGITS };		//orden de las texturas
struct TextureData		//struct que contiene datos importantes de las texturas: nombre, filas y columnas
{
	std::string filename;
	int rows, cols;
};
	const TextureData textures_data_[NUM_TEXTURES] = {		//array de datos de textura
		//{"filename",n,m}
		{"../images/digits2.jpeg",3,4},
		{"../images/BlueWallsEtc.png",3,10},
		{"../images/characters1.png",4,14},
		{"../images/digits2.jpeg",3,4}
	};

///clase Game
class Game
{
public:
	//constructora
	Game();
	//destructora
	~Game();

	//creacion de texturas y objetos
	void init();
	//carga del mapa
	void load(std::string filename);
	//crea un pacman en una pos dada
	void createPacman(Vector2D pos);
	//crea un fantasma en una pos dada
	void createGhost(Vector2D pos,int color);
	//bucle principal
	void run();
	
	//metodos que comprueban colisiones

	//colisiones del pacman con el entorno
	bool check_collisionofPacman(Vector2D pos);
	//colisiones de un fantasma con el entorno
	bool check_collisionofGhost(Vector2D pos);
	//colisiones entre el fantasma y el pacman
	bool check_collisionGhostPacman();
	
	//metodo donde el pacman come
	void eatFood(Vector2D pos);
	//devuelve si el pacman ha comido comida
	bool isPacmanNyom() { return pacman_->getNyom(); };

	int getSwapX() { return dim_map_x-1; }
	int getSwapY() { return dim_map_y-1; }

private:
	SDL_Window* window_=nullptr;
	SDL_Renderer* renderer_=nullptr;

	GameMap* map_=nullptr;
	Pacman* pacman_=nullptr;
	Ghost* ghost_[NUM_GHOSTS];
	Texture* textures[NUM_TEXTURES];

	void render();
	void update();
	void handleEvents();

	bool exit_ = false;
	int food_left = 0;

	int dim_map_x = 0;
	int dim_map_y = 0;
};

