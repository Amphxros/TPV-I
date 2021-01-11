
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "App.h"

using namespace std;

using uint = unsigned int;

void firstTest() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	try {

		App app= App();
		app.run();
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