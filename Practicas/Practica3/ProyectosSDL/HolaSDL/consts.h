#pragma once

using uint = unsigned int;

const uint WIN_WIDTH = 800;	//ancho de ventana
const uint WIN_HEIGHT = 800;	//alto de ventana
const uint DELAY = 300;

const uint NUM_TEXTURES = 9;	//numero de texturas

const uint NUM_LEVELS = 5;	//numero total de niveles
const uint NUM_GHOSTS = 4;		//numero de fantasmas
const uint TAM_TILE = WIN_HEIGHT / 35;	//tama�o de tile
const uint NUM_DIRS = 4;		//numero de direcciones

const uint COOLNYOM = 100;	// Variable global de tiempo de duracion del powerup
const uint NUM_VIDAS = 3;		// numero de vidas

const uint TIME_PER_ELECTION = 5;	//numero de movimientos antes de elegir una direccion nueva
const uint TIME_PER_PHASE = 50;		//numero de movimientos antes de cambiar de fase
const uint TIME_PER_REPRODUCTION = 15; //numero de movimientos antes de reproducirse(de lo contrario es incontrolable)

const uint OFFSET = WIN_HEIGHT / 15;	// Para el hueco de las vidas y puntuacion

const uint POINTS_PER_FOOD = 50;		//puntuacion por comida
const uint POINTS_PER_VITAMIN = 500;	//puntuacion por vitamina
const uint POINTS_PER_GHOST = 500;	//puntuacion por fantasma comido

const uint POINTS_PER_LEVEL = 3000; //puntos por nivel

