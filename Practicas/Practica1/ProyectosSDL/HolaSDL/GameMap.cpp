#include "GameMap.h"
#include <iostream>
#include <fstream>

void GameMap::leeArchivo(string filename) {
	std::ifstream file;
	file.open(filename);

	if(file.is_open()){
		int dimx=0, dimy=0;
		file >> dimx >> dimy;	//Tamaño del mapa

		map = new MapCell*[dimx, dimy];
		char car;	//Auxiliar para lectura

		for(int i=0; i<dimx; i++){
			for(int j=0;j<dimy;j++){
				std::cin >> car;
				switch(car){
				case'0':
					map[i, j] = MapCell::Empty;
					break;
				case'1':
					map[i, j] = MapCell::Wall;
					break;
				case'2':
					map[i, j] = MapCell::Food;
					break;
				case'3':
					map[i, j] = MapCell::Vitamins;
					break;
				default:
					//lanzar algo, como una pelota
					break;
				}
			}
		}
	}


};
void GameMap::escribeArchivo(string filename) {
};