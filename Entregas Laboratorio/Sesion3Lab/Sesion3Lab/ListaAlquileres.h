#pragma once
#include "Alquiler.h"

class ListaAlquileres
{
public: 
	ListaAlquileres() {
	
	};
	ListaAlquileres~() {};

	void OrdenaAlquileres();
	void MostrarAlquileres();

	private:
		int tam, limite;
		Alquiler* lista;
};

