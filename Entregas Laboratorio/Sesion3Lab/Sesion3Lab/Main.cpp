// G13
// Amparo Rubio Bellon
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

	alquileres_.OrdenaAlquiler();
	alquileres_.MostrarAlquiler();

	return 0;
}