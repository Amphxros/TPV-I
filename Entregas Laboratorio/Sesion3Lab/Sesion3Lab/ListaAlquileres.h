#pragma once
#include "Alquiler.h"

class ListaAlquileres
{
public:
	ListaAlquileres(int tam, int lim, Alquiler* list);
	bool LeerAlquiler(std::string filename);
private:
	int tam, limite;
	Alquiler* lista;
};

