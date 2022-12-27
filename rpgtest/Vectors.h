#pragma once

struct vec2d {
	double x;
	double y;

	vec2d(double x0, double y1);
	vec2d();
	void Add(vec2d newvar);
	void Sub(vec2d newvar);
	void Mult(vec2d newvar);
	void Div(vec2d newvar);

	void Add(double newvar);
	void Sub(double newvar);
	void Mult(double newvar);
	void Div(double newvar);

	static vec2d Add(vec2d vec1, vec2d vec2);
	static vec2d Sub(vec2d vec1, vec2d vec2);
	static vec2d Mult(vec2d vec1, vec2d vec2);
	static vec2d Div(vec2d vec1, vec2d vec2);
	static vec2d Add(vec2d vec1, double newvar);
	static vec2d Sub(vec2d vec1, double newvar);
	static vec2d Mult(vec2d vec1, double newvar);
	static vec2d Div(vec2d vec1, double newvar);
	static vec2d Round(vec2d oldvec);

	void Round();
	static double Distance(vec2d vec1, vec2d vec2);
	static void SetRectToVector(SDL_Rect* rect, vec2d vec);
	void SetToRect(SDL_Rect rect);
	static bool Collision(vec2d mins, vec2d maxs, vec2d check);
};