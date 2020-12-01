#pragma once
#include "GameObject.h"
#include <list>

enum directions { LEFT, RIGHT, UP, DOWN };		//enum para las posibles direcciones
const Vector2D dirs_[4] = {			//posibles direcciones
	Vector2D(-1,0),		//izquierda
	Vector2D(1,0),		//derecha
	Vector2D(0,-1),		//arriba
	Vector2D(0,1)		//abajo
};
class Game;
class GameCharacter :
    public GameObject
{
public:
   
    virtual ~GameCharacter();
   
    virtual void render() override;
    virtual void update() override;

    inline void resetPos() { pos_ = pos_init; }
    inline void setItList(const std::list<GameObject*>::iterator& it) { it_ = it; }
protected:
    GameCharacter(): GameObject() {};
    GameCharacter(Point2D pos, double speed, double width, double height, Texture* texture, Game* game);
   
    Point2D pos_init;	//posicion inicial
    Vector2D dir_;		//direccion actual
	float speed_=5;
    std::list<GameObject*>::iterator it_;	//iterador
};

