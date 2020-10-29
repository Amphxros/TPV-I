
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>
#include "Texture.h"
#include "Dog.h"

using namespace std;

using uint = unsigned int;

const uint TIME_PER_FRAME = 60;
void renderFrame(SDL_Texture* texture, SDL_Rect & dest, SDL_Renderer* renderer) {
	int width, height;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	SDL_Rect rect;
	rect.w = width / 6;
	rect.h = height;
	rect.x = width / 6 * (SDL_GetTicks() / TIME_PER_FRAME % 6);
	rect.y = 0;
	dest.x += 5;

	SDL_RenderCopy(renderer, texture, &rect, &dest);
	SDL_RenderPresent(renderer);
	if (dest.x == 600)
		dest.x = 0;
}

void render(SDL_Texture* texture, SDL_Rect & dest, SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, nullptr, &dest);
	SDL_RenderPresent(renderer);
}

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
		Texture* dog_texture = new Texture(renderer, "./images/dog.png", 1, 6);
		Dog* dog = new Dog(0, 500, 5, 100, 100, dog_texture);
		while (!exit)
		{
			dog->render();
			dog->update();
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