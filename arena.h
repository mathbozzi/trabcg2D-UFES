#ifndef ARENA_H_
#define ARENA_H_

#include <iostream>
#include <stdio.h>
#include "lutador.h"

using namespace std;

// This class represents a generic Rectrilateral
class Arena
{
	// The vertex corresponds to the lower-left one
	Point vertex;
	float width;
	float height;
	Cor cor;

public:
	Arena(float x, float y, float width, float height, Cor c);
	Point get_vertex() const;
	float get_width() const;
	float get_height() const;
	Cor get_color() const;
	void set_vertex(Point v1);
	void print() const;
	friend ostream &operator<<(ostream &output, const Arena &c);
	void desenhaArena(float width, float height, Cor c);
};

#endif /* ARENA_H_ */
