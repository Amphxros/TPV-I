#pragma once
#include "GameStateMachine.h"


using uint = unsigned int;

const uint WIN_WIDTH = 800;	//ancho de ventana
const uint WIN_HEIGHT = 800;	//alto de ventana
const uint DELAY = 300;

const uint NUM_TEXTURES = 10;	//numero de texturas



enum TextureOrder { INIT, MAP_SPRITESHEET, CHAR_SPRITESHEET, DIGITS, BUTTONS_PLAY, BUTTONS_QUIT,BUTTON_SAVE,BUTTON_LOAD };		//orden de las texturas
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
	{"../images/play.png",1,3},
	{"../images/exit.png",1,3},
	{"../images/play.png",1,3},
	{"../images/restart.png",1,3},
	{"../images/main.png",1,3} 
};

class App
{
public:
	App();
	~App();
	void run(); 

	void quit() { exit_ = true; };

	static void quitApp(App* app);
	static void playGame(App* app);
	static void resume(App* app);
	static void pauseGame(App* app);
	static void toMainMenu(App* app);

	GameStateMachine* states_;

	Texture* getTexture(TextureOrder order) { return textures[(int)order]; }

private:
	SDL_Window* window_ = nullptr; //puntero a ventana
	SDL_Renderer* renderer_ = nullptr; // puntero al renderer

	void init();
	void render();
	void update();
	void handleEvents();
	
	bool exit_;
	Texture* textures[NUM_TEXTURES]; //array de texturas
};

