#pragma once
#include "Coche.h"

class ListaCoches
{
public:

	// La creacion pasa por el metodo de lectura del archivo
	ListaCoches() { 
		lista->CargaCoches(); 
	};
	ListaCoches~ {};

	private:
		int tam, limite;
		Coche* lista;


};

