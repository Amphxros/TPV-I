#include "SmartGhost.h"

SmartGhost::SmartGhost(Point2D pos, double width, double height, Texture* texture, Game* game, int color):
	Ghost(pos,width,height,texture,game,color), age_(Age::CHILD)
{
}

void SmartGhost::render()
{
	Ghost::render();
}

void SmartGhost::update()
{
	// preguntar
}
