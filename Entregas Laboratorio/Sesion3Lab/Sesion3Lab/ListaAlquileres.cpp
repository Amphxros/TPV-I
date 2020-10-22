#include "ListaAlquileres.h"
#include <algorithm>
#include <fstream>

ListaAlquileres::ListaAlquileres() : tam(0), limite(0), lista_(ListaCoches())
{
	LeerAlquiler("rent.txt");
}

ListaAlquileres::ListaAlquileres(int t, int lim,  ListaCoches listcoches) :
	tam(t), limite(lim), lista_(listcoches)
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
		lista = new Alquiler[limite];
	
		for (int i = 0; i < tam; i++) {
			int coche = 0;
			file >> coche;

			Coche* c = lista_.buscaCoche(coche);
			char aux = '/';
			int d, m, a, dia ;
			file >> d >> aux >> m >> aux >> a;
			Date dt = Date(d, m, a);
			
			file >> dia;
		
			lista[i].setCoche(c);
			lista[i].setDate(dt);
			lista[i].setDays(dia);
			
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
		if (lista[i].getCoche() != nullptr) {
			std::cout << lista[i].getDate().getDay() << aux << lista[i].getDate().getMonth() << aux << lista[i].getDate().getYear() << " " << lista[i].getCoche()->getModel() << " " <<
				lista[i].getDias() << " dia(s) por " << lista[i].getDias() * lista[i].getCoche()->getPrecio() << " euros." << std::endl;
		}
		else std::cout << lista[i].getDate().getDay() << aux << lista[i].getDate().getMonth() << aux << lista[i].getDate().getYear() << " " << " ERROR: Modelo inexistente " << std::endl;

	}
}

void ListaAlquileres::OrdenaAlquiler()
{
	sort(lista, (lista + tam),ComparaFechas);
}

