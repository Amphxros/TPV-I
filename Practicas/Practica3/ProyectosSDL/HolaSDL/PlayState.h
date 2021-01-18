#pragma once
#include <string>
#include <SDL.h>

#include "Vector2D.h"
#include "Pacman.h"
#include "Ghost.h"
#include "InfoBar.h"
#include "Pacman.h"
#include "GameMap.h"

#include "checkML.h"
#include "consts.h"
#include "GameState.h"
	

const std::string map_name[NUM_LEVELS] = {		//array de datos de los ficheros del mapa
	{"../Mapas/level01.dat"},
	{"../Mapas/level02.dat"},
	{"../Mapas/level03.dat"},
	{"../Mapas/level04.dat"},
	{"../Mapas/level05.dat"}
};

///clase Game
class PlayState: public GameState
{
public:
	
	PlayState():GameState(), level_(-1){}
	//constructora
	PlayState(App* app);
	//destructora
	virtual ~PlayState();

	virtual void render();  //renderiza los elementos del juego
	virtual void update();  //actualiza los elementos de juego(posiciones, control de colisiones ...)
	virtual void handleEvents(SDL_Event& event);	// Controla la salida del juego y los eventos de Pacman

	void saveToFile();
	//carga el fichero seed.pac
	void loadFromFile(int seed);

	//eleimina todos los objetos de gObjects_
	void clear();

	//crea un pacman en una pos dada
	void createPacman(Vector2D pos);
	//crea un fantasma en una pos dada
	void createGhost(Vector2D pos,int color);
	//crea un smart ghost
	void createSmartGhost(Vector2D pos);
	

	void deleteGhost(std::list<GameObject*>::iterator it, std::list<Ghost*>::iterator git);
	
	//GetWidth/height son los pixeles del tile
	Point2D SDLPointToMapCoords(Point2D mapCoor) const { return Point2D((int)(mapCoor.getX() / map_->getWidth()), (int)(mapCoor.getY() / map_->getHeight())); }

	bool tryMove(SDL_Rect rect, Vector2D dir, Point2D& newPos);
	bool eatFood(SDL_Rect rect,Point2D& newPos );

	bool CollisionWithGhosts(Pacman* g);
	bool CollisionBetweenGhosts(Ghost* g);
	
	// Diferencia entre comida normal y la Hamburguesa
	bool isPacmanNyom() { return pacman_->getNyom(); };	//Nyom es si nos hemos tomado las vitaminas
	int getVidas() { return pacman_->getVidas(); }

	int getSwapX() { return dim_map_x-1; } //devuelve la posicion limite del mapa en x
	int getSwapY() { return dim_map_y-1; } //devuelve la posicion limite en y
	void addPoints(int points) { infoBar_->setPuntos(infoBar_->getPuntos() + points); }

private:

	GameMap* map_=nullptr; //mapa
	Pacman* pacman_=nullptr;// pacman
	InfoBar* infoBar_=nullptr;

	std::list<Ghost*>ghosts_;	//lista de fantasmas
	
	
	

	//creacion de texturas y objetos
	void init();
	// Carga del mapa desde el archivo.dat
	void load(std::string filename);
	// pasa de nivel
	void nextLevel();

	
	int dim_map_x = 0;
	int dim_map_y = 0;
	int level_;

	int num_ghosts = 0;
};
