// G13
// Amparo Rubio Bellón
// Jorge Zurdo Izquierdo

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;

struct Car	{
	int mat_;
	int precio_;
	std::string model_;
};

struct Date	{
	int d, m, a; //dia/mes/año
};

struct Rent {
	Car* car_;
	Date date_;
	int days_;

};

struct ListaCoches {
	int tam, limite;
	Car* lista;
};

struct ListaAlquileres {
	int tam, limite;
	Rent* lista;
};

/// <summary>
/// :carga la información del archivo coches.txt en la lista de coches
/// </summary>
/// <param name="lista"></param>
/// <returns> true si el archivo se ha podido leer </returns>
bool CargaCoches(ListaCoches &l) {
	std::ifstream file;
	file.open("coches.txt");
	
	if (file.is_open()) {
		int dim = 0;
		file >> l.tam;		// Primer elemento del txt es el numero con el tamaño de la lista
		l.lista = new Car[2 * l.tam];

		for (int i = 0; i < l.tam; i++) {
			file >> l.lista[i].mat_;
			file >> l.lista[i].precio_;
			std::getline(file, l.lista[i].model_);

		//std::cout << l.lista[i].mat_ << " " << l.lista[i].precio_ << " " << l.lista[i].model_ << std::endl;
		}
	
		return true;
	}
	else {
		return false;
	}
}

bool ComparaFechas(Rent primera, Rent segunda) {

	if (primera.date_.a < segunda.date_.a)	return true;
	else if (primera.date_.a == segunda.date_.a) {

		if (primera.date_.m < segunda.date_.m) return true;
		else if (primera.date_.m == segunda.date_.m) {

			if (primera.date_.d < primera.date_.d)	return true;
			else if (primera.date_.d > primera.date_.d) return false;
		}
	}

	return false;
}

void OrdenaAlquileres(ListaAlquileres &l) {

	// Requiere del inicio y el final del array, asi de c
	std::sort(l.lista, l.lista+l.tam, ComparaFechas);

}

Car* buscaCoche(Car* lista, int tam, int code) {
	for (int i = 0; i < tam; i++)
	{
		if (code == lista[i].mat_)		return &(lista[i]);
	}
	return nullptr;
}

bool leerAlquiler(ListaAlquileres& l, ListaCoches& coches) {

	std::ifstream file;
	file.open("rent.txt");

	if (file.is_open()) {
		int tam_rent = 0;
		file >> l.tam;
		l.lista = new Rent[2 * l.tam];

		for (int i = 0; i < l.tam; i++) {
			int coche = 0;
			file >> coche;
			l.lista[i].car_ = buscaCoche(coches.lista, coches.tam, coche);

			char aux = '/';

			file >> l.lista[i].date_.d >> aux >> l.lista[i].date_.m >> aux >> l.lista[i].date_.a;
			file >> l.lista[i].days_;

			/*
			if (l.lista[i].car_ != nullptr)
				std::cout << l.lista[i].car_->mat_ << " " << l.lista[i].date_.d << aux << l.lista[i].date_.m << aux << l.lista[i].date_.a << " " << " " << l.lista[i].days_ << std::endl;
			else std::cout << "Modelo inexistente " << l.lista[i].date_.d << aux << l.lista[i].date_.m << aux << l.lista[i].date_.a << " " << l.lista[i].days_ << std::endl;
			*/

		}
		return true;
	}
	else {
		return false;
	}
}

void MostrarAlquileres(ListaAlquileres l) {
	for (int i = 0; i < l.tam; i++) {

		char aux = '/';
		if (l.lista[i].car_ != nullptr)
			std::cout << l.lista[i].date_.d << aux << l.lista[i].date_.m << aux << l.lista[i].date_.a << " " << l.lista[i].car_->model_ << " " <<
			l.lista[i].days_ << " dia(s) por " << l.lista[i].days_ * l.lista[i].car_->precio_ << " euros." << std::endl;
		else std::cout << l.lista[i].date_.d << aux << l.lista[i].date_.m << aux << l.lista[i].date_.a << " " << " ERROR: Modelo inexistente " << std::endl;

	}
}


int main() {	
	//listas
	ListaCoches coches_ = ListaCoches();
	ListaAlquileres alquileres_ = ListaAlquileres();
	//lectura
	CargaCoches(coches_);
	leerAlquiler(alquileres_, coches_);		// Necesita coches para añadir nullptr si uno no existe
	OrdenaAlquileres(alquileres_);
	MostrarAlquileres(alquileres_);

	int axe = 0;
	//borrado
	
	delete[] alquileres_.lista;
	alquileres_.lista = nullptr;
	delete[] coches_.lista;
	coches_.lista = nullptr;

	return 0;
}

