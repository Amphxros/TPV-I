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
const int WIN_HEIGHT=800;	//alto de ventana

const int NUM_LEVELS=4;
const int NUM_TEXTURES=4;	//numero de texturas
const int NUM_GHOSTS=4;		//numero de fantasmas
const int TAM_MAT = WIN_HEIGHT/35;	//tama�o de tile
const int NUM_DIRS = 4;		//numero de direcciones

const int COOLNYOM = 10000;
const int TIME_PER_FRAME = 50;
const int OFFSET = WIN_HEIGHT / 15;	// Para el hueco de las vidas y puntuacion

const int POINTS_PER_FOOD=50;
const int POINTS_PER_VITAMIN=500;
const int POINTS_PER_GHOST=500;

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

	const std::string map_name[NUM_LEVELS] = {		//array de datos de los ficheros del mapa
		{"../Mapas/level01.dat"},
		{"../Mapas/level02.dat"},
		{"../Mapas/level03.dat"},
		{"../Mapas/level04.dat"}
		//{"../Mapas/level05.dat"},
	};

	enum State { START,PLAYING,GAMEOVER,WIN };
///clase Game
class Game
{
public:
	//constructora
	Game();
	//destructora
	~Game();

	//bucle principal
	void run();

	//crea un pacman en una pos dada
	void createPacman(Vector2D pos);
	//crea un fantasma en una pos dada
	void createGhost(Vector2D pos,int color);
	//crea un smart ghost
	void createSmartGhost(Vector2D pos);
	
	
	bool CollisionWithWalls(GameObject* g);
	bool CollisionWithGhosts(GameObject* g);
	
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
	Texture* textures[NUM_TEXTURES]; //array de texturas
	InfoBar* infoBar_=nullptr;

	std::list<Ghost*>ghosts_;	//lista de fantasmas
	std::list<GameObject*> gObjects_; //lista de GO (mapa, barra de vida, fantasmas, pacman ...)

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

