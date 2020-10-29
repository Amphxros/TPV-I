
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Texture.h"
#include "Dog.h"

using namespace std;

using uint = unsigned int;

const uint TIME_PER_FRAME = 60;

void handleEvents( bool& exit) {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT)
			exit = true;
		else if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE)
				exit = true;
		}
	}
}
void firstTest() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	const uint winWidth = 800;
	const uint winHeight = 600;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		cout << "Error cargando SDL" << endl;
	else {
		Texture* bg = new Texture(renderer, "../images/background1.png");
		Texture* dog_texture = new Texture(renderer, "../images/dog.png", 1, 6);
		Dog* dog = new Dog(0, 300, 5, 350, 350, dog_texture);
		bool exit = false;
		while (!exit)
		{
			SDL_RenderClear(renderer);
			bg->render({ 0,0,800,600 }, SDL_FLIP_NONE);
			dog->render();
			dog->update();
			SDL_RenderPresent(renderer);
			handleEvents(exit);
			SDL_Delay(30);
		}
		
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* argv[]){
	firstTest();
	return 0;
}