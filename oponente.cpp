#include <stdio.h>
#include <math.h>
#include "oponente.h"
#include "input.h"

Oponente::Oponente(Point pos, float raio, Color cor)
{

    this->centro = pos;
    this->cor = cor;
    this->raio = raio;
    this->theta1 = -45;
    this->theta2 = 135;
}

Point Oponente::get_position()
{
    return this->centro;
}

void Oponente::set_position(Point pos)
{
    this->centro = pos;
}

void Oponente::DesenhaRect(GLint height, GLint width, Color corBraco)
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

void Oponente::DesenhaCirc(GLint radius, Color corOponente)
{

    GLfloat circle_points = 50;
    glBegin(GL_POLYGON);
    for (int i = 0; i < circle_points; i++)
    {
        double angle = 2 * 3.141592 * i / circle_points;
        glColor3f(corOponente.r, corOponente.g, corOponente.b);
        glVertex2f(radius * cos(angle), radius * sin(angle));
    }
    glEnd();
}

void Oponente::DesenhaNariz(GLint radius, Color corOponente)
{
    glPushMatrix();
    {
        glTranslatef(0, (radius) + (0.1 * radius), 0);
        DesenhaCirc((radius * 0.2), corOponente);
    }
    glPopMatrix();
}

void Oponente::DesenhaBraco(Point pos, GLfloat theta1, GLfloat theta2)
{
    Color GRAY = {0.5, 0.5, 0.5};
    Color RED = {1, 0, 0};
    glPushMatrix();
    {
        glPushMatrix();
        {
            glTranslatef(this->raio, 0, 0);
            glRotatef(theta1, 0, 0, 1);
            DesenhaRect(this->raio * sqrt(2) / 2, this->raio*0.1, GRAY);

            glTranslatef(this->raio * sqrt(2), 0, 0);
            glRotatef(theta2, 0, 0, 1);
            DesenhaRect(this->raio * sqrt(2) / 2, this->raio*0.1, GRAY);

            glTranslatef(this->raio * sqrt(2), 0, 0);
            DesenhaCirc((this->raio / 2), RED);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(-(this->raio), 0, 0);
            glRotatef(-theta1, 0, 0, 1);
            DesenhaRect(-(this->raio * sqrt(2) / 2), this->raio*0.1, GRAY);

            glTranslatef(-(this->raio * sqrt(2)), 0, 0);
            glRotatef(-theta2, 0, 0, 1);
            DesenhaRect(-(this->raio * sqrt(2) / 2), this->raio*0.1, GRAY);

            glTranslatef(-(this->raio * sqrt(2)), 0, 0);
            DesenhaCirc((this->raio / 2), RED);
        }
        glPopMatrix();
    }
    glPopMatrix();
}

void Oponente::DesenhaOponente()
{

    glPushMatrix();
    {
        glTranslatef(this->centro.x, this->centro.y, 0);
        // DesenhaRect(baseWidth, baseHeight, 1.0f, 0.0f, 0.0f);
        DesenhaBraco(this->centro, theta1, theta2);
        DesenhaNariz(this->raio, this->cor);
        DesenhaCirc(this->raio, this->cor);
    }
    glPopMatrix();
}

// void Oponente::RodaBraco1(GLfloat inc)
// {
//     gTheta1 = gTheta1 + inc;
// }

// void Oponente::RodaBraco2(GLfloat inc)
// {
//     gTheta2 = gTheta2 + inc;
// }

void Oponente::MoveEmX(GLfloat dx)
{
    // glPushMatrix();
    glTranslatef(dx * 100, 0, 0);
    // glPopMatrix();
    // gThetaWheel = gThetaWheel + (dx * 200); // falta rodar as rodas
}

void Oponente::MoveEmY(GLfloat dy)
{
    // glPushMatrix();
    glTranslatef(0, dy * 100, 0);
    // glPopMatrix();
    // gThetaWheel = gThetaWheel + (dx * 200); // falta rodar as rodas
}

// glutIgnoreKeyRepeat(true)