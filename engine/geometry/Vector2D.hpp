#pragma once

class Vector2D
{
private:
	float xPos, yPos;

public:
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(int x, int y);
	~Vector2D() {}

	void Add(Vector2D vec);
	void Subtract(Vector2D vec);
	void Multiply(Vector2D vec);
	void Multiply(float scalar);
	void Divide(Vector2D vec);
	void Equals(Vector2D vec);

	float x() { return xPos; }
	float y() { return yPos; }
	void x(float x) { xPos = x; }
	void y(float y) { yPos = y; }
	void x(int x) { xPos = (float)x; }
	void y(int y) {yPos = (float)y; }

	void set(int x, int y) { xPos = (float)x; yPos = (float)y; }
	void set(float x, float y) { xPos = x; yPos = y; }
};

Vector2D::Vector2D()
{
	xPos = yPos = 0;
}

Vector2D::Vector2D(float x, float y)
{
	xPos = x;
	yPos = y;
}

Vector2D::Vector2D(int x, int y)
{
	xPos = (float)x;
	yPos = (float)y;
}

void Vector2D::Add(Vector2D vec)
{
	xPos += vec.xPos;
	yPos += vec.yPos;
}

void Vector2D::Subtract(Vector2D vec)
{
	xPos -= vec.xPos;
	yPos -= vec.yPos;
}

void Vector2D::Multiply(Vector2D vec)
{
	xPos *= vec.xPos;
	yPos *= vec.yPos;
}

void Vector2D::Multiply(float scalar)
{
	xPos *= scalar;
	yPos *= scalar;
}

void Vector2D::Divide(Vector2D vec)
{
	xPos /= vec.xPos;
	yPos /= vec.yPos;
}

void Vector2D::Equals(Vector2D vec)
{
	xPos = vec.xPos;
	yPos = vec.yPos;
}
