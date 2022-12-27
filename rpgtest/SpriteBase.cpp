
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>

#include <random>

#include "Globals.h"
#include "MathFunctionsHeader.h"

#include "SpriteBase.h"
#include "iostream"

	void Sprite::ResetRect() { SDL_Rect rect; }

	void Sprite::updateSurface(std::string sprfile)
	{
		imagename = sprfile;
		SDL_Surface* surface = IMG_Load((app.datapath + sprfile).c_str());
		tex = SDL_CreateTextureFromSurface(app.Renderer, surface);
		SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
		SDL_FreeSurface(surface);
	}
	Sprite::Sprite(int x, int y, int w, int h, std::string sprfile)
	{
		updateSurface(sprfile);
		isText = false;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
	}
	Sprite::~Sprite()
	{
	}
	void Sprite::start()
	{
	
	}
	void Sprite::update()
	{
		
	}
	void Sprite::deconstructSelf()
	{
		SDL_DestroyTexture(tex);
		delete this;
	}
	void Sprite::makeText(TTF_Font* font, SDL_Color color)
	{
		updateText(font, imagename, color);
		isText = true;
	}
	void Sprite::updateText(TTF_Font* font, std::string text, SDL_Color color)
	{
		SDL_DestroyTexture(tex);
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
		tex = SDL_CreateTextureFromSurface(app.Renderer, surface);
		SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
		SDL_FreeSurface(surface);
	}

	SprT::SprT(int x, int y, int w, int h, std::string sprfile, SDL_Color color) : Sprite(x, y, w, h, sprfile) {
		fcolor = color;
	}
	void SprT::update()
	{
		if (GRandom(1, 4) == 3)
		{
			this->updateText(app.MainFont, "D8f9wf", fcolor);
		}
		else if (GRandom(1, 3) == 2)
		{
			this->updateText(app.MainFont, "DEj3e", fcolor);
		}
		else
		{
			this->updateText(app.MainFont, "BGGGGGGG", fcolor);
		}
	}
	void SprT::deconstructSelf()
	{
		SDL_DestroyTexture(tex);
		delete this;
	}




	spritelist::spritelist()
	{
		spritecount = 0;
	}
	void spritelist::remove(Sprite* spr)
	{
		int return_i = -1;
		int i = 0;
		for (void* v : allsprites)
		{
			if (v == spr)
			{
				return_i = i;
			}
			i += 1;
		}
		if (return_i != -1 && spr != NULL)
		{
			spr->deconstructSelf();
			allsprites.erase(allsprites.begin() + return_i);
			spritecount -= 1;
		}
	}
	//Sprite* spritelist::makeSprite(std::string imagepath, int x, int y, int w, int h)
	//{
	//	Sprite* newsprite = new Sprite(x, y, w, h, imagepath);
	//	allsprites.push_back(newsprite);
	//	spritecount += 1;
	//	//newsprite->start();
	//	return newsprite;
	//}
	Sprite* spritelist::makeText(std::string text, TTF_Font* font, SDL_Color color, int x, int y)
	{
		Sprite* newsprite = new Sprite(x, y, 0, 0, text);
		newsprite->makeText(font, color);
		allsprites.push_back(newsprite);
		spritecount += 1;
		return newsprite;
	}
	//Sprite* spritelist::makeSprT(std::string text, TTF_Font* font, SDL_Color color, int x, int y)
	//{
	//	Sprite* newsprite = new SprT(x, y, 0, 0, text, color);
	//	newsprite->makeText(font, color);
	//	allsprites.push_back(newsprite);
	//	spritecount += 1;
	//	//newsprite->start();
	//	return newsprite;
	//}
	//Sprite* spritelist::makePhysical(int x, int y)
	//{
	//	Sprite* newsprite = new Physical();
	//	newsprite->rect.x = x;
	//	newsprite->rect.y = y;
	//	allsprites.push_back(newsprite);
	//	spritecount += 1;
	//	//newsprite->start();
	//	static_cast<Physical*>(newsprite)->start();
	//	return newsprite;
	//}
	void spritelist::add(Sprite* sprite)
	{
		allsprites.push_back(sprite);
		spritecount += 1;
	}
	void spritelist::update()
	{
		for (Sprite* v : allsprites)
		{
			v->update();
		}
	}
	void spritelist::draw(SDL_Renderer* renderer)
	{
		//SDL_RenderClear(renderer);
		for (Sprite* v : allsprites)
		{
			Sprite spr = *v;
			SDL_RenderCopy(renderer, spr.tex, NULL, &spr.rect);
		}

	}
	void spritelist::empty()
	{
		for (Sprite* v : allsprites)
		{
			v->deconstructSelf();
			spritecount = 0;
		}
	}
