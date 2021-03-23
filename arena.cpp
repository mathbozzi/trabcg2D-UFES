#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>
#include "arena.h"

using namespace std;

Arena::Arena(float x, float y, float width, float height, Cor c)
{
	Point p = {x, y};
	this->pos = p;
	this->width = width;
	this->height = height;
	this->cor = c;
}

void desenhaArena(float width, float height, Cor c)
{
	glColor3f(c.r, c.g, c.b);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(width, 0);
	glVertex2f(width, height);
	glVertex2f(0, height);
	glEnd();
}

Point Arena::ObtemPos()
{
	return this->pos;
}

void Arena::set_vertex(Point p)
{
	this->pos = p;
}

float Arena::get_width()
{
	return this->width;
}

float Arena::get_height()
{
	return this->height;
}

Cor Arena::ObtemCor()
{
	return this->cor;
}
