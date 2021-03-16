#ifndef RECT_H_
#define RECT_H_

#include <iostream>
#include <stdio.h>
#include "lutador.h"

using namespace std;

// This class represents a generic Rectrilateral
class Retangulo
{
	// The vertex corresponds to the lower-left one
	Point vertex;
	float width;
	float height;
	Color color;

public:
	Retangulo(float x, float y, float width, float height, Color c);
	Point get_vertex() const;
	float get_width() const;
	float get_height() const;
	Color get_color() const;
	void set_vertex(Point v1);
	void print() const;
	friend ostream &operator<<(ostream &output, const Retangulo &c);
	void desenhaRetangulo(float width, float height, Color c);
	// void desenhaRetangulo(float width, float height, Color c, float xTrans, float yTrans);
};

#endif /* RECT_H_ */
