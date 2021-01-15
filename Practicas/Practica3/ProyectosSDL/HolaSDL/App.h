#pragma once
#include "consts.h"
#include <string>
#include "GameStateMachine.h"

enum TextureOrder { 
	INIT,
	MAP_SPRITESHEET,
	CHAR_SPRITESHEET,
	DIGITS,
	BUTTON_MAIN,
	BUTTON_PLAY,
	BUTTON_RESTART,
	BUTTON_RESUME,
	BUTTON_EXIT

};		//orden de las texturas
struct TextureData		//struct que contiene datos importantes de las texturas: nombre, filas y columnas
{
	std::string filename;
	int rows, cols;
};
const TextureData textures_data_[NUM_TEXTURES] = {		//array de datos de textura
	{"../images/digits2.jpeg",3,4},
	{"../images/BlueWallsEtc.png",3,10},
	{"../images/characters1.png",4,14},
	{"../images/digits2.jpeg",3,4},
	
	//buttons
	{"../images/main.png",1,3},
	{"../images/play.png",1,3},
	{"../images/restart.png",1,3},
	{"../images/resume.png",1,3},
	{"../images/exit.png",1,3},

};

class App
{
public:
	App();
	~App();

	void run();
	void quit() { exit_ = true; }
	void play();
	void pause();
	void resume();
	void toMainMenu();

	static void quitApp(App* app);
	static void playGame(App* app);
	static void resume(App* app);
	static void pauseGame(App* app);
	static void toMainMenu(App* app);


private:
	void render();
	void update();
	void handleEvents();

	SDL_Window* window_=nullptr;
	SDL_Renderer* renderer_=nullptr;

	bool exit_=false;
	GameStateMachine* states_=nullptr;
	Texture* textures[NUM_TEXTURES];

};

