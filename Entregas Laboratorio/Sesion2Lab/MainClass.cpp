
#include <iostream>
#include <string>
#include <fstream>
struct Car
{
	int mat_;
	int precio_;
	std::string model_;
};
struct Date {
	int d, m,a; //dia/mes/año
};
struct Rent {
	Car* car_;
	std::string date_;//<- CAMBIAR ESTO A TIPO FECHA
	Date date;//<- CAMBIAR ESTO A TIPO FECHA
	int days;

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
bool CargaCoches(ListaCoches l) {
	std::ifstream file;
	file.open("coches.txt");
	if (file.is_open()) {
		int dim = 0;
		file >> l.tam;
		l.lista = new Car[2*l.tam];

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
Car* buscaCoche(Car* lista,int tam, int code) {

	int i = 0;
	while (i < tam && code != lista[i].mat_)
		i++;

	if (i > tam)
		return nullptr;
	else
		return &(lista[i]);
}

bool leerAlquiler(Rent* rent, Car* coches, const int & tam_coches, int tam_rent) {
	std::ifstream file;
	file.open("rent.txt");
	if (file.is_open()) {
		tam_rent = 0;
		file >> tam_rent;
		rent = new Rent[2*tam_rent];
		
		for (int i = 0; i < tam_rent; i++) {
			int code = -1;
			file >> code;
			rent[i].car_ = buscaCoche(coches, tam_coches, code);

			if (rent[i].car_ != nullptr) {
				std::getline(file, rent[i].date_);
				file >> rent[i].days;
				std::cout << rent[i].car_->mat_ << " " << rent[i].date_ << " " << rent[i].days << std::endl;

			}
			else {
				return false;
			}
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

	//leerAlquiler(alquileres, coches, tam_coches, tam_rent);
	
	//borrado
	//delete alquileres;
	//delete l;
	return 0;
}

