#include "InfoBar.h"
#include "Game.h"

InfoBar::InfoBar(Vector2D pos, double width, double height, Texture* texture, Texture* nums, Game* game):
 GameObject(pos, width,height,texture, game),num_texture(nums), points_(0){		
}
void InfoBar::setPuntos(int p)
{
	points_ = p;
	punt_.clear();
	int aux = points_;
	while (aux > 0) {
		int r = aux % 10;
		aux /= 10;
		punt_.push_back(r);
	}
}
void InfoBar::render()
{
	for (int i = 0; i < punt_.size(); i++) {
		SDL_Rect dest;
		dest.x = pos_.getX() - TAM_MAT * i + 5;
		dest.y = pos_.getY();
		dest.w = TAM_MAT;
		dest.h = TAM_MAT;

		num_texture->renderFrame(dest, punt_[i]/4, punt_[i]%4);
	}

	for(int i=0;i<game_->getVidas();i++){
		SDL_Rect dest;
		dest.x=(pos_.getX()) - TAM_MAT* i + 5;
		dest.y=pos_.getY() + OFFSET/2;
		dest.w=TAM_MAT;
		dest.h=TAM_MAT;

		texture_->renderFrame(dest,0,11);
	}
}
