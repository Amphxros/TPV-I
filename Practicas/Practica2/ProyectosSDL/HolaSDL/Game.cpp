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

	infoBar_= new InfoBar(Vector2D(0,0), 0, 0, textures[TextureOrder::CHAR_SPRITESHEET],textures[TextureOrder::DIGITS],this);
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
	init();
	infoBar_->setPuntos(p);
	pacman_->setVidas(v);
}

void Game::createPacman(Vector2D pos)
{
	pacman_ = new Pacman(Vector2D((pos.getX()*TAM_MAT), (pos.getY()*TAM_MAT)),TAM_MAT/2,TAM_MAT +5,TAM_MAT +5, textures[TextureOrder::CHAR_SPRITESHEET], this,3);
	std::list<GameObject*>::iterator it = gObjects_.insert(gObjects_.end(), pacman_);
	pacman_->setItList(it);
}

void Game::createGhost(Vector2D pos, int color)
{
	Ghost* g = new Ghost(Vector2D((pos.getX() * TAM_MAT), (pos.getY() * TAM_MAT)),TAM_MAT/2,TAM_MAT,TAM_MAT, textures[TextureOrder::CHAR_SPRITESHEET], this, color);

	std::list<GameObject*>::iterator it = gObjects_.insert(gObjects_.end(), g);
	g->setItList(it);

	ghosts_.insert(ghosts_.end(), g);
}

void Game::createSmartGhost(Vector2D pos)
{
	SmartGhost* g = new SmartGhost(Vector2D(( pos.getX() * TAM_MAT), ( pos.getY() * TAM_MAT)),TAM_MAT/2, TAM_MAT, TAM_MAT, textures[TextureOrder::CHAR_SPRITESHEET], this, 4);
	std::list<GameObject*>::iterator it = gObjects_.insert(gObjects_.end(), g);
	g->setItList(it);

	ghosts_.insert(ghosts_.end(), g);
}

void Game::deleteGameObject(GameObject* g)
{
	std::cout << "borra" << std::endl;
	gObjects_.remove(g);
	delete g;
}

void Game::deleteGhost(Ghost* g)
{
	std::cout << "boooo" << std::endl;
	ghosts_.remove(g);
	deleteGameObject(g);
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

bool Game::CollisionWithGhosts(GameObject* g)
{
	for (auto g_ : ghosts_) {
		if (SDL_HasIntersection(&(g->getdest()), &(g_->getdest()))) {
			if (pacman_->getNyom()) {
				g_->resetPos();
				deleteGhost(g_);
			}
			else {
				pacman_->resetPos();
				pacman_->setVidas(pacman_->getVidas() - 1);
				if (pacman_->getVidas() == 0) 
					exit_ = true;
			}
			return true;
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
			if(level_>NUM_LEVELS){
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

//bool Game::check_collisionGhostPacman() {
//
//	for (int i = 0; i < NUM_GHOSTS; i++)
//	{
//		// GetPos devuelve pos_ + dir_
//		if(ghost_[i]->getPos()==pacman_->getPos()|| ghost_[i]->getPos()==pacman_->getCurrPos()) {	
//			if (isPacmanNyom()) { 
//			ghost_[i]->resetPos(); 
//			infoBar_->setPuntos(infoBar_->getPuntos() + POINTS_PER_GHOST);
//			}
//			else {
//				pacman_->resetPos();
//			 pacman_->setVidas(pacman_->getVidas()-1);
//			 if(pacman_->getVidas()==0) exit_=true;
//			 }
//		
//			return true;
//		}
//	}
//	return false;
//}

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
		else
		{
		pacman_->handleEvents(event);
		}
	}
}
