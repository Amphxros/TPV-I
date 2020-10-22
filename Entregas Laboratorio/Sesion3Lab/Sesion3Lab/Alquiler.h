#pragma once
#include <iostream>
#include "Date.h"
#include "Coche.h"
class Alquiler
{
public:
	Alquiler(): car_(new Coche()), date_(Date()), days_(-1){};
	Alquiler(Coche* coche, Date date, int dias);

	inline Coche* getCoche() const { return car_; }
	inline Date getDate() const { return date_; }
	inline int getDias() const { return days_; }

	inline void setCoche(Coche* c) { car_ = c; }
	inline void setDate(Date d) { date_ = d; }
	inline void setDays(int d) { days_ = d; }


private:	
	Coche* car_;
	Date date_;
	int days_;
};
