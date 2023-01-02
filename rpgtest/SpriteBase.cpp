
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>

#include <random>

#include "Globals.h"
#include "MathFunctionsHeader.h"

#include "SpriteBase.h"
#include "iostream"
#include "Ents.h"

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
		removing = false;
		angle = 0;
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
		//removing = true;
		//SpriteGarbage.add(this);
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
	void Sprite::setAlpha(Uint8 alpha)
	{
		SDL_SetTextureAlphaMod(tex, alpha);
	}
	void Sprite::enterData(std::vector<std::string> data)
	{

	}
	std::string Sprite::getData()
	{
		std::string sussy = "what";
		return sussy;
	}
	int Sprite::getClassType()
	{
		return classtype;
	}
	void Sprite::initialize()
	{
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
			allsprites.erase(allsprites.begin() + return_i);
			spritecount -= 1;
		}
	}
	Sprite* spritelist::makeText(std::string text, TTF_Font* font, SDL_Color color, int x, int y)
	{
		Sprite* newsprite = new Sprite(x, y, 0, 0, text);
		newsprite->makeText(font, color);
		allsprites.push_back(newsprite);
		spritecount += 1;
		return newsprite;
	}
	void spritelist::add(Sprite* sprite)
	{
		allsprites.push_back(sprite);
		spritecount += 1;
	}
	void spritelist::update()
	{
		//std::vector<Sprite*> vectorcopy = allsprites;
		int lastspritecount = spritecount;
		int i = 0;
		while (spritecount > i) {
			Sprite* sprite = allsprites[i];
			if (sprite != nullptr) { sprite->update(); }
			i++;
			i += spritecount - lastspritecount;
			lastspritecount = spritecount;
		}
		//for (Sprite* v : vectorcopy)
		//{
		//
		//	if (v != nullptr) { v->update(); }
		//}
	}
	void spritelist::draw(SDL_Renderer* renderer)
	{
		for (Sprite* v : allsprites)
		{
			Sprite spr = *v;
			//if (spr.removing == true) {
			//	//remove(v); idk
			//	delete v;
			//}
			//else {
				spr.rect.x -= spr.rect.w*0.5;
				spr.rect.y -= spr.rect.h*0.5;
				SDL_RenderCopyEx(renderer, spr.tex, NULL, &spr.rect, spr.angle, NULL, SDL_FLIP_NONE);
			//}
		}

	}
	void spritelist::empty(bool destroy)
	{
		//int i = 0;
		while (allsprites.size() > 0) {
			Sprite* v = allsprites.back();
			if (/*v->removing == 0 || v->removing == 1*/destroy) { SDL_DestroyTexture(v->tex); delete v; ents.allsprites.remove(v); }
			allsprites.pop_back();
		}
		spritecount = 0;
	}

//spritelist SpriteGarbage;