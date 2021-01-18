#include "EndState.h"
#include "MenuButton.h"
#include <iostream>

EndState::EndState():
	GameState()
{
}

EndState::EndState(App* app): GameState(app)
{
	MenuButton* button = new MenuButton(Vector2D((WIN_WIDTH / 2)-75, (WIN_HEIGHT / 2)-100), 150, 100, app_->getTexture(TextureOrder::BUTTON_MAIN), this, App::toMainMenu);
	std::list<GameObject*>::iterator it_ = gObjects_.insert(gObjects_.end(), button);
	std::list<EventHandler*>::iterator ev_ = evHandlers_.insert(evHandlers_.end(), button);

}

void EndState::render()
{
	GameState::render();
}

void EndState::update()
{
	//Los updates de los botones estan vacios 
	//como en este estado solo hay botones 
	//no necesita llamarse al GameState::update
}

void EndState::handleEvents(SDL_Event& event)
{
	GameState::handleEvents(event);
}

void EndState::saveScores()
{
}

void EndState::loadScores()
{
	std::ifstream file;
	file.open("scores.log");

	if (file.is_open()) {
		for (int i = 0; i < MAX_SCORES; i++) {		
			int m, d, a, p;
			string s;
			file >> s >> p >> d >> m >> a;
			//User u = User(s, p, d, m, a);
			//scores_.emplace(u, i);
			//std::cout << u.name << " " << std::to_string(u.score) << " " <<std::to_string( u.date.d) << "/" << std::to_string(u.date.m) << std::to_string(u.date.a) << std::endl;
		}
	}
	else {
		
	}

}
