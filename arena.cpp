#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include "arena.h"

using namespace std;

Arena::Arena(float x, float y, float width, float height, Color c){
	// Assuming x and y correspond to the lower-left vertex of the rectangle

	Point v = {x,y};

	this->vertex = v;
	this->width = width;
	this->height = height;
	this->color = c;
}


void desenhaArena (float width, float height, Color c){

	glColor3f(c.r,c.g,c.b);

	glBegin(GL_QUADS);
		glVertex2f(0,0);
		glVertex2f(width,0);
		glVertex2f(width,height);
		glVertex2f(0,height);
	glEnd();

}

// getter for the vertices
Point Arena::get_vertex() const{
	return this->vertex;
}

void Arena::set_vertex(Point v1){
	this->vertex = v1;
}

float Arena::get_width() const{
	return this->width;
}

float Arena::get_height() const{
	return this->height;
}

Color Arena::get_color() const{
	return this->color;
}



// void Arena::print() const{
// 	float r = this->color.r;
// 	float g = this->color.g;
// 	float b = this->color.b;

// 	cout << "< Arena >" << endl;
// 	printf("Vertex: (%f,%f)\n",this->vertex.x,this->vertex.y);
// 	printf("Width: %f\n",this->width);
// 	printf("Height: %f\n",this->height);
// 	printf("Color: (%f,%f,%f)\n",r,g,b);

// }

// ostream& operator<<(ostream& output, const Arena& c){
// 	output << "Sou um Arenarilatero." << endl;
// 	return output;
// }
