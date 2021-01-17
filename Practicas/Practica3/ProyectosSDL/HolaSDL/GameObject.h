#pragma once
#include "Vector2D.h"
#include <fstream>
#include <SDL.h>
#include <list>
#include "Texture.h"

#include "checkML.h"
class GameState;
class GameObject
{
public:
	virtual ~GameObject() { texture_ = nullptr; game_ = nullptr; }
	virtual void render()=0;
	virtual void update()=0;

	SDL_Rect getdest() { return SDL_Rect{ (int)pos_.getX(), (int)pos_.getY(), (int)width_, (int)height_ }; }

	inline void setItList(const std::list<GameObject*>::iterator& it) { it_ = it; }
	inline std::list<GameObject*>::iterator getIt() { return it_;}

	inline double getWidth() { return width_; }
	inline double getHeight() { return height_; }
	inline Point2D getPos() { return pos_; }

protected:
	GameObject() :pos_(Point2D(-1, -1)), width_(0), height_(0) { throw "objeto nulo"; };
	GameObject(Point2D pos, double width, double height, Texture* texture, GameState* game):
		pos_(pos), width_(width),height_(height), texture_(texture),game_(game) {}

	Point2D pos_;				//posicion
	double width_, height_;		//width y height seran igual a la constante de tile generalmente
	GameState* game_ = nullptr;		//puntero a gamestate
	Texture* texture_= nullptr;	//textura
	
	std::list<GameObject*>::iterator it_;	//iterador
};

