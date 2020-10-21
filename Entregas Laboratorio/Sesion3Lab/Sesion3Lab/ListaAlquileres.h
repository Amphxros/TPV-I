#pragma once
#include <iostream>

#include "Alquiler.h"
#include "ListaCoches.h"
#include "Date.h"

using namespace std;

class ListaAlquileres
{

public:
	ListaAlquileres() {};
	ListaAlquileres(int t, int lim, Alquiler* list, ListaCoches listcoches);
	~ListaAlquileres() {};

	bool LeerAlquiler(std::string filename);
	void MostrarAlquiler();
	void OrdenaAlquiler(ListaAlquileres& l);

	bool ComparaFechas(Alquiler primera, Alquiler segunda);
	inline Alquiler* getLista() { return lista; }
	inline int getTam() { return tam; }


private:
	int tam, limite;
	Alquiler* lista;
	ListaCoches lista_;
};