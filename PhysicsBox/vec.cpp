#include "vec.hpp"
#include <cmath>

namespace phbox
{
	vec2::vec2() { x=y=0; }

	vec2::vec2(float a, float b): x(a), y(b) {}

	float vec2::module() { return sqrt(x*x+y*y); }

	vec2 vec2::operator+(vec2 v) 
	{ 
		return vec2(this->x+v.x, this->y+v.y);
	}

	vec2 vec2::operator-(vec2 v)
	{
		return vec2(this->x-v.x, this->y-v.y);
	}

	vec2 vec2::operator*(float n)
	{
		return vec2(this->x*n, this->y*n);
	}

	vec2 vec2::operator/(float n)
	{
		return vec2(this->x/n, this->y/n);
	}

	float vec2::operator*(vec2 v) // Скалярное произведение
	{
		return this->x*v.x+this->y*v.y;
	}

	vec2::~vec2() {}

	float distance(vec2 v0, vec2 v1) { return sqrt((v0.x-v1.x)*(v0.x-v1.x)-(v0.y-v1.y)*(v0.y-v1.y)); }
};