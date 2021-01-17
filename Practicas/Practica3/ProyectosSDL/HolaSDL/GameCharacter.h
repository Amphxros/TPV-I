#pragma once
#include "GameObject.h"
#include "checkML.h"

enum directions { LEFT, UP, RIGHT, DOWN };		//enum para las posibles direcciones
const Vector2D dirs_[4] = {			//posibles direcciones
	Vector2D(-1,0),		//izquierda
	Vector2D(0,-1),		//arriba
	Vector2D(1,0),		//derecha
	Vector2D(0,1)		//abajo
};
class PlayState;
class GameCharacter :
    public GameObject
{
public:
    virtual ~GameCharacter();
   
    virtual void render() override;
    virtual void update() override;
	virtual void saveToFile(std::ofstream& file);
	virtual void loadFromFile(std::ifstream& file);

    inline void resetPos() { pos_ = pos_init; }		//resetea la posicion
	inline void setPos(Vector2D pos) { pos_ = pos; }//cambia la posicion
	inline void setPos(int x, int y) { pos_ = Vector2D(x, y); }

  
protected:
	GameCharacter();
    GameCharacter(Point2D pos, double speed, double width, double height, Texture* texture, GameState* game);
   
    Point2D pos_init;	//posicion inicial
    Vector2D dir_;		//direccion actual
	float speed_;		//velocidad
	PlayState* game_state;
   
};

