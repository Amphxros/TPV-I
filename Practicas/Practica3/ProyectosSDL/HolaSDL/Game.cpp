#include "Game.h"

#include <iostream>
#include <fstream>
#include <cstdlib>	// Para el random
#include "SmartGhost.h"
#include "App.h"

Game::Game(App* app): GameState(app), level_(0)
{
	
	init();
}

Game::~Game()
{	
	//borrado de objetos
	clear();
	//destruccion de cosas de sdl
	
}

void Game::init()
{	
	// Cargado del Mapa
	map_ = new GameMap(Vector2D(0,0),TAM_TILE,TAM_TILE,30, 30,app_->getTexture(TextureOrder::MAP_SPRITESHEET) , this);
	std::list<GameObject*>::iterator it = gObjects_.insert(gObjects_.end(), map_);
	map_->setItList(it);

	// Cargado de la barra de puntuaciones
	infoBar_= new InfoBar(Vector2D(WIN_WIDTH - OFFSET,0), 0, 0,app_->getTexture(TextureOrder::CHAR_SPRITESHEET), app_->getTexture(TextureOrder::DIGITS),this);
	it = gObjects_.insert(gObjects_.end(), infoBar_);
	infoBar_->setItList(it);

	load(map_name[level_]);
}


void Game::load(std::string filename)
{
	std::ifstream file;
	file.open(filename);

	if (file.is_open()) {
		
		file >> dim_map_x >> dim_map_y;	// Dimensiones del mapa
		
		for (int i = 0; i < dim_map_x; i++) {
			for (int j = 0; j < dim_map_y; j++) {
				int d;
				file >> d;

				switch (d) {
				case 0:case 1:case 2:case 3: //0 vacio, 1 muro, 2 comida, 3 vitaminas
					map_->write(j, i, (MapCell)d); 
					break;

				case 4: //fantasmas inteligentes
					map_->write(j, i, (MapCell)0);
					createSmartGhost(Vector2D(j, i));
					break;
			
				case 5:case 6:case 7:case 8:		// Los fantasmas normales van del 5 al 8  
					map_->write(j, i, (MapCell)0);
					createGhost(Vector2D(j, i), d - 5);	
					break;
				case 9:		//pacman
					map_->write(j, i, (MapCell)0);
					createPacman(Vector2D(j, i));
					break;

				default:
					map_->write(j, i, (MapCell)0);
					break;
				}
			}
		}
	}
	else
		throw "Archivo no encontrado";
}

void Game::nextLevel()
{
	// Datos para el siguiente nivel (Mismos puntos y vidas)
	int v = pacman_->getVidas();
	int p = infoBar_->getPuntos();
	level_++;
	clear();
	num_ghosts = 0;

	// Nuevos datos del nivel
	init();
	infoBar_->setPuntos(p);
	pacman_->setVidas(v);
}

void Game::createPacman(Vector2D pos)
{
	// Creamos Pacman, lo añadimos a la lista y movemos el iterador
	pacman_ = new Pacman(Vector2D((pos.getX()*TAM_TILE), (pos.getY()*TAM_TILE)),TAM_TILE/2,TAM_TILE +5,TAM_TILE +5, app_->getTexture(TextureOrder::CHAR_SPRITESHEET), this,NUM_VIDAS);
	std::list<GameObject*>::iterator it = gObjects_.insert(gObjects_.end(), pacman_);
	pacman_->setItList(it);

	std::list < EventHandler*>::iterator ev = evHandlers_.insert(evHandlers_.begin(), pacman_);
	pacman_->setItHandler(ev);

}

void Game::createGhost(Vector2D pos, int color)
{
	// Creamos el Fantasma, lo añadimos a la lista y movemos el iterador
	Ghost* g = new Ghost(Vector2D((pos.getX() * TAM_TILE), (pos.getY() * TAM_TILE)),TAM_TILE/2,TAM_TILE,TAM_TILE, app_->getTexture(TextureOrder::CHAR_SPRITESHEET), this, color);

	std::list<GameObject*>::iterator it = gObjects_.insert(gObjects_.end(), g);
	g->setItList(it);

	// Lo añadimos a la lista de fantasmas y aumentamos su tamaño
	std::list <Ghost*>::iterator git=ghosts_.insert(ghosts_.end(), g);
	g->setGhostIt(git);
	num_ghosts++;
}

