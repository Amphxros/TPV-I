#pragma once
#include <list>
#include "SDL.h"
#include "checkML.h"
class EventHandler
{
public:
	virtual void handleEvents(SDL_Event& event)=0;
	
	void setItHandler(const std::list<EventHandler*>::iterator& it) { it_ = it; }

protected:
	EventHandler() {}
	std::list<EventHandler*>::iterator it_;

};