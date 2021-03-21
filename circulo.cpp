#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <cmath>
#include "circulo.h"
#include "lutador.h"

using namespace std;

Circulo::Circulo(Point center, float r, Cor c){
	this->center = center;
	this->radius = r;
	this->cor = c;
}

void Circulo::desenha (){
	glPushMatrix();

	glColor3f(this->cor.r,this->cor.g,this->cor.b);


	glTranslatef(this->center.x,this->center.y,1);
	// Needed to invert y axis because of SVG and OpenGL's different y-axis
	// orientation

	int i;
	float x,y;
	glBegin(GL_POLYGON);
	// Let`s use 36 vertices to draw the circle as a polygon
	for(i = 0 ; i < 360 ; i += 4 ){
		x = radius*cos(M_PI*i/180.0);
		y = radius*sin(M_PI*i/180.0);
		glVertex3f(x,y,0);
	}
	glEnd();

	glPopMatrix();
}

void Circulo::desenha (float deltaX, float deltaY){
	glPushMatrix();

	glColor3f(this->cor.r,this->cor.g,this->cor.b);


	glTranslatef(this->center.x + deltaX,-this->center.y + deltaY,1);
	// Needed to invert y axis because of SVG and OpenGL's different y-axis
	// orientation

	int i;
	float x,y;
	glBegin(GL_POLYGON);
	// Let`s use 36 vertices to draw the circle as a polygon
	for(i = 0 ; i < 360 ; i += 4 ){
		x = radius*cos(M_PI*i/180.0);
		y = radius*sin(M_PI*i/180.0);
		glVertex3f(x,y,0);
	}
	glEnd();

	glPopMatrix();
}

Point Circulo::get_center() const{
	return this->center;
}

void Circulo::set_center(Point c){
	this->center = c;
}

float Circulo::get_radius() const{
	return this->radius;
}

void Circulo::set_radius(float r){
	this->radius = r;
}

Cor Circulo::get_color() const{
	return this->cor;
}

void Circulo::set_color(Cor c){
	this->cor = c;
}

//Draws a circle centered in the origin
void desenhaCircle (float radius, Cor cor){

	glColor3f(cor.r,cor.g,cor.b);

	int i;
	float x,y;
	glBegin(GL_POLYGON);
	// Let`s use 36 vertices to draw the circle as a polygon
	for(i = 0 ; i < 360 ; i += 4 ){
		x = radius*cos(M_PI*i/180.0);
		y = radius*sin(M_PI*i/180.0);
		glVertex3f(x,y,0);
	}
	glEnd();

}

//Draws a circle centered at center
void desenhaCircle (float radius, Point center, Cor cor){

	glPushMatrix();

	glColor3f(cor.r,cor.g,cor.b);
	glTranslatef(center.x,center.y,0);

	// Needed to invert y axis because of SVG and OpenGL's different y-axis
	// orientation

	int i;
	float x,y;
	glBegin(GL_POLYGON);
	// Let`s use 36 vertices to draw the circle as a polygon
	for(i = 0 ; i < 360 ; i += 4 ){
		x = radius*cos(M_PI*i/180.0);
		y = radius*sin(M_PI*i/180.0);
		glVertex3f(x,y,0);
	}
	glEnd();

	glPopMatrix();
}
