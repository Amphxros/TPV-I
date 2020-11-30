#pragma once
#include "Vector2D.h"
#include <fstream>
#include <SDL.h>
#include "Texture.h"
class Game;
class GameObject
{
public:
	~GameObject() { texture_ = nullptr; game_ = nullptr; }
	virtual void render()=0;
	virtual void update()=0;

	//virtual void saveToFile(std::ofstream & file );
	//virtual void loadFromFile(const std::ifstream & file );

	SDL_Rect getdest() { return SDL_Rect{ (int)pos_.getX(), (int)pos_.getY(),(int)width_, (int)height_ }; }

protected:
	GameObject():pos_(Point2D(-1,-1)), width_(0), height_(0){};
	GameObject(Point2D pos, double width, double height, Texture* texture, Game* game):
		pos_(pos), width_(width),height_(height), texture_(texture),game_(game) {}

	Point2D pos_;				//posicion
	double width_, height_;		//width y height seran igual a la constante de tile generalmente
	Game* game_ = nullptr;		//puntero a game
	Texture* texture_= nullptr;	//textura
};

