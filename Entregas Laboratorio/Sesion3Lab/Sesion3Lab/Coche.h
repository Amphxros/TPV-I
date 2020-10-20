#pragma once
#include <string>
class Coche
{	
public:
	Coche() : mat_(-1), precio_(-1),model_(""){}
	Coche(int mat, int precio, std::string model);

	inline int getMat() { return mat_; }
	inline int getPrecio() { return precio_; }
	inline std::string getModel() { return model_; }

	void CargaCoches();

private:
	int mat_, precio_;
	std::string model_;

};

