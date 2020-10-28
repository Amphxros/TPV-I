#pragma once
#include <string>
#include <SDL.h>

typedef unsigned int uint;
class Texture
{
public:
	Texture();
	Texture(SDL_Renderer* r,std::string filename, int fils=1, int rows=1);
	~Texture();
	void clear();

	int getW();
	int getH();
	uint getNumFils();
	uint getNumCols();

	void load(std::string filename, uint nRows = 1, uint nCols = 1);
	void render(SDL_Rect& dest, SDL_Renderer* renderer);
	void renderFrame(SDL_Rect & dest, SDL_Renderer* renderer);

private:
	SDL_Texture* texture_=nullptr;
	SDL_Renderer* renderer_ = nullptr;

	uint width_=0;
	uint height_=0;
	
	uint fwidth_=0;
	uint fheight_=0;
	
	uint fils=1;
	uint cols=1;


};

