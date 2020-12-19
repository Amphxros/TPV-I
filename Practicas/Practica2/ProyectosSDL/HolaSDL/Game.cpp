#include "Game.h"

#include <iostream>
#include <fstream>
#include <cstdlib>	// Para el random
#include "SmartGhost.h"

Game::Game()
{
	srand(NULL);
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("ManPac", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (window_ == nullptr || renderer_ == nullptr)
		throw "Error cargando SDL";
	else {
	for (int i = 0; i < NUM_TEXTURES; i++) {
		textures[i] = new Texture(renderer_, textures_data_[i].filename, textures_data_[i].rows, textures_data_[i].cols);
	}	
	init();
	}
}

Game::~Game()
{
	std::cout << "txt" << std::endl;
	for (int i = 0; i < NUM_TEXTURES; i++) {
		delete textures[i];	textures[i] = nullptr;
	}
	
	std::cout << "lista" << std::endl;
	clear();

	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Game::init()
{	
	map_ = new GameMap(Vector2D(0,0),TAM_MAT,TAM_MAT,30, 30, textures[TextureOrder::MAP_SPRITESHEET], this);
	std::list<GameObject*>::iterator it = gObjects_.insert(gObjects_.end(), map_);
	map_->setItList(it);

	infoBar_= new InfoBar(Vector2D(WIN_WIDTH - OFFSET,0), 0, 0, textures[TextureOrder::CHAR_SPRITESHEET],textures[TextureOrder::DIGITS],this);
	it = gObjects_.insert(gObjects_.end(), infoBar_);
	infoBar_->setItList(it);

	load(map_name[level_]);

}

void Game::load(std::string filename)
{
	std::ifstream file;
	file.open(filename);

	if (file.is_open()) {
		
		file >> dim_map_x >> dim_map_y;	//Tama�o del mapa
		
		for (int i = 0; i < dim_map_x; i++) {
			for (int j = 0; j < dim_map_y; j++) {
				int d;
				file >> d;

				switch (d) {
				case 0:case 1:case 2:case 3:
					map_->write(j, i, (MapCell)d); 
					if (d == 2) food_left++;	// Caso 2 es la comida, el resto son el mapa
					break;

				case 4:
					map_->write(j, i, (MapCell)0);
					createSmartGhost(Vector2D(j, i));
					break;
				// Los fantasmas se codifican del 0 (5) al 3 (8) 
				case 5:case 6:case 7:case 8:
					map_->write(j, i, (MapCell)0);
					createGhost(Vector2D(j, i), d - 5);	
					break;
				case 9:
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
	int v = pacman_->getVidas();
	int p = infoBar_->getPuntos();
	level_++;
	clear();
	num_ghosts = 0;
	init();
	infoBar_->setPuntos(p);
	pacman_->setVidas(v);
}

void Game::createPacman(Vector2D pos)
{
	pacman_ = new Pacman(Vector2D((pos.getX()*TAM_MAT), (pos.getY()*TAM_MAT)),TAM_MAT/2,TAM_MAT +5,TAM_MAT +5, textures[TextureOrder::CHAR_SPRITESHEET], this,5);
	std::list<GameObject*>::iterator it = gObjects_.insert(gObjects_.end(), pacman_);
	pacman_->setItList(it);
}

void Game::createGhost(Vector2D pos, int color)
{
	Ghost* g = new Ghost(Vector2D((pos.getX() * TAM_MAT), (pos.getY() * TAM_MAT)),TAM_MAT/2,TAM_MAT,TAM_MAT, textures[TextureOrder::CHAR_SPRITESHEET], this, color);

	std::list<GameObject*>::iterator it = gObjects_.insert(gObjects_.end(), g);
	g->setItList(it);

	ghosts_.insert(ghosts_.end(), g);
	num_ghosts++;
}

void Game::createSmartGhost(Vector2D pos)
{
	SmartGhost* g = new SmartGhost(Vector2D(( pos.getX() * TAM_MAT), ( pos.getY() * TAM_MAT)),TAM_MAT/2, TAM_MAT, TAM_MAT, textures[TextureOrder::CHAR_SPRITESHEET], this, 4);
	std::list<GameObject*>::iterator it = gObjects_.insert(gObjects_.end(), g);
	g->setItList(it);

	ghosts_.insert(ghosts_.end(), g);
	num_ghosts++;
}

void Game::deleteGameObject(GameObject* g)
{
	std::cout << "borra" << std::endl;
	gObjects_.remove(g);
	delete g;
}

void Game::deleteGhost(Ghost* g)
{
	Ghost* aux = g;
	ghosts_.remove(aux);
	gObjects_.remove(aux);
	delete g;
	num_ghosts--;
}

void Game::deletePacman()
{
	std::cout << "nyom nyom" << std::endl;
	deleteGameObject(pacman_);
}

bool Game::tryMove(SDL_Rect rect, Vector2D dir, Point2D& newPos)
{
	SDL_Rect dest; //rectangulo correspondiente a la posicion siguiente
	dest.x = newPos.getX();
	dest.y = newPos.getY();
	dest.w = rect.w;
	dest.h = rect.h;

	return !(map_->IntersectWall(dest));
}

bool Game::eatFood(SDL_Rect rect, Point2D& newPos)
{
	SDL_Rect dest; //rectangulo correspondiente a la posicion siguiente
	dest.x = newPos.getX();
	dest.y = newPos.getY();
	dest.w = rect.w;
	dest.h = rect.h;

	return (map_->IntersectFood(dest));
}

bool Game::CollisionWithGhosts(Pacman* g)
{
	for (auto g_ : ghosts_) {
		if (SDL_HasIntersection(&(g->getdest()), &(g_->getdest()))) {
			if (pacman_->getNyom()) {
				g_->resetPos();
				if (dynamic_cast<SmartGhost*>(g_) != nullptr) {
					deleteGhost(g_);
				}
				else {
					g_->resetPos();
				}
			}
			else {
				pacman_->resetPos();
				pacman_->setVidas(pacman_->getVidas()-1);
				if (pacman_->getVidas()< 0) 
					exit_ = true;
			}
			return true;
		}
	}
	return false;
}

bool Game::CollisionBetweenGhosts(Ghost* g)
{
	for (auto g_ : ghosts_) {
	
		SDL_Rect dest;
		dest.x = (g_->getPos().getX() + g->getPos().getX()) / 2;
		dest.y = (g_->getPos().getY() + g->getPos().getY()) / 2;
		dest.w = g->getWidth();
		dest.h = g->getHeight();
		if (SDL_HasIntersection(&(g->getdest()), &(g_->getdest()))) {
			
			if (!map_->IntersectWall(dest)) {
				
				SmartGhost* gs=dynamic_cast<SmartGhost*>(g_);
				if (gs != nullptr) {
					if (gs->getAge() == Age::ADULT) {
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

void Game::run()
{
	while (!exit_)
	{
		handleEvents();
		update();
		render();
		
		if((food_left<=0 || infoBar_->getPuntos()>= (level_ +1)*POINTS_PER_LEVEL)){
			if(level_>=NUM_LEVELS){
				exit_ = true;
			}	
			else 
			{
				nextLevel();
			}
		}
		SDL_Delay(300);
	}
}

void Game::loadFromFile(int seed)
{
	clear();
	std::ifstream file;
	file.open(std::to_string(seed) + ".pac");

	if (file.is_open()) {
	//cargar partida
		int p, v;
		file >> p >> v >> level_;
		
		//mapa
		file >> dim_map_x >> dim_map_y;
		map_ = new GameMap(Vector2D(0, 0), TAM_MAT, TAM_MAT, 40, 40, textures[TextureOrder::MAP_SPRITESHEET], this);
		for (int i = 0; i <= dim_map_x; i++) {
			for (int j = 0; j <= dim_map_y; j++) {
				int d;
				file >> d;
				map_->write(i, j, (MapCell)d);
			}
		}
		std::list<GameObject*>::iterator it = gObjects_.insert(gObjects_.end(), map_);
		map_->setItList(it);

		infoBar_ = new InfoBar(Vector2D(WIN_WIDTH - OFFSET, 0), 0, 0, textures[TextureOrder::CHAR_SPRITESHEET], textures[TextureOrder::DIGITS], this);
		it = gObjects_.insert(gObjects_.end(), infoBar_);
		infoBar_->setItList(it);
		infoBar_->setPuntos(p);

		//pacman
		int x, y, x0, y0, w, h;
		file >> x >> y >> x0 >> y0 >> w >> h;
		pacman_ = new Pacman(Vector2D(x0,y0), TAM_MAT / 2, w, h, textures[TextureOrder::CHAR_SPRITESHEET], this, v);
		pacman_->setPos(x, y);
		it = gObjects_.insert(gObjects_.end(), pacman_);
		pacman_->setItList(it);
	
		//fantasmas
		file >> num_ghosts;
		for (int i = 0; i < num_ghosts; i++) {
			//habría usado el loadfromfile de Ghost pero no habia una forma clara de distinguir los fantasmas normales 
			//sin cargar la linea entera(ya que tiene el color que es la unica diferencia a nivel de archivo de guardado)
			int x, y, x0, y0, w, h, c;
			file >> x >> y >> x0 >> y0 >> w >> h >> c;
			if (c== 5) {
				SmartGhost* g = new SmartGhost(Vector2D(x0, y0), TAM_MAT / 2, w, h, textures[TextureOrder::CHAR_SPRITESHEET], this, c);
				g->setPos(x, y);
				it = gObjects_.insert(gObjects_.end(), g);
				g->setItList(it);
				ghosts_.push_back(g);
				
			}
			else {
				Ghost* g= new Ghost(Vector2D(x0, y0), TAM_MAT / 2, w, h, textures[TextureOrder::CHAR_SPRITESHEET], this, c);
				g->setPos(x, y);
				it = gObjects_.insert(gObjects_.end(), g);
				g->setItList(it);
				ghosts_.push_back(g);

			}


		}
	}
	else {
		//throw a rock or a sandwich...I'm hungry help
		init();
	}

}

void Game::saveToFile() {

	int seed = -1;
	std::cout << "Introduce codigo: ";
	std::cin >> seed;
	std::ofstream file;
	file.open(std::to_string(seed) + ".pac");

	if (file.is_open()) {
		int p = infoBar_->getPuntos();
		int v = pacman_->getVidas();

		file << p << " " << v << " " << level_ << std::endl; //puntos, vidas y nivel

		file << std::endl;
		file << dim_map_x << " " << dim_map_y << std::endl; //dimensiones del mapa en num de tiles

		for (int i = 0; i <= dim_map_x; i++) {
			for (int j = 0; j <= dim_map_y; j++) {
				int d = (int)(map_->getCell(i, j));
				file << d << " ";
			}
			file << std::endl;
		}

		pacman_->saveToFile(file);
		file << std::endl;
		file << num_ghosts;
		file << std::endl;
		for (auto it = ghosts_.begin(); it != ghosts_.end(); ++it) {
			auto g = *it;
			g->saveToFile(file);
			file << std::endl;
		}
		std::cout << "Guardado " << seed << ".pac";

	}
	else {
		//throw a rock or whatever
	}
}

void Game::clear()
{
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
	SDL_RenderClear(renderer_);	// Limpieza del frame
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);	// Color del fondo

	for (GameObject* g : gObjects_)
		g->render();

	SDL_RenderPresent(renderer_);
}

void Game::update()
{
	for (auto it= gObjects_.begin();it!=gObjects_.end();++it)
		(*it)->update();
}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			exit_ = true;
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_g) {
			saveToFile();
		}
		else
		{
			pacman_->handleEvents(event);	
		}
	}
}





