#include "GameMap.h"

#include "PlayState.h"
#include <iostream>

GameMap::GameMap(Point2D pos, double width, double height, int rows, int cols, Texture* texture, GameState* game):
	GameObject(pos,width,height,texture,game), rows_(rows), cols_(cols), game_state(static_cast<PlayState*>(game))
{
	map = new MapCell * [cols_];

	// Inicializacion por defecto a Empty
	for (int i = 0; i < cols_; i++) {
		map[i] = new MapCell[rows_];
		for (int j = 0; j < rows_; j++)
			map[i][j] = MapCell::Empty;
	}
}

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
			
			dest.x = pos_.getX()+(i * width_);	// OFFSET es el tama�o de la barra
			dest.y = pos_.getY()+ (j * height_);
			dest.w = width_;
			dest.h = height_;

			if (map[i][j] == MapCell::Wall) { //muro
				texture_->renderFrame(dest, 1, 7);
			}

			else if (map[i][j] == MapCell::Food) { //comida
				texture_->renderFrame(dest, 2, 9);
			}

			else if (map[i][j] == MapCell::Vitamins) { //vitaminas
				dest.w += 5;
				dest.h += 5;
				texture_->renderFrame(dest, 2, 8);
			}
		}
	}
}


bool GameMap::IntersectWall(SDL_Rect dest)
{
	Point2D topLeft = game_state->SDLPointToMapCoords(Point2D(dest.x, dest.y)); //pos x + i * width, pos y + j * height
	Point2D botRight = game_state->SDLPointToMapCoords(Point2D(dest.x + (dest.w/2), dest.y + (dest.h/2))); //el margen es porque de lo contrario no se mueve 
	bool b = false;
	for (int y = topLeft.getY(); y <= botRight.getY(); y++) {
		for (int x = topLeft.getX(); x <= botRight.getX(); x++) {
			
			if (map[x][y] == MapCell::Wall) {
				b=true; 
			}
		}
	}
	return b;
}

bool GameMap::IntersectFood(SDL_Rect dest){
	Point2D topLeft = game_state->SDLPointToMapCoords(Point2D(dest.x, dest.y)); //pos x + i * width, pos y + j * height
	Point2D botRight = game_state->SDLPointToMapCoords(Point2D(dest.x + dest.w, dest.y + dest.h));

	bool b = false;
	for (int y = topLeft.getY(); y < botRight.getY(); y++) {
		for (int x = topLeft.getX(); x < botRight.getX(); x++) {
			if (map[x][y] != MapCell::Wall && map[x][y] != MapCell::Empty) {
			
				if (map[x][y] == MapCell::Vitamins) {
					game_state->addPoints(POINTS_PER_VITAMIN);
					b = true;
				}
				else {
					game_state->addPoints(POINTS_PER_FOOD);
				}
				write(x, y, MapCell::Empty);
			}
		}
	}
	return b;
}
