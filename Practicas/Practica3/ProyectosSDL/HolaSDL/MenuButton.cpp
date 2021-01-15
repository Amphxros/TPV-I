#include "MenuButton.h"
#include "App.h"

MenuButton::MenuButton():
	GameObject(), EventHandler(), call_back_(nullptr)
{
}

MenuButton::MenuButton(Point2D pos, double width, double height, Texture* texture, GameState* game, CallBack* cb):
	GameObject(pos,width,height,texture,game), EventHandler(), call_back_(cb),click(NORMAL)
{
}

MenuButton::~MenuButton()
{
}

void MenuButton::render()
{
	SDL_Rect dest = getdest();
	texture_->renderFrame(dest, 1, (int)click);
}

void MenuButton::update()
{
}

bool MenuButton::handleEvents(SDL_Event& event)
{
	SDL_Point cursor_pos = { event.button.x, event.button.y };
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (SDL_PointInRect(&(cursor_pos), &getdest())) { //clickando el boton y estando en el boton
			click = State::CLICKED;
			if (call_back_ != nullptr)
				call_back_(game_->getApp());
		}
		break;

	case SDL_MOUSEMOTION:

		if (SDL_PointInRect(&(cursor_pos), &getdest())) { //dentro del boton pero sin clickar
			click = State::HIGHLIGHTED;
		}
		else {  // Cualquier posicion que no sea en el boton
			click = State::NORMAL;
		}
		break;

	default:
		break;
	}

	return false;
}
