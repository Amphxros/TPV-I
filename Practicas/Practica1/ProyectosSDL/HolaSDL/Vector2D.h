#pragma once

#include "checkML.h"
class Vector2D
{
public:
	Vector2D() :x_(0),y_(0){};
	Vector2D(int x, int y) :x_(x), y_(y) {};
	~Vector2D() {};

	double getX() { return x_; };	//devuelve x
	double getY() { return y_; };	//devuelve y (para sorpresa de muchos)
	//suma de vectores
	Vector2D operator+(Vector2D& v) { return Vector2D(x_ + v.getX(), y_ + v.getY()); };
	//resta de vectores
	Vector2D operator-(Vector2D & v) { return Vector2D(x_ - v.getX(), y_ - v.getY()); };
	//Deteccion automatica de producto escalar o vectorial
	Vector2D operator*(double dragon) { return Vector2D(dragon * x_, dragon * y_); };
	Vector2D operator*(Vector2D& v) { return Vector2D(v.getX() * x_, v.getY() * y_); };
	//Compara cordenadas x e y de vectores
	bool operator==(Vector2D& v) { return ((v.getX() == x_) && (v.getY() == y_)); };

private:
	double x_,y_;
};
using Point2D = Vector2D;
