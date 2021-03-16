#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include "retangulo.h"

using namespace std;

Retangulo::Retangulo(float x, float y, float width, float height, Color c){
	// Assuming x and y correspond to the lower-left vertex of the rectangle

	Point v = {x,y};

	this->vertex = v;
	this->width = width;
	this->height = height;
	this->color = c;
}


void desenhaRetangulo (float width, float height, Color c){

	glColor3f(c.r,c.g,c.b);

	glBegin(GL_QUADS);
		glVertex2f(0,0);
		glVertex2f(width,0);
		glVertex2f(width,height);
		glVertex2f(0,height);
	glEnd();

}

// void desenhaRetangulo (float width, float height, Color c, float xTrans, float yTrans){
	
// 	glPushMatrix();
// 	glColor3f(c.r,c.g,c.b);
// 	// glTranslatef(xTrans,yTrans,1); 
// 	// Needed to invert y axis because of SVG and OpenGL's different y-axis
// 	// orientation

// 	glBegin(GL_QUADS);
// 		glVertex2f(0,0);
// 		glVertex2f(width,0);
// 		glVertex2f(width,height);
// 		glVertex2f(0,height);
// 	glEnd();

// 	glPopMatrix();
// }

// getter for the vertices
Point Retangulo::get_vertex() const{
	return this->vertex;
}

void Retangulo::set_vertex(Point v1){
	this->vertex = v1;
}

float Retangulo::get_width() const{
	return this->width;
}

float Retangulo::get_height() const{
	return this->height;
}

Color Retangulo::get_color() const{
	return this->color;
}



// void Retangulo::print() const{
// 	float r = this->color.r;
// 	float g = this->color.g;
// 	float b = this->color.b;

// 	cout << "< Retangulo >" << endl;
// 	printf("Vertex: (%f,%f)\n",this->vertex.x,this->vertex.y);
// 	printf("Width: %f\n",this->width);
// 	printf("Height: %f\n",this->height);
// 	printf("Color: (%f,%f,%f)\n",r,g,b);

// }

// ostream& operator<<(ostream& output, const Retangulo& c){
// 	output << "Sou um Retangulorilatero." << endl;
// 	return output;
// }
