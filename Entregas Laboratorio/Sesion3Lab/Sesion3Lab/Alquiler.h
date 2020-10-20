#pragma once
#include <iostream>
#include "Date.h"
#include "Coche.h"
class Alquiler
{
public:
	Alquiler(): car_(new Coche()), date_(Date()), days_(-1){};
	Alquiler(Coche* coche, Date date, int dias);

	inline Coche* getCoche() { return car_; }
	inline Date getDate() { return date_; }
	inline int getDias() { return days_; }
private:	
	Coche* car_;
	Date date_;
	int days_;
};

