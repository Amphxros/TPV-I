#include "GameMap.h"
#include <iostream>
#include <fstream>
#include "Game.h"
GameMap::GameMap(int rows, int cols, Texture* texture, Game* game):
rows_(rows),cols_(cols),texture_(texture),game_(game){

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

		for (int i = 0; i < dimy; i++) {
			for (int j = 0; j < dimx; j++) {
				int d;
				file >> d;
				std::cout << d<< " ";
				switch (d) {
				case 0:
					map[i][j] = MapCell::Empty; //por ejemplo
					break;
				case 1:
					map[i][j] = MapCell::Wall; //por ejemplo
					break;
				case 2:
					map[i][j] = MapCell::Food; //por ejemplo
					break;
				case 3:
					map[i][j] = MapCell::Vitamins; //por ejemplo
					break;
				//mas casos para crear fantasmas, pacman etc
				case 5:
					map[i][j] = MapCell::Empty;
					game_->createGhost(Vector2D(TAM_MAT * i, TAM_MAT * j), 1);
					break;
				case 6:
					map[i][j] = MapCell::Empty;
					game_->createGhost(Vector2D(TAM_MAT * i, TAM_MAT * j), 2);
					break;
				case 7:
					map[i][j] = MapCell::Empty;
					game_->createGhost(Vector2D(TAM_MAT * i, TAM_MAT * j), 3);
					break;
				case 8:
					map[i][j] = MapCell::Empty;
					game_->createGhost(Vector2D(TAM_MAT * i, TAM_MAT * j), 4);
					break;
				case 9:
					map[i][j] = MapCell::Empty; //por ejemplo
					game_->createPacman(Vector2D(TAM_MAT * i, TAM_MAT * j));
					break;

				default:
					map[i][j] = MapCell::Empty;
					break;
				}
			}
				std::cout << " " << std::endl;
		}
	}


}
void GameMap::write(std::string filename)
{
}