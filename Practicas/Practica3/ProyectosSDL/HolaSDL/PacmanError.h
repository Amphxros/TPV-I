#pragma once
#include <stdexcept>
#include <iostream>

#include "checkML.h"
class PacmanError:	
	public std::logic_error
{
public:
	PacmanError(const std::string& what) : std::logic_error(what), what_(what){
		std::cout << what;
	}

	
protected:
	std::string what_;

};

class FileNotFoundError:	
	public PacmanError
{
public:
	FileNotFoundError(std::string what)	:	
		PacmanError(what){	
		std::cout << "Couldn't load the file " << std::endl;
	}

};

class FileFormatError :	
	public PacmanError
{
public:
	FileFormatError(std::string what, std::string filename) : 
		PacmanError(what), file(filename) {
		std::cout << "Couldn't load the file " << file << std::endl;	
	}

private:
	std::string file;
};

class SDLError :	
	public PacmanError
{
public:
	SDLError(std::string what) : PacmanError(what) {}

	void SDLGetError() {}
	void IMGGetError() {	
		std::cout << "Couldn't load the image " << std::endl;
	}

	// A la espera de arreglar la libreria
	void TTF_GetError() {	
		std::cout << "Couldn't load the font " << std::endl;
	}
};