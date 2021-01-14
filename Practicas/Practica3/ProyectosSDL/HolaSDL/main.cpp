
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Game.h"

using namespace std;

using uint = unsigned int;

void firstTest() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	try {

		string carga_;
		std::cout << "jugar(p) o cargar partida(c)?"<<std::endl;
		std::cin >> carga_;
		do{
			std::cout << "Introducir (p) o (c)"<<std::endl;
			std::cin >> carga_;
		} while (carga_ != "p" && carga_ != "c");

		Game g = Game();
		
		if (carga_ == "c") {
			int seed;
			std::cout << "Introduce codigo: ";
			std::cin >> seed;
			g.loadFromFile(seed);
		}
		g.run();
	}
	catch(std::string s){
		std::cout << s;
	}
	SDL_Quit();
}

int main(int argc, char* argv[]){
	firstTest();
	return 0;
}