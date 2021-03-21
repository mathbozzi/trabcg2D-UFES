#ifndef CIRCULO_H_
#define CIRCULO_H_

#include <iostream>
#include <stdio.h>
#include "lutador.h"

using namespace std;

class Circulo {

	Point center;
	float radius;
	Cor cor;

	public:
	Circulo(Point center, float r, Cor c);
	void desenha ();
	void desenha (float deltaX, float deltaY);
	Point get_center() const;
	void set_center(Point c);
	float get_radius() const;
	void set_radius(float r);
	Cor get_color() const;
	void set_color(Cor c);
	bool outsideOf(Circulo* c) const;
	bool insideOf(Circulo* c) const;
	void print() const;

};

void desenhaCirculo (float radius, Cor cor);
void desenhaCirculo (float radius, Point center, Cor cor);

#endif /* CIRCULO_H_ */
