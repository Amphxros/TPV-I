
#include "SDL.h"
#include "SDL_image.h"
#include "checkML.h"
#include <iostream>

using namespace std;

using uint = unsigned int;

const uint TIME_PER_FRAME = 60;
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
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			

			//aqui se renderizan cosas
			SDL_Texture* texture; // Variable para la textura
			string filename = "../images/dog.png"; // Nombre del fichero con la imagen .bmp
			SDL_Surface* surface = IMG_Load(filename.c_str()); // Solo para bmps
			texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface); // Se borra la estructura auxiliar
			// Textura lista para ser usada

			//Tamano de frame
		
			
			bool exit = false;
			//Tamano spritesheet
			int width, height;
			SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

			SDL_Rect dest;
			dest.x = 0;
			dest.y = 0;
			dest.w = 50;
			dest.h = 50;

			while (!exit) {
				SDL_RenderClear(renderer);
			SDL_Rect rect;
			rect.w = width / 6;
			rect.h = height;
			rect.x = width / 6 * (SDL_GetTicks() / TIME_PER_FRAME % 6);
			rect.y = 0;
			dest.x += 1;

			SDL_RenderCopy(renderer, texture, &rect, &dest);
			SDL_Delay(25);
			SDL_RenderPresent(renderer);
			if (dest.x == winHeight)
				dest.x = 0;
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