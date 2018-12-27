#pragma once

#include "Vector2D.hpp"

/**
 * It's a rectangle, it shouldn't need documentation.
 */
class Rectangle
{
public:
	float x, y, w, h;
	
	Rectangle() {
		x = y = w = h = 0;
	}
	
	Rectangle(float width, float height)
	{
		w = width;
		h = height;
		x = y = 0;
	}
	
	Rectangle(float xPos, float yPos, float width, float height)
	{
		x = xPos;
		y = yPos;
		w = width;
		h = height;	  
	}

	~Rectangle() { }
	
	void Equals(Rectangle rect)
	{
		w = rect.w;
		h = rect.h;
		x = rect.x;
		y = rect.y;
	}

	void SetSize(float width, float height)
	{
		w = width;
		h = height;
	}
};
