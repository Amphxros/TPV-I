#include "GameMap.h"
#include <iostream>
#include <fstream>

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
				//para acceder a cada dato
				//switch aqui
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
				//mas casos . . .

				default:
					break;
				}
			}
		}
	}


}
void GameMap::write(std::string filename)
{
}