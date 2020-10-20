#include "ListaAlquileres.h"
#include <algorithm>

ListaAlquileres::ListaAlquileres(int t, int lim, Alquiler* list, ListaCoches listcoches) :
	tam(t), limite(lim), lista(list), lista_(listcoches)
{
}
bool ListaAlquileres::LeerAlquiler(std::string filename)
{
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
}

void ListaAlquileres::OrdenaAlquiler(ListaAlquileres & l)
{
	std::sort(l.getLista(), (l.getLista() + l.getTam()), ComparaFechas);
}

