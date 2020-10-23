// G13
// Amparo Rubio Bellon
// Jorge Zurdo Izquierdo

#include "ListaCoches.h"
#include <fstream>
#include <iostream>

/// constructora
ListaCoches::ListaCoches() :
	tam(0),limite(0)
{
	cargaCoches("coches.txt");
}

/// constructora
ListaCoches::ListaCoches(int tam, int limite) :
	tam(tam), limite(limite)
{
	cargaCoches("coches.txt");
}

/// carga los coches de un archivo filename
bool ListaCoches::cargaCoches(std::string filename)
{
	std::ifstream file;

	file.open(filename);

	if (file.is_open()) {
		file >> tam;		// Primer elemento del txt es el numero con el tamaño de la lista
		limite = 2 * tam;
		
		lista = new Coche[limite];

		for (int i = 0; i < tam; i++) {
			int m = 0, pre=0;
			std::string s;
			file >> m;
			lista[i].setMat(m);

			file >> pre;
			lista[i].setPrecio(pre);

			std::getline(file, s);
			lista[i].setModel(s);
			
			std::cout << lista[i].getMat() << " " << lista[i].getPrecio() << " " << lista[i].getModel() << std::endl;
		}

		return true;
	}
	else {
		return false;
	}
}

///devuelve el coche con la matricula code
Coche* ListaCoches::buscaCoche(int code)
{
	int i = 0;
	while (lista[i].getMat()!=code && i<tam)
	{
		i++;
	}
	return &lista[i];
}
