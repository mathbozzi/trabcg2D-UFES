#ifndef OPONENTE_H
#define OPONENTE_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "lutador.h"


// Angle must be in degrees
Point rotateBy(Point p, float angle);

// This assumes that the coordinates of oldOrigin are expressed in terms
// of the new coordinate system
Point translateFrom(Point p, Point oldOrigin);

class Oponente
{
    Point centro;
    float raio;
    Color cor;
    GLfloat theta1;
    GLfloat theta2;

public:
    Oponente(Point pos, float raio, Color cor);
    Point get_position();
    void set_position(Point pos);
    void DesenhaOponente();
    void DesenhaBraco(Point pos, GLfloat theta1, GLfloat theta2);
    void DesenhaCirc(GLint radius, Color corOponente);
    void DesenhaNariz(GLint radius, Color corOponente);
    void DesenhaRect(GLint height, GLint width, Color corBraco);
    void MoveEmX(GLfloat dx);
    void MoveEmY(GLfloat dx);

};

#endif /* Oponente_H */
