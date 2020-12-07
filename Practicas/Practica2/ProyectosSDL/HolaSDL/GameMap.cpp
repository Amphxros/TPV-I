#include "GameMap.h"

#include "Game.h"
#include <iostream>

GameMap::GameMap(Point2D pos, double width, double height, int rows, int cols, Texture* texture, Game* game):
	GameObject(pos,width,height,texture,game), rows_(rows), cols_(cols)
{
	map = new MapCell * [cols_];

	for (int i = 0; i < cols_; i++) {
		map[i] = new MapCell[rows_];
		for (int j = 0; j < rows_; j++)
			map[i][j] = MapCell::Empty;
	}
}

GameMap::~GameMap()
{
	for (int i = 0; i < rows_; i++) {
		delete []map[i];
	}
	delete map; map = nullptr;
}

void GameMap::render()
{ 
	for (int i = 0; i < cols_; i++) {
		for (int j = 0; j < rows_; j++) {
			SDL_Rect dest;
			
			dest.x = pos_.getX()+(i * width_);	// OFFSET es el tamaño de la barra
			dest.y = pos_.getY()+ (j * height_);
			dest.w = width_;
			dest.h = height_;

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

bool GameMap::IntersectWall(SDL_Rect dest)
{
	Point2D topLeft = game_->SDLPointToMapCoords(Point2D(dest.y, dest.x));
	Point2D botRight = game_->SDLPointToMapCoords(Point2D(dest.y + height_ - 1, dest.x + width_- 1));

	for (int y = topLeft.getY(); y <= botRight.getY(); y++) {
		for (int x = topLeft.getX(); x <= botRight.getX(); x++) {
			if (map[y][x] == MapCell::Wall) {
				return true; 
			}
		}
	}
	return false;
}
