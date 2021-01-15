
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Game.h"
#include "App.h"

using namespace std;

using uint = unsigned int;

void firstTest() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	try {
		
		App g = App();
		g.run();
		
		/*if (carga_ == "c") {
			int seed;
			std::cout << "Introduce codigo: ";
			std::cin >> seed;
			g.loadFromFile(seed);
		}*/

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