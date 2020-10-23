// G13
// Amparo Rubio Bellon
// Jorge Zurdo Izquierdo
#include "ListaAlquileres.h"
#include <algorithm>
#include <fstream>

ListaAlquileres::ListaAlquileres() : tam(0), limite(0), lista_coches(ListaCoches())
{
	LeerAlquiler("rent.txt");
}

ListaAlquileres::ListaAlquileres(int t, int lim,  ListaCoches listcoches) :
	tam(t), limite(lim), lista_coches(listcoches)
{

	LeerAlquiler("rent.txt");
}

bool ListaAlquileres::LeerAlquiler(std::string filename)
{
	std::ifstream file;
	file.open(filename);

	if (file.is_open()) {
		int tam_rent = 0;
		file >> tam;
		limite = 2 * tam;
		alquileres = new Alquiler[limite];
	
		for (int i = 0; i < tam; i++) {
			int coche = 0;
			file >> coche;

			Coche* c = lista_coches.buscaCoche(coche);
			char aux = '/';
			int d, m, a, dia ;
			file >> d >> aux >> m >> aux >> a;
			Date dt = Date(d, m, a);
			
			file >> dia;
		
			alquileres[i].setCoche(c);
			alquileres[i].setDate(dt);
			alquileres[i].setDays(dia);
			
			delete c;
		}
		return true;
	}
	
	return false;
}

bool ListaAlquileres::ComparaFechas(Alquiler primera, Alquiler segunda) {

	if (primera.getDate().getYear() < segunda.getDate().getYear())
		return true;
	else if (primera.getDate().getYear() == segunda.getDate().getYear()) {

		if (primera.getDate().getMonth() < segunda.getDate().getMonth()) 
			return true;
		else if (primera.getDate().getMonth() == segunda.getDate().getMonth()) {

			if (primera.getDate().getDay() < primera.getDate().getDay())	
				return true;
			else if (primera.getDate().getDay() > primera.getDate().getDay()) 
				return false;
		}
	}

	return false;
}

void ListaAlquileres::MostrarAlquiler()
{
	for (int i = 0; i < tam; i++) {

		char aux = '/';
		if (alquileres[i].getCoche() != nullptr) {
			std::cout << alquileres[i].getDate().getDay() << aux << alquileres[i].getDate().getMonth() << aux << alquileres[i].getDate().getYear() << " " << alquileres[i].getCoche()->getModel() << " " <<
				alquileres[i].getDias() << " dia(s) por " << alquileres[i].getDias() * alquileres[i].getCoche()->getPrecio() << " euros." << std::endl;
		}
		else std::cout << alquileres[i].getDate().getDay() << aux << alquileres[i].getDate().getMonth() << aux << alquileres[i].getDate().getYear() << " " << " ERROR: Modelo inexistente " << std::endl;

	}
}

void ListaAlquileres::OrdenaAlquiler() const
{
	std::sort(alquileres, alquileres + tam, ComparaFechas);
}