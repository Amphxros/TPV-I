#pragma once
#include "Coche.h"

class ListaCoches
{
public:
	ListaCoches();
	ListaCoches(int tam, int limite, Coche* list);
	~ListaCoches() {};

	bool cargaCoches(std::string filename);

private:
	int tam, limite;
	Coche* lista;


};
