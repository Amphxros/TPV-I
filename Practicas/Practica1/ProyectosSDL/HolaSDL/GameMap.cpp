#include "GameMap.h"

#include "Game.h"
#include <iostream>

GameMap::GameMap(int rows, int cols, Texture* texture, Game* game):
rows_(rows),cols_(cols),texture_(texture),game_(game){
	map = new MapCell * [cols_];

	for (int i = 0; i < cols_; i++) {
		map[i] = new MapCell[rows_];
		for(int j=0;j<rows_;j++)
			map[i][j] = MapCell::Empty;
	}

}
// Esto peta de momento
GameMap::~GameMap()
{
	for (int i = 0; i < rows_; i++) {
		delete map[i];
	}
	delete map; map = nullptr;
}

void GameMap::render()
{ 
	for (int i = 0; i < cols_; i++) {
		for (int j = 0; j < rows_; j++) {
			SDL_Rect dest;
			dest.x = (i * TAM_MAT) + OFFSET;	// OFFSET es el tamaño de la barra
			dest.y = (j * TAM_MAT) + OFFSET;
			dest.w = TAM_MAT;
			dest.h = TAM_MAT;

			if (map[i][j] == MapCell::Wall) {
				texture_->renderFrame(dest, 1, 7);
			}

			else if (map[i][j] == MapCell::Food) {
				texture_->renderFrame(dest, 2, 9);
			}

			else if (map[i][j] == MapCell::Vitamins) {
				texture_->renderFrame(dest, 2, 8);
			}
		}
	}
}
