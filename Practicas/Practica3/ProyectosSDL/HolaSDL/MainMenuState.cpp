#include "MainMenuState.h"

MainMenuState::MainMenuState(App* app)	:	GameState(app)
{

	MenuButton* playbutton = new MenuButton(Vector2D(WIN_WIDTH / 2-75, WIN_HEIGHT / 4), 150, 100, app_->getTexture(TextureOrder::BUTTON_PLAY), this, App::playGame);
	gObjects_.push_back(playbutton); 
	evHandlers_.push_back(playbutton);

	MenuButton* loadbutton = new MenuButton(Vector2D(WIN_WIDTH/2 -75,WIN_HEIGHT/2), 150, 100, app_->getTexture(TextureOrder::BUTTON_RESTART), this, App::loadGame);
	gObjects_.push_back(loadbutton);
	evHandlers_.push_back(loadbutton);

	MenuButton* exitbutton = new MenuButton(Vector2D(WIN_WIDTH / 2-75, 3*WIN_HEIGHT / 4), 150, 100, app_->getTexture(TextureOrder::BUTTON_EXIT), this, App::quitApp);
	gObjects_.push_back(exitbutton);
	evHandlers_.push_back(exitbutton);

}



void MainMenuState::render()
{
	GameState::render();
}

void MainMenuState::update()
{
	//Los updates de los botones estan vacios 
	//como en este estado solo hay botones 
	//no necesita llamarse al GameState::update
}

void MainMenuState::handleEvents(SDL_Event& event)
{
	GameState::handleEvents(event);
}
