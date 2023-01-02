#include <SDL.h>
#include "Vectors.h"
#include <math.h>

vec2d::vec2d(double x0, double y0) {
	x = x0;
	y = y0;
}
vec2d::vec2d(SDL_Rect recta) {
	x = recta.x;
	y = recta.y;
}
vec2d::vec2d() {
	x = 0;
	y = 0;
}

void vec2d::Add(vec2d newvar) {
	x += newvar.x;
	y += newvar.y;
}
void vec2d::Sub(vec2d newvar) {
	x -= newvar.x;
	y -= newvar.y;
}
void vec2d::Mult(vec2d newvar) {
	x *= newvar.x;
	y *= newvar.y;
}
void vec2d::Div(vec2d newvar) {
	x /= newvar.x;
	y /= newvar.y;
}

void vec2d::Add(double newvar) {
	x += newvar;
	y += newvar;
}
void vec2d::Sub(double newvar) {
	x -= newvar;
	y -= newvar;
}
void vec2d::Mult(double newvar) {
	x *= newvar;
	y *= newvar;
}
void vec2d::Div(double newvar) {
	x /= newvar;
	y /= newvar;
}

vec2d vec2d::Add(vec2d vec1, vec2d vec2) {
	vec2d newvec;
	newvec.x = vec1.x;
	newvec.y = vec1.y;
	newvec.x += vec2.x;
	newvec.y += vec2.y;
	return newvec;
}
vec2d vec2d::Sub(vec2d vec1, vec2d vec2) {
	vec2d newvec;
	newvec.x = vec1.x;
	newvec.y = vec1.y;
	newvec.x -= vec2.x;
	newvec.y -= vec2.y;
	return newvec;
}
vec2d vec2d::Mult(vec2d vec1, vec2d vec2) {
	vec2d newvec;
	newvec.x = vec1.x;
	newvec.y = vec1.y;
	newvec.x *= vec2.x;
	newvec.y *= vec2.y;
	return newvec;
}
vec2d vec2d::Div(vec2d vec1, vec2d vec2) {
	vec2d newvec;
	newvec.x = vec1.x;
	newvec.y = vec1.y;
	newvec.x /= vec2.x;
	newvec.y /= vec2.y;
	return newvec;
}

vec2d vec2d::Add(vec2d vec1, double newvar) {
	vec2d newvec;
	newvec.x = vec1.x;
	newvec.y = vec1.y;
	newvec.x += newvar;
	newvec.y += newvar;
	return newvec;
}
vec2d vec2d::Sub(vec2d vec1, double newvar) {
	vec2d newvec;
	newvec.x = vec1.x;
	newvec.y = vec1.y;
	newvec.x -= newvar;
	newvec.y -= newvar;
	return newvec;
}
vec2d vec2d::Mult(vec2d vec1, double newvar) {
	vec2d newvec;
	newvec.x = vec1.x;
	newvec.y = vec1.y;
	newvec.x *= newvar;
	newvec.y *= newvar;
	return newvec;
}
vec2d vec2d::Div(vec2d vec1, double newvar) {
	vec2d newvec;
	newvec.x = vec1.x;
	newvec.y = vec1.y;
	newvec.x /= newvar;
	newvec.y /= newvar;
	return newvec;
}
vec2d vec2d::Round( vec2d oldvec ) {
	vec2d newvec;
	newvec.x = round(oldvec.x);
	newvec.y = round(oldvec.y);
	return newvec;
}

void vec2d::Round() {
	x = round(x);
	y = round(y);
}
double vec2d::Distance(vec2d vec1, vec2d vec2) {
	double x1 = vec1.x;
	double y1 = vec1.y;
	double x2 = vec2.x;
	double y2 = vec2.y;
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
void vec2d::SetRectToVector(SDL_Rect* rect, vec2d vec) {
	rect->x = vec.x;
	rect->y = vec.y;
}
void vec2d::SetToRect(SDL_Rect rect) {
	x = rect.x;
	y = rect.y;
}

bool vec2d::Collision(vec2d mins, vec2d maxs, vec2d check) {
	if (check.x > mins.x &&
		check.y > mins.y &&
		check.x < maxs.x &&
		check.y < maxs.y)
		 { return true; }

	else { return false; }
}

bool vec2d::SquareCollision(vec2d box, vec2d check, int boxwidth) {
	if (vec2d::Collision(vec2d::Sub(box, boxwidth/2), vec2d::Add(box, boxwidth/2), check))
	{
		return true;
	}

	else { return false; }
}

double vec2d::Largest(vec2d lis) {
	double t1 = fabs(lis.x);
	double t2 = fabs(lis.y);
	if (t1 > t2) { return t1; }
	else { return t2; }
}