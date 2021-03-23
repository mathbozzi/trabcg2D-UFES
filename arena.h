#ifndef ARENA_H_
#define ARENA_H_

#include <iostream>
#include <stdio.h>
#include "lutador.h"

using namespace std;

class Arena
{
	Point pos;
	Cor cor;
	float width;
	float height;

public:
	Arena(float x, float y, float width, float height, Cor c);
	Point ObtemPos();
	Cor ObtemCor();
	void desenhaArena(float width, float height, Cor c);
	void set_vertex(Point p);
	float get_width();
	float get_height();
};

#endif /* ARENA_H_ */
