#include "Vector2D.hpp"
#include "Rectangle.hpp"

#include <iostream>
using namespace std;

void TestVectorConstructors()
{
	Vector2D vec1;
	if (vec1.x() != 0 || vec1.y() != 0)
		cout << "Vector2D::Vector2D() failed" << endl;

	Vector2D vec2(-1, 1);
	if (vec2.x() != -1 || vec2.y() != 1)
		cout << "Vector2d::Vector2D(int, int) failed" << endl;

	Vector2D vec3(1.0f, -1.0f);
	if (vec3.x() != 1 || vec3.y() != -1)
		cout << "Vector2D::Vector2D(float, float) failes" << endl;
}

void TestVectorOperators()
{
	Vector2D vec1(-5, 10);
	Vector2D vec2(12, 2);
	float scalar = 0.5;

	vec1.Add(vec2);
	if (vec1.x() != 7 || vec1.y() != 12 || vec2.x() != 12 || vec2.y() != 2)
		cout << "Vector2D::Add(Vector2D) failed" << endl;

	vec1.Subtract(vec2);
	if (vec1.x() != -5 || vec1.y() != 10 || vec2.x() != 12 || vec2.y() != 2)
		cout << "Vector2D::Subtract(Vector2D) failed" << endl;

	vec1.Multiply(vec2);
	if (vec1.x() != -60 || vec1.y() != 20 || vec2.x() != 12 || vec2.y() != 2)
		cout << "Vector2D::Multiply(Vector2D) failed" << endl;

	vec1.Multiply(scalar);
	if (vec1.x() != -30 || vec1.y() != 10)
		cout << "Vector2D::Multiply(float) failed" << endl;

	vec1.Divide(vec2);
	if (vec1.x() != -30/12.0f || vec1.y() != 10/2.0f || vec2.x() != 12 || vec2.y() != 2)
		cout << "Vector2D::Divide(Vector2D) failed" << endl;

	vec1.Equals(vec2);
	if (vec1.x() != 12 || vec1.y() != 2 || vec2.x() != 12 || vec2.y() != 2)
		cout << "Vector2D::Equals(Vector2D) failed" << endl;
}

void TestVectorGettersSetters()
{
	Vector2D vec1(1, 2);
	if (vec1.x() != 1)
		cout << "Vector2D::x() failed" << endl;
	if (vec1.y() != 2)
		cout << "Vector2D::y() failed" << endl;

	vec1.x(3);
	vec1.y(4);
	if (vec1.x() != 3)
		cout << "Vector2D::x(int) failed" << endl;
	if (vec1.y() != 4)
		cout << "Vector2D::y(int) failed" << endl;

	vec1.x(1.0f);
	vec1.y(2.0f);
	if (vec1.x() != 1)
		cout << "Vector2D::x(float) failed" << endl;
	if (vec1.y() != 2)
		cout << "Vector2D::y(float) failed" << endl;

	vec1.set(3, 4);
	if (vec1.x() != 3 || vec1.y() != 4)
		cout << "Vector2D::position(int, int) failed" << endl;

	vec1.set(1, 2);
	if (vec1.x() != 1 || vec1.y() != 2)
		cout << "Vector2D::position(float, float) failed" << endl;
}

void TestRectangleConstructors()
{
	Rectangle rect1;
	if (rect1.x() != 0 || rect1.y() != 0 || rect1.w() != 0 || rect1.h() != 0)
		cout << "Rectangle::Rectangle() failed" << endl;

	Rectangle rect2(10.0f, 20.0f);
	if (rect2.x() != 0 || rect2.y() != 0 || rect2.w() != 10 || rect2.h() != 20)
		cout << "Rectangle::Rectangle(float, float) failed" << endl;

	Rectangle rect3(1.0f, 2.0f, 10.0f, 20.0f);
	if (rect3.x() != 1 || rect3.y() != 2 || rect3.w() != 10 || rect3.h() != 20)
		cout << "Rectangle::Rectangle(float, float) failed" << endl;
}

int main()
{
	TestVectorConstructors();
	TestVectorOperators();
	TestVectorGettersSetters();

	TestRectangleConstructors();
	
	return 0;
}
