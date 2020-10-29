#include "Texture.h"
#include <SDL_image.h>

Texture::Texture()
{
}

Texture::Texture(SDL_Renderer* r, std::string filename, int fils, int cols): renderer_(r)
{
	load(filename, fils, cols);
}

Texture::~Texture()
{
	clear();
}

void Texture::clear()
{
	SDL_DestroyTexture(texture_);
	texture_ = nullptr;
	width_ = height_ = 0;
}

void Texture::load(std::string filename, uint nRows, uint nCols)
{
	SDL_Surface* tmp = IMG_Load(filename.c_str());
	if (tmp == nullptr)
		throw "Error loading " + filename;
	clear();
	texture_ = SDL_CreateTextureFromSurface(renderer_, tmp);
	if (texture_ == nullptr)
		throw "can't load texture " + filename;
	fils = nRows;
	cols = nCols;
	width_ = tmp->w;
	height_ = tmp->h;
	fwidth_ = width_ / fils;
	fheight_ = height_ / cols;
	SDL_FreeSurface(tmp);

}

void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const
{
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = width_; srcRect.h = height_;
	SDL_RenderCopyEx(renderer_, texture_, &srcRect, &destRect, 0, 0, flip);
}

void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const
{
	SDL_Rect srcRect;
	srcRect.x = fwidth_ * col;
	srcRect.y = fheight_ * row;
	srcRect.w = fwidth_;
	srcRect.h = fheight_;
	SDL_RenderCopyEx(renderer_, texture_, &srcRect, &destRect, angle, 0, flip);
}
