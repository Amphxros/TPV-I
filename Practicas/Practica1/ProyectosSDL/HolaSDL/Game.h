#pragma once
#include <string>
#include <SDL.h>

#include "Vector2D.h"
#include "Pacman.h"
#include "Ghost.h"
#include "InfoBar.h"
#include "GameMap.h"
#include "checkML.h"

const int WIN_WIDTH=800;	//ancho de ventana
const int WIN_HEIGHT=600;	//alto de ventana

const int NUM_TEXTURES=4;	//numero de texturas
const int NUM_GHOSTS=4;		//numero de fantasmas
const int TAM_MAT = WIN_HEIGHT/35;	//tama�o de tile
const int NUM_DIRS = 4;		//numero de direcciones

const int COOLNYOM = 3000;
const int TIME_PER_FRAME = 50;
const int OFFSET = WIN_HEIGHT / 15;	// Para el hueco de las vidas y puntuacion


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

	//crea un pacman en una pos dada
	void createPacman(Vector2D pos);
	//crea un fantasma en una pos dada
	void createGhost(Vector2D pos,int color);
	//bucle principal
	void run();

	// Las colisiones con la pared
	bool check_collisionofPacman(Vector2D pos);
	//colisiones de un fantasma con el entorno
	bool check_collisionofGhost(Vector2D pos);
	// Las colisiones entre Pacman y Ghost
	bool check_collisionGhostPacman();
	
	// Diferencia entre comida normal y la Hamburguesa
	void eatFood(Vector2D pos);
	bool isPacmanNyom() { return pacman_->getNyom(); };	//Nyom es si nos hemos tomado las vitaminas
	int getVidas() { return pacman_->getVidas(); }

	int getSwapX() { return dim_map_x-1; } //devuelve la posicion limite del mapa en x
	int getSwapY() { return dim_map_y-1; } //devuelve la posicion limite en y

private:
	SDL_Window* window_=nullptr; //puntero a ventana
	SDL_Renderer* renderer_=nullptr; // puntero al renderer

	GameMap* map_=nullptr; //mapa
	Pacman* pacman_=nullptr;// pacman
	Ghost* ghost_[NUM_GHOSTS];//array de fantasmas
	Texture* textures[NUM_TEXTURES]; //array de texturas
	Vector2D posicionesInit[NUM_GHOSTS + 1];	// Posiciones iniciales de fantasma(s) y pacman para que vuelvan
	InfoBar* infoBar_=nullptr;

	void render();  //renderiza los elementos del juego
	void update();  //actualiza los elementos de juego(posiciones, control de colisiones ...)
	void handleEvents();	// Controla la salida del juego y los eventos de Pacman
	
	//creacion de texturas y objetos
	void init();
	//carga del mapa
	void load(std::string filename);

	bool exit_ = false;
	int food_left = 0;

	int dim_map_x = 0;
	int dim_map_y = 0;
};

