
#include <iostream>
#include <string>
#include <fstream>
struct Car
{
	int mat_;
	int precio_;
	//CAMBIAR ESTO A UN VALOR CON GET LINE !!
	std::string model_;
	std::string name_;
};

struct Rent {
	Car* car_;
	std::string date_;//<- CAMBIAR ESTO A TIPO FECHA
	int days;

};

/// <summary>
/// :carga la información del archivo coches.txt en la lista de coches
/// </summary>
/// <param name="lista"></param>
/// <returns> true si el archivo se ha podido leer </returns>
bool CargaCoches(Car* lista,int & tam) {
	std::ifstream file;
	file.open("coches.txt");
	if (file.is_open()) {
		int dim = 0;
		file >> tam;
		lista = new Car[2*tam];

		for (int i = 0; i < tam; i++) {
			file >> lista[i].mat_;
			file >> lista[i].precio_;
			file >> lista[i].model_;
			file >> lista[i].name_;

		//std::cout << lista[i].mat_ << " " << lista[i].precio_ << " " << lista[i].model_<< " "<< lista[i].name_ << std::endl;
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
			int code = 0;
			file >> code;

			rent[i].car_ = buscaCoche(coches, tam_coches, code);
			if (rent[i].car_ != nullptr) {
				file >> rent[i].date_;
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
	int tam_coches=10;
	int tam_rent=10;
	Car* lista= new Car();
	Rent* alquileres = new Rent();
	CargaCoches(lista, tam_coches);
	leerAlquiler(alquileres, lista, tam_coches, tam_rent);
	delete alquileres;
	delete lista;
	return 0;
}

