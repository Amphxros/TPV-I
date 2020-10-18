#include <iostream>
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
	//std::string date_;//<- CAMBIAR ESTO A TIPO FECHA
	Date date_;//<- CAMBIAR ESTO A TIPO FECHA
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

		std::cout << l.lista[i].mat_ << " " << l.lista[i].precio_ << " " << l.lista[i].model_ << std::endl;
		}
	
		return true;
	}
	else {
		return false;
	}
}

// De momento siempre devuelve nullptr
Car* buscaCoche(Car* lista, int tam, int code) {
	/*
	int i = 0;
	while (i < tam && code != lista[i].mat_)
		i++;

	if (i > tam)
		return nullptr;
	else
		return &(lista[i]);
	*/
	for (int i = 0; i < tam; i++)
	{
		if (code == lista[i].mat_)		return &(lista[i]);
	}
	return nullptr;
}

//bool leerAlquiler(Rent* rent, Car* coches, const int & tam_coches, int tam_rent) {
bool leerAlquiler(ListaAlquileres &l, ListaCoches &coches) {

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
			std::string date;
			char aux = '/';

			// Tenemos que leer las fechas aunque el coche no exista
			//if (rent[i].car_ != nullptr) {
				//std::getline(file, rent[i].date_);
				//std::getline(file, date);
				file >> l.lista[i].date_.d >> aux >> l.lista[i].date_.m >> aux >> l.lista[i].date_.a;
				file >> l.lista[i].days_;

				//l.lista[i].car_->mat_ <<
				if (l.lista[i].car_ != nullptr)
					std::cout << l.lista[i].car_->mat_ << " " << l.lista[i].date_.d << aux << l.lista[i].date_.m << aux << l.lista[i].date_.a << " " << date << " " << l.lista[i].days_ << std::endl;
				else std::cout << "Modelo inexistente " << l.lista[i].date_.d << aux << l.lista[i].date_.m << aux << l.lista[i].date_.a << " " << date << " " << l.lista[i].days_ << std::endl;

			/*}
			else {
				return false;
			}*/
		}
		return true;
	}
	else {
		return false;
	}
}


int main() {	
	//listas
	ListaCoches coches_ = ListaCoches();
	ListaAlquileres alquileres_ = ListaAlquileres();
	//lectura
	CargaCoches(coches_);
	leerAlquiler(alquileres_, coches_);		// Necesita coches para añadir nullptr si uno no existe

	//leerAlquiler(alquileres, coches, tam_coches, tam_rent);
	int axe = 0;
	//borrado
	//delete alquileres;
	//delete l;
	return 0;
}

