#pragma once
#include <list>
#include <SDL.h>

#include "checkML.h"
class EventHandler
{
public:
	virtual ~EventHandler(){} //destructora
	virtual bool handleEvents(SDL_Event& event) = 0; //metodo que maneja los eventos
	void setItHandler(const std::list<EventHandler*>::iterator& it) { it_ = it; }

protected:
	EventHandler() {}
	std::list<EventHandler*>::iterator it_; //iterador (necesario para la lista)
};

