// G13
// Amparo Rubio Bellón
// Jorge Zurdo Izquierdo

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "ListaCoches.h"
#include "ListaAlquileres.h"

int main() {
	//listas
	ListaCoches coches_ = ListaCoches();
	ListaAlquileres alquileres_ = ListaAlquileres();
	//lectura
	coches_->CargaCoches(coches_);
	alquileres_->leerAlquiler(alquileres_, coches_);		// Necesita coches para añadir nullptr si uno no existe
	alquileres_->OrdenaAlquileres(alquileres_);
	alquileres_->MostrarAlquileres(alquileres_);

	int axe = 0;
	//borrado

	delete[] alquileres_.lista;
	alquileres_.lista = nullptr;
	delete[] coches_.lista;
	coches_.lista = nullptr;

	return 0;
}