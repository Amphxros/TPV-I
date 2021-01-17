#include "InfoBar.h"
#include "PlayState.h"

InfoBar::InfoBar(Vector2D pos, double width, double height, Texture* texture, Texture* nums, GameState* game):
 GameObject(pos, width,height,texture, game),num_texture(nums), points_(0), game_state(static_cast<PlayState*>(game)){		
}
void InfoBar::setPuntos(int p)
{
	points_ = p;
	punt_.clear();
	int aux = points_;
	//los troceamos en el vector para el renderizado
	while (aux > 0) {
		int r = aux % 10;
		aux /= 10;
		punt_.push_back(r);
	}
}
void InfoBar::render()
{
	//renderizado de los puntos
	for (int i = 0; i < punt_.size(); i++) {
		SDL_Rect dest;
		dest.x = pos_.getX() - TAM_TILE * i + 5;
		dest.y = pos_.getY();
		dest.w = TAM_TILE;
		dest.h = TAM_TILE;

		num_texture->renderFrame(dest, punt_[i]/4, punt_[i]%4);
	}

	//renderizado de las vidas
	for(int i=0;i<game_state->getVidas();i++){
		SDL_Rect dest;
		dest.x=(pos_.getX()) - TAM_TILE* i + 5;
		dest.y=pos_.getY() + OFFSET/2;
		dest.w=TAM_TILE;
		dest.h=TAM_TILE;

		texture_->renderFrame(dest,0,11);
	}
}
