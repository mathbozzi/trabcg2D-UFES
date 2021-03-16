#ifndef CIRCULO_H_
#define CIRCULO_H_

#include <iostream>
#include <stdio.h>
#include "lutador.h"

using namespace std;

class Circulo {

	Point center;
	float radius;
	Color color;

	public:
	Circulo(Point center, float r, Color c);
	void desenha ();
	void desenha (float deltaX, float deltaY);
	Point get_center() const;
	void set_center(Point c);
	float get_radius() const;
	void set_radius(float r);
	Color get_color() const;
	void set_color(Color c);
	bool outsideOf(Circulo* c) const;
	bool insideOf(Circulo* c) const;
	void print() const;

	friend ostream& operator<<(ostream& output, const Circulo& c);
};

void desenhaCirculo (float radius, Color color);
void desenhaCirculo (float radius, Point center, Color color);

#endif /* CIRCULO_H_ */
