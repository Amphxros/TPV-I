// G13
// Amparo Rubio Bellon
// Jorge Zurdo Izquierdo
#pragma once
#include <iostream>

#include "Alquiler.h"
#include "ListaCoches.h"
#include "Date.h"

using namespace std;

class ListaAlquileres
{

public:
	ListaAlquileres();
	ListaAlquileres(int t, int lim, ListaCoches listcoches);
	~ListaAlquileres() { delete alquileres; };

	bool LeerAlquiler(std::string filename);
	void MostrarAlquiler();
	void OrdenaAlquiler() const;

	bool ComparaFechas(Alquiler primera, Alquiler segunda);
	inline Alquiler* getLista() { return alquileres; }
	inline int getTam() { return tam; }


private:
	int tam, limite;
	Alquiler* alquileres;
	ListaCoches lista_coches;
};