// Funciona igual que la creacion de fantasma normal
void Game::createSmartGhost(Vector2D pos)
{
	SmartGhost* g = new SmartGhost(Vector2D(( pos.getX() * TAM_TILE), ( pos.getY() * TAM_TILE)),TAM_TILE/2, TAM_TILE, TAM_TILE, app_->getTexture(TextureOrder::CHAR_SPRITESHEET), this, 4);
	std::list<GameObject*>::iterator it = gObjects_.insert(gObjects_.end(), g);
	g->setItList(it);

	std::list <Ghost*>::iterator git=ghosts_.insert(ghosts_.end(), g);
	g->setGhostIt(git);
	num_ghosts++;
}

void Game::deleteGhost(std::list<GameObject*>::iterator it, std::list<Ghost*>::iterator git)
{
	// Lo borramos de la lista de objetos y de la de fantasmas
	gObjects_.erase(it);
	ghosts_.erase(git);
	num_ghosts--;
}

// Detecta la colision con las paredes
bool Game::tryMove(SDL_Rect rect, Vector2D dir, Point2D& newPos)
{
	SDL_Rect dest; //rectangulo correspondiente a la posicion siguiente
	dest.x = newPos.getX();
	dest.y = newPos.getY();
	dest.w = rect.w;
	dest.h = rect.h;

	return !(map_->IntersectWall(dest));
}

// Detecta la interseccion con la comida
bool Game::eatFood(SDL_Rect rect, Point2D& newPos)
{
	SDL_Rect dest; //rectangulo correspondiente a la posicion siguiente
	dest.x = newPos.getX();
	dest.y = newPos.getY();
	dest.w = rect.w;
	dest.h = rect.h;

	return (map_->IntersectFood(dest));
}

// Comprueba la colision del pacman con los fantasmas, resetea la posicion suya o de ellos y los elimina si es un fantasma inteligente
bool Game::CollisionWithGhosts(Pacman* g)
{
	for (auto g_ : ghosts_) {
		if (SDL_HasIntersection(&(g->getdest()), &(g_->getdest()))) {
			if (pacman_->getNyom()) {
				
				infoBar_->setPuntos(infoBar_->getPuntos() + POINTS_PER_GHOST);
				if (dynamic_cast<SmartGhost*>(g_) != nullptr) {
					deleteGhost(g_->getIt(), g_->getGhostIt());
				}
				else {
					g_->resetPos();
				}
			}
			else {
				pacman_->resetPos();
				pacman_->setVidas(pacman_->getVidas()-1);
				if (pacman_->getVidas() < 0) {
					app_->quit();
				}
			}
			return true;
		}
	}
	return false;
}

//compueba la colision de un fantasma inteligente entre los fantasmas y si es un fantasma normal o uno inteligente y adulto crea un fantasma inteligente
bool Game::CollisionBetweenGhosts(Ghost* g)
{
	for (auto g_ : ghosts_) {
	
		SDL_Rect dest; //rectangulo correspondiente con la posicion media
		dest.x = (g_->getPos().getX() + g->getPos().getX()) / 2;
		dest.y = (g_->getPos().getY() + g->getPos().getY()) / 2;
		dest.w = g->getWidth();
		dest.h = g->getHeight();

		if (SDL_HasIntersection(&(g->getdest()), &(g_->getdest()))&& g->getIt()!=g_->getIt()) {
			
			if (!map_->IntersectWall(dest)) { //comprueba que la posicion no es muro
				
				SmartGhost* gs=dynamic_cast<SmartGhost*>(g_); // si es un fantasma inteligente
				if (gs != nullptr) {
					if (gs->getAge() == Age::ADULT) {// si es un fantasma inteligente y adulto
						Vector2D ps = SDLPointToMapCoords(Point2D(dest.x, dest.y));
						createSmartGhost(ps);
						return true;
					}
				}
				else {
					Vector2D ps = SDLPointToMapCoords(Point2D(dest.x, dest.y));
					createSmartGhost(ps);
					return true;
				}
			}
		}
	}
	return false;
}

