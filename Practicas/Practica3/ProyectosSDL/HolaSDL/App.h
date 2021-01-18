#pragma once
#include "consts.h"
#include <string>
//#include <SDL_ttf.h>
#include "GameStateMachine.h"
#include "checkML.h"

//enum de texturas
enum class TextureOrder { 
	INIT,
	MAP_SPRITESHEET,
	CHAR_SPRITESHEET,
	DIGITS,
	BUTTON_MAIN,
	BUTTON_PLAY,
	BUTTON_RESTART,
	BUTTON_RESUME,
	BUTTON_EXIT

};		

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
	{"../images/exit.png",1,3}

};

class App
{
public:
	//constructora
	App();
	//destructra
	~App();
	//bucle principal
	void run();
	//quit-> quita la app
	void quit() { exit_ = true; }
	//inicia una partida
	void play();
	//pausa el juego
	void pause();
	//vuelve a la partida
	void resume();
	//guarda el juego
	void saveGame();
	//carga el juego
	void loadGame();
	//vuelve al menu
	void toMainMenu();
	//termina el juego
	void endGame();

	//callbacks
	static void quitApp(App* app);
	static void playGame(App* app);
	static void resume(App* app);
	static void pauseGame(App* app);
	static void toMainMenu(App* app);
	static void saveGame(App* app);
	static void loadGame(App* app);

	//devuelve una textura textures[(int)t]
	Texture* getTexture(TextureOrder t) { return textures[(int)t]; }

private:
	//renderiza el estado actual
	void render();
	//actualiza el estado actual
	void update();
	//maneja los eventos del estado actual
	void handleEvents();

	//puntero a la ventana
	SDL_Window* window_=nullptr;
	//puntero al renderer
	SDL_Renderer* renderer_=nullptr;


	bool exit_=false;
	GameStateMachine* states_=nullptr; //maquina de estados
	Texture* textures[NUM_TEXTURES]; //array de texturas
	
	//TTF_Font* font;
};

