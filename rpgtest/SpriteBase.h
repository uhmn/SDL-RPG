#pragma once
#include <SDL_ttf.h>
#include <string>
#include <vector>

class Sprite {
public:
	SDL_Texture* tex;
	SDL_Rect rect;
	std::string imagename;
	bool isText;
	unsigned int classtype;
	bool removing;
	int angle;

	void ResetRect();
	void updateSurface(std::string sprfile);
	Sprite(int x, int y, int w, int h, std::string sprfile);
	~Sprite();
	virtual void start();
	virtual void update();
	virtual void deconstructSelf();
	void makeText(TTF_Font* font, SDL_Color color);
	void updateText(TTF_Font* font, std::string text, SDL_Color color);
	void setAlpha(Uint8 alpha);
	virtual void enterData(std::vector<std::string> data);
	virtual std::string getData();
	int getClassType();
	virtual void initialize();
};

class SprT : public Sprite {
public:
	SDL_Color fcolor;
	SprT(int x, int y, int w, int h, std::string sprfile, SDL_Color color);
	void update();
	void deconstructSelf();
};

class spritelist {
public:
	std::vector<Sprite*> allsprites;
	int spritecount;
	spritelist();
	void remove(Sprite* spr);
	Sprite* makeText(std::string text, TTF_Font* font, SDL_Color color, int x = 0, int y = 0);
	void add(Sprite* sprite);
	void update();
	void draw(SDL_Renderer* renderer);
	void empty(bool destroy = false);
};

//extern spritelist SpriteGarbage;