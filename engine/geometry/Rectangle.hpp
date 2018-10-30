#pragma once

#include "Vector2D.hpp"

/**
 * It's a rectangle, it shouldn't need documentation.
 */
class Rectangle
{
private:
	float width, height;
	Vector2D position;

public:
	Rectangle() {
		width = height = 0;
		position.set(0, 0);
	}
	
	Rectangle(float w, float h)
	{
		width = w;
		height = h;
		position.set(0, 0);
	}
	
	Rectangle(float x, float y, float w, float h)
	{
		width = w;
		height = h;
		position.set(x, y);
	}

	~Rectangle() { }
	
	void Equals(Rectangle rect)
	{
		width = rect.width;
		height = rect.height;
		position.Equals(rect.position);
	}

	float x() { return position.x(); }
	float y() { return position.y(); }
	float w() { return width; }
	float h() { return height; }
	Vector2D pos() { return position; }
	
	void x(float x) { position.x(x); }
	void y(float y) { position.y(y); }
	void w(float w) { width = w; }
	void h(float h) { height = h; }
	void pos(Vector2D pos) { position = pos; }
};
