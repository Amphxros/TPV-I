#pragma once
#include "GameStateMachine.h"
class App
{
public:
	App();
	void run(); 

	void quit() { exit_ = true; };

	static void quitApp(App* app);
	static void playGame(App* app);
	static void resume(App* app);
	static void pauseGame(App* app);
	static void toMainMenu(App* app);

	GameStateMachine* states_;

private:
	SDL_Window* window_ = nullptr; //puntero a ventana
	SDL_Renderer* renderer_ = nullptr; // puntero al renderer

	void init();
	void render();
	void update();
	void handleEvents();
	
	bool exit_;
};

