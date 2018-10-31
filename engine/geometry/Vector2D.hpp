#pragma once

class Vector2D
{
public:
	float x, y;
	
	Vector2D();
	Vector2D(float xPos, float yPos);
	~Vector2D() {}

	void Add(Vector2D vec);
	void Subtract(Vector2D vec);
	void Multiply(Vector2D vec);
	void Multiply(float scalar);
	void Divide(Vector2D vec);
	void Equals(Vector2D vec);

	void set(float x, float y);
};

Vector2D::Vector2D()
{
	x = y = 0;
}

Vector2D::Vector2D(float xPos, float yPos)
{
	x = xPos;
	y = yPos;
}

void Vector2D::Add(Vector2D vec)
{
	x += vec.x;
	y += vec.y;
}

void Vector2D::Subtract(Vector2D vec)
{
	x -= vec.x;
	y -= vec.y;
}

void Vector2D::Multiply(Vector2D vec)
{
	x *= vec.x;
	y *= vec.y;
}

void Vector2D::Multiply(float scalar)
{
	x *= scalar;
	y *= scalar;
}

void Vector2D::Divide(Vector2D vec)
{
	x /= vec.x;
	y /= vec.y;
}

void Vector2D::Equals(Vector2D vec)
{
	x = vec.x;
	y = vec.y;
}
