#pragma once
#include "Coche.h"

class ListaCoches
{
public:
	ListaCoches();
	ListaCoches(int tam, int limite, Coche* list);

	bool cargaCoches(std::string filename);

	Coche* buscaCoche(int code);
	
	inline int getTam() { return tam; }
	inline int getLimite() { return limite; }
	inline Coche* getLista() { return lista; }

private:
	int tam, limite;
	Coche* lista;
};
