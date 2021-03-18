#include <stdio.h>
#include <math.h>
#include "lutador.h"
#include "input.h"
#include "arena.h"

Lutador::Lutador(Point pos, float raio, Color cor, GLfloat thetaLutador)
{

    this->centro = pos;
    this->cor = cor;
    this->raio = raio;
    this->theta1 = -45;
    this->theta2 = 135;
    this->lutadorAngulo = thetaLutador;
}

Point Lutador::ObtemPosicao()
{
    return this->centro;
}

void Lutador::MudaPosicao(Point pos)
{
    this->centro = pos;
}

void Lutador::DesenhaRect(GLint height, GLint width, Color corBraco)
{
    glColor3f(corBraco.r, corBraco.g, corBraco.b);

    glBegin(GL_QUADS);
    {
        glVertex2f(-height + height, width);
        // printf("(%f,%f)\n",(float)-height,(float) width+width);
        glVertex2f(-height + height, -width);
        // printf("(%f,%f)\n",(float)-height,(float) -width+width);
        glVertex2f(height + height, -width);
        // printf("(%f,%f)\n",(float)height,(float) -width+width);
        glVertex2f(height + height, width);
        // printf("(%f,%f)\n",(float)height,(float) width+width);
    }
    glEnd();
}

void Lutador::DesenhaCirc(GLint radius, Color corlutador)
{

    GLfloat circle_points = 50;
    glBegin(GL_POLYGON);
    for (int i = 0; i < circle_points; i++)
    {
        double angle = 2 * 3.141592 * i / circle_points;
        glColor3f(corlutador.r, corlutador.g, corlutador.b);
        glVertex2f(radius * cos(angle), radius * sin(angle));
    }
    glEnd();
}

void Lutador::DesenhaNariz(GLint radius, Color corlutador)
{
    glPushMatrix();
    {
        glTranslatef(0, (radius) + (0.1 * radius), 0);
        DesenhaCirc((radius * 0.2), corlutador);
    }
    glPopMatrix();
}

void Lutador::DesenhaBraco(Point pos, GLfloat theta1, GLfloat theta2)
{
    Color GRAY = {0.5, 0.5, 0.5};
    Color RED = {1, 0, 0};
    glPushMatrix();
    {
        glPushMatrix();
        {
            glTranslatef(this->raio, 0, 0);
            glRotatef(theta1, 0, 0, 1);
            DesenhaRect(this->raio * sqrt(2) / 2, this->raio * 0.1, GRAY);

            glTranslatef(this->raio * sqrt(2), 0, 0);
            glRotatef(theta2, 0, 0, 1);
            DesenhaRect(this->raio * sqrt(2) / 2, this->raio * 0.1, GRAY);

            glTranslatef(this->raio * sqrt(2), 0, 0);
            DesenhaCirc((this->raio / 2), RED);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(-(this->raio), 0, 0);
            glRotatef(-theta1, 0, 0, 1);
            DesenhaRect(-(this->raio * sqrt(2) / 2), this->raio * 0.1, GRAY);

            glTranslatef(-(this->raio * sqrt(2)), 0, 0);
            glRotatef(-theta2, 0, 0, 1);
            DesenhaRect(-(this->raio * sqrt(2) / 2), this->raio * 0.1, GRAY);

            glTranslatef(-(this->raio * sqrt(2)), 0, 0);
            DesenhaCirc((this->raio / 2), RED);
        }
        glPopMatrix();
    }
    glPopMatrix();
}

void Lutador::DesenhaLutador()
{
    glPushMatrix();
    {
        glTranslatef(this->centro.x, this->centro.y, 0);
        glRotatef(this->lutadorAngulo, 0, 0, 1);
        DesenhaBraco(this->centro, theta1, theta2);
        DesenhaNariz(this->raio, this->cor);
        DesenhaCirc(this->raio, this->cor);
    }
    glPopMatrix();
}

// void Lutador::RodaBraco1(GLfloat inc)
// {
//     gTheta1 = gTheta1 + inc;
// }

// void Lutador::RodaBraco2(GLfloat inc)
// {
//     gTheta2 = gTheta2 + inc;
// }

// void Lutador::MoveLutador(GLfloat dx)
// {
//     glTranslatef(dx * 100, 0, 0);
// }

// void Lutador::CurvaLutador(GLfloat dr)
// {
//     this->thetaLutador = this->thetaLutador + dr * 100;
//     glTranslatef(dr * 100, 0, 0);
// }

// void Lutador::GiraLutador(GLfloat dy)
// {
//     // glPushMatrix();
//     this->thetaLutador = this->thetaLutador + dy * 100;
//     // glTranslatef(0, dy * 100, 0);
//     // glPopMatrix();
//     // gThetaWheel = gThetaWheel + (dx * 200); // falta rodar as rodas
// }

GLfloat Lutador::ObtemAnguloJogador()
{
    return this->lutadorAngulo;
}

float Lutador::ObtemRaio()
{
    return this->raio;
}

void Lutador::MudaAnguloJogador(float newangle)
{
    this->lutadorAngulo = newangle;
}

void Lutador::MoveLutador(float dx, float dy)
{
    this->centro.x += dx;
    this->centro.y += dy;
}

Point Lutador::atualizaLutador(bool w, bool s, bool a, bool d, GLdouble timeDiff)
{

    float valocidadeLutador = 0.1 * timeDiff;
    float dx = 0, dy = 0;
    float playerAngle = this->lutadorAngulo;

    if (d)
    {
        this->lutadorAngulo = this->lutadorAngulo - 1;
    }

    if (a)
    {
        this->lutadorAngulo = this->lutadorAngulo + 1;
    }

    if (w)
    {
        dy = valocidadeLutador * cos(M_PI * playerAngle / 180.0);
        dx = -valocidadeLutador * sin(M_PI * playerAngle / 180.0);
    }

    if (s)
    {
        dy = -valocidadeLutador * cos(M_PI * playerAngle / 180.0);
        dx = +valocidadeLutador * sin(M_PI * playerAngle / 180.0);
    }

    Point p = {dx, dy};

    return p;
}

// int Lutador::estaDentro(Arena *a)
// {
//     // 	float x1,x2,r;

//     // 	x1 = this.;
//     // 	y1 = this->position.y;
//     // 	r = this->radius;

//     //   Point ccenter = c->get_center();
//     //   float cradius = c->get_radius();

//     // 	x2 = ccenter.x;
//     // 	y2 = ccenter.y;
//     // 	r2 = cradius;

//     // 	float dist = sqrt(pow(x1-x2,2) + pow(y1-y2,2));

//     // 	if(dist <= r2 - r1)
//     // 		return true;
//     // 	else
//     return 0;
// }

// glutIgnoreKeyRepeat(true)