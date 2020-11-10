#include "GameMap.h"
#include <iostream>
#include <fstream>
#include "Game.h"
GameMap::GameMap(int rows, int cols, Texture* texture, Game* game):
rows_(rows),cols_(cols),texture_(texture),game_(game){

}
GameMap::~GameMap()
{
}
void GameMap::load(string filename) {
	std::ifstream file;
	file.open(filename);

	if(file.is_open()){
		int dimx=0, dimy=0;
		file >> dimx >> dimy;	//Tamaño del mapa

		map = new MapCell*[dimy];
		for(int i=0;i<dimy;i++){
			map[i] = new MapCell[dimx];
		}

		/* para borrar
		for(i,fils,i++)
		delete map[i];
		
		delete map
		*/

		for (int i = 0; i < dimx; i++) {
			for (int j = 0; j < dimy; j++) {
				int d;
				file >> d;
				std::cout << d<< " ";
				switch (d) {
				case 0:case 1:case 2:case 3:
					map[j][i] =(MapCell)d; //por ejemplo
					break;

				//mas casos para crear fantasmas, pacman etc
				case 5:case 6:case 7:case 8:
					map[j][i] = MapCell::Empty;
					game_->createGhost(Vector2D(j, i), d-5);
					break;
				
				case 9:
					map[j][i] = MapCell::Empty; //por ejemplo
					game_->createPacman(Vector2D( j,i));
					break;

				default:
					map[j][i] = MapCell::Empty;
					break;
				}
			}
				std::cout << " " << std::endl;
		}
		rows_ = dimx;
		cols_ = dimy;
	}
}
void GameMap::write(std::string filename)
{
}

void GameMap::render()
{
	for (int i = 0; i < cols_; i++) {
		for (int j = 0; j < rows_; j++) {
			SDL_Rect dest;
			dest.x = i * TAM_MAT;
			dest.y = j * TAM_MAT;
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
