
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>

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
			SDL_Texture* texture; // Variable para la textura
			string filename = "../images/dog.png"; // Nombre del fichero con la imagen .bmp
			SDL_Surface* surface = IMG_Load(filename.c_str()); // Solo para bmps
			texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface); // Se borra la estructura auxiliar
		
			SDL_Texture* bg; // Variable para la textura
			filename = "../images/background1.png"; // Nombre del fichero con la imagen .bmp
			surface = IMG_Load(filename.c_str()); // Solo para bmps
			bg = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface); // Se borra la estructura auxiliar
		
			SDL_Rect dest;
			dest.x = 0;
			dest.y = 500;
			dest.w = 100;
			dest.h = 100;
			
			SDL_Rect b;
			b.x = 0;
			b.y = 0;
			b.w = 800;
			b.h = 600;
			bool exit = false;
			//Tamano spritesheet
			while (!exit)
			{
				SDL_RenderClear(renderer);

				render(bg, b, renderer);
				renderFrame(texture,dest,renderer);
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