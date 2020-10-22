#pragma once
#include "Coche.h"

class ListaCoches
{
public:
	ListaCoches();
	ListaCoches(int tam, int limite);
	~ListaCoches() { delete lista; };

	bool cargaCoches(std::string filename);
	Coche* buscaCoche(int code);

	inline int getTam() const { return tam; }
private:
	int tam, limite;
	Coche* lista;


};
