#pragma once
#include <string>
#include <SDL.h>

typedef unsigned int uint;
class Texture
{
public:
	Texture();
	Texture(SDL_Renderer* r ,std::string filename, int fils=1, int cols=1);
	~Texture();

	inline uint getW() const { return width_; };
	inline uint getH() const { return height_; };
	inline uint getNumFils() const { return fils; };
	inline uint getNumCols() const { return cols; };

	void load(std::string filename, uint nRows = 1, uint nCols = 1);
	void render(const SDL_Rect& destRect, SDL_RendererFlip flip) const;
	void renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const;

private:
	
	SDL_Texture* texture_=nullptr;
	SDL_Renderer* renderer_ = nullptr;

	uint width_=0;
	uint height_=0;
	
	uint fwidth_=0;
	uint fheight_=0;
	
	uint fils=1;
	uint cols=1;

	void clear();

};