void Game::loadFromFile(int seed)
{
	clear(); //borramos todo

	std::ifstream file;
	file.open((std::to_string(seed) + ".pac").c_str());

	//cargar partida si el archivo está abierto
	if (file.is_open()) {
		int p, v;	//puntos y vida auxiliares
		file >> p >> v >> level_;
		
		//carga del mapa
		file >> dim_map_x >> dim_map_y;
		map_ = new GameMap(Vector2D(0, 0), TAM_TILE, TAM_TILE, 40, 40, app_->getTexture(TextureOrder::CHAR_SPRITESHEET), this);
		for (int i = 0; i <= dim_map_x; i++) {
			for (int j = 0; j <= dim_map_y; j++) {
				int d;
				file >> d;
				map_->write(i, j, (MapCell)d);
			}
		}
		std::list<GameObject*>::iterator it = gObjects_.insert(gObjects_.end(), map_);
		map_->setItList(it);

		//carga de la infoBar
		infoBar_ = new InfoBar(Vector2D(WIN_WIDTH - OFFSET, 0), 0, 0, app_->getTexture(TextureOrder::CHAR_SPRITESHEET), app_->getTexture(TextureOrder::DIGITS), this);
		it = gObjects_.insert(gObjects_.end(), infoBar_);
		infoBar_->setItList(it);
		infoBar_->setPuntos(p);

		//carga del pacman
		int x, y, x0, y0, w, h;
		file >> x >> y >> x0 >> y0 >> w >> h;
		pacman_ = new Pacman(Vector2D(x0,y0), TAM_TILE / 2, w, h, nullptr, this, v);
		pacman_->setPos(x, y);
		it = gObjects_.insert(gObjects_.end(), pacman_);
		pacman_->setItList(it);
	
		//fantasmas
		int n;
		file >> num_ghosts;
		std::cout << num_ghosts;
		for (int i = 0; i < num_ghosts; i++) {
			//habría usado el loadfromfile de Ghost pero no habia una forma clara de distinguir los fantasmas normales 
			//sin cargar la linea entera(ya que tiene el color que es la unica diferencia a nivel de archivo de guardado)
			int x, y, x0, y0, w, h, c;
			file >> x >> y >> x0 >> y0 >> w >> h >> c;
			if (c== 5) { //si su color es 5 entonces es un SmartGhost
				SmartGhost* g = new SmartGhost(Vector2D(x0, y0), TAM_TILE / 2, w, h, app_->getTexture(TextureOrder::CHAR_SPRITESHEET), this, c);
				g->setPos(x, y);
				it = gObjects_.insert(gObjects_.end(), g);
				g->setItList(it);

				std::list <Ghost*>::iterator git = ghosts_.insert(ghosts_.end(), g);
				g->setGhostIt(git);
			}
			else {
				//creamos un fantasma normal si su color no es 5
				Ghost* g= new Ghost(Vector2D(x0, y0), TAM_TILE / 2, w, h, app_->getTexture(TextureOrder::CHAR_SPRITESHEET), this, c);
				g->setPos(x, y);
				it = gObjects_.insert(gObjects_.end(), g);
				g->setItList(it);
				std::list <Ghost*>::iterator git = ghosts_.insert(ghosts_.end(), g);
				g->setGhostIt(git);
			}
		}
	}
	else {
		level_ = 0;
		init(); //si no encontramos un archivo valido creamos una partida nueva
	}

}

void Game::saveToFile() {

	//pillamos el nombre del fichero
	int seed = -1;
	do {
		std::cin >> seed;
	} while (seed < 0);

	//creamos el fichero seed.pac
	std::ofstream file;
	file.open(std::to_string(seed) + ".pac");

	//si se abre escribiremos los datos de los objetos
	if (file.is_open()) {
		int p = infoBar_->getPuntos();
		int v = pacman_->getVidas();

		file << p << " " << v << " " << level_ << std::endl; //puntos, vidas y nivel

		file << std::endl;
		file << dim_map_x << " " << dim_map_y << std::endl; //dimensiones del mapa en num de tiles

		//informacion del mapa
		for (int i = 0; i <= dim_map_x; i++) {
			for (int j = 0; j <= dim_map_y; j++) {
				int d = (int)(map_->getCell(i, j));
				file << d << " ";
			}
			file << std::endl;
		}
		//pacman
		pacman_->saveToFile(file);
		file << std::endl;
		
		//numero de fantasmas
		file << num_ghosts;
		file << std::endl;
		//guardado de fantasmas
		for (auto it = ghosts_.begin(); it != ghosts_.end(); ++it) {
			auto g = *it;
			g->saveToFile(file);
			file << std::endl;
		}
		file.close();
		std::cout << "Guardado " << seed << ".pac";

	}
	else {
		throw "No se ha podido guardar el fichero";
	}
}

void Game::clear()
{
	//borrado de objetos
	for (auto g = gObjects_.begin(); g != gObjects_.end();) {
		auto aux = g;
		g++;
		delete* aux;
	}
	gObjects_.clear();
	ghosts_.clear();
}

void Game::render()
{
	GameState::render();
}

void Game::update()
{
	for (auto it = gObjects_.begin(); it != gObjects_.end();) //update		
		(*(it++))->update();

	SDL_Delay(2*DELAY);
}

void Game::handleEvents(SDL_Event& event)
{
	GameState::handleEvents(event);
}
