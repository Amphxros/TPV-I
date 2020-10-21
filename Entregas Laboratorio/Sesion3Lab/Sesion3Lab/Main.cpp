// G13
// Amparo Rubio Bell�n
// Jorge Zurdo Izquierdo

#include <iostream>
#include <string>
#include <fstream>

#include "ListaAlquileres.h"	// Incluye Alquileres y ListaCoches
#include "ListaCoches.h"

using namespace std;

int main() {
	//listas
	ListaCoches coches_ = ListaCoches();
	ListaAlquileres alquileres_ = ListaAlquileres();
	//lectura
	//coches_->CargaCoches(coches_);
	//alquileres_->leerAlquiler(alquileres_, coches_);		// Necesita coches para a�adir nullptr si uno no existe
	//alquileres_->OrdenaAlquileres(alquileres_);
	//alquileres_->MostrarAlquileres(alquileres_);

	////borrado
	//delete[] alquileres_.lista;
	//alquileres_.lista = nullptr;
	//delete[] coches_.lista;
	//coches_.lista = nullptr;

	return 0;
}