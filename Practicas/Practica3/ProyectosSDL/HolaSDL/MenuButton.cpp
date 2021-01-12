#include "MenuButton.h"

MenuButton::MenuButton(): 
	GameObject(), EventHandler(), state(ButtonState::NORMAL){}

MenuButton::MenuButton(Point2D pos, double width, double height, Texture* texture, GameState* game_, CallBack* callback):
	GameObject(pos,width,height,texture,game_), EventHandler(), callback_(callback),state(ButtonState::NORMAL){}

MenuButton::~MenuButton()
{
}

void MenuButton::render()
{
	SDL_Rect dest = getdest();
	texture_->renderFrame(dest, 0, (int)state);
}

void MenuButton::update() { }

void MenuButton::handleEvents(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		SDL_Point cursor_pos = { event.button.x, event.button.y };
		if (SDL_PointInRect(&(cursor_pos), &getdest())) { //clickando el boton y estando en el boton
			state = ButtonState::PRESSED;
			if(callback_!=nullptr)
				callback_(game_->getApp());
		}
		break;

	case SDL_MOUSEMOTION:
        SDL_Point cursor_pos = { event.button.x, event.button.y };
        if(SDL_PointInRect(&(cursor_pos), &getdest())) { //dentro del boton pero sin clickar
			state = ButtonState::HIGHLIGHT;
        }
		else {  // Cualquier posicion que no sea en el boton
			state = ButtonState::NORMAL;
		}
		break;

	default:
		break;
	}
}
