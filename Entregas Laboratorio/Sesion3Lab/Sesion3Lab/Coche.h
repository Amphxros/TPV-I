#pragma once
#include <string>
class Coche
{	
public:
	Coche() : mat_(-1), precio_(-1),model_(""){}
	Coche(int mat, int precio, std::string model);

	inline int getMat()const { return mat_; }
	inline void setMat(int mat) { mat_ = mat; }
	
	inline int getPrecio()const { return precio_; }
	inline void setPrecio(int pre) { precio_ = pre; }
	
	inline std::string getModel()const { return model_; }
	inline void setModel(std::string s) { model_ = s; }


private:
	int mat_, precio_;
	std::string model_;

};

