#include "InfoBar.h"
#include "Game.h"

InfoBar::InfoBar(Vector2D pos, Texture* texture, Texture* nums, Game* game):
pos_(pos), texture_(texture), num_texture(nums),game_(game){
	
}
void InfoBar::render()
{
	for (int i = 0; i < punt_.size(); i++) {
		SDL_Rect dest;
		dest.x = pos_.getX() + TAM_MAT * i + 5;
		dest.y = pos_.getY();
		dest.w = TAM_MAT;
		dest.h = TAM_MAT;

		num_texture->renderFrame(dest, punt_[i]/4, punt_[i]%4);
	}

	for(int i=0;i<game_->getVidas();i++){
		SDL_Rect dest;
		dest.x=(pos_.getX()*TAM_MAT)+ OFFSET + TAM_MAT * (i+1);
		dest.y=pos_.getY()*TAM_MAT + OFFSET;
		dest.w=TAM_MAT;
		dest.h=TAM_MAT;

		texture_->renderFrame(dest,0,11);
	}
}
