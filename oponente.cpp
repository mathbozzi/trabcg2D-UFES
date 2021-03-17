#include <stdio.h>
#include <math.h>
#include "oponente.h"
#include "input.h"

Oponente::Oponente(Point pos, float raio, Color cor, GLfloat thetaOponente)
{

    this->centro = pos;
    this->cor = cor;
    this->raio = raio;
    this->thetaOponente = thetaOponente;
    this->theta1 = -45;
    this->theta2 = 135;
    this->OponenteAngulo = 0;
    this->wheelAngulo = 0;
}

Point Oponente::ObtemPosicao()
{
    return this->centro;
}

void Oponente::MudaPosicao(Point pos)
{
    this->centro = pos;
}

GLfloat Oponente::ObtemAngulo()
{
    return this->wheelAngulo;
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

void Oponente::DesenhaOponente()
{
    glPushMatrix();
    {
        glTranslatef(this->centro.x, this->centro.y, 0);
        glRotatef(this->OponenteAngulo, 0, 0, 1);
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

// void Oponente::MoveOponente(GLfloat dx)
// {
//     glTranslatef(dx * 100, 0, 0);
// }

// void Oponente::CurvaOponente(GLfloat dr)
// {
//     this->thetaOponente = this->thetaOponente + dr * 100;
//     glTranslatef(dr * 100, 0, 0);
// }

// void Oponente::GiraOponente(GLfloat dy)
// {
//     // glPushMatrix();
//     this->thetaOponente = this->thetaOponente + dy * 100;
//     // glTranslatef(0, dy * 100, 0);
//     // glPopMatrix();
//     // gThetaWheel = gThetaWheel + (dx * 200); // falta rodar as rodas
// }

GLfloat Oponente::ObtemAnguloJogador(){
    return this->OponenteAngulo;
}

void Oponente::MudaAnguloJogador(float newangle){
    this->OponenteAngulo = newangle;
}

void Oponente::MoveOponente(float dx, float dy)
{
    this->centro.x += dx;
    this->centro.y += dy;
}

Point Oponente::update(bool w, bool s, bool a, bool d, GLdouble timeDiff)
{

    float playerSpeed = 0.1*timeDiff;
    float dx = 0, dy = 0;
    float wheelAngle = this->wheelAngulo;
    float playerAngle = this->OponenteAngulo;

    if (d && wheelAngle > -45 + 1){
        this->wheelAngulo -= 1;
    }

    if (a && wheelAngulo < 45 - 1)
        this->wheelAngulo += 1;

    if (w)
    {
        if (wheelAngulo > 0)
        {
            this->wheelAngulo -= 1;
            this->OponenteAngulo += 1;
        }
        else if (wheelAngulo < 0)
        {
            this->wheelAngulo += 1;
            this->OponenteAngulo -= 1;
        }

        dy = playerSpeed * cos(M_PI * playerAngle / 180.0);
        dx = -playerSpeed * sin(M_PI * playerAngle / 180.0);
    }

    if (s)
    {
        if (wheelAngulo > 0)
        {
            this->wheelAngulo -= 1;
            this->OponenteAngulo -= 1;
        }
        else if (wheelAngulo < 0)
        {
            this->wheelAngulo += 1;
            this->OponenteAngulo += 1;
        }

        dy = -playerSpeed * cos(M_PI * playerAngle / 180.0);
        dx = +playerSpeed * sin(M_PI * playerAngle / 180.0);
    }


    Point p = {dx, dy};

    return p;
}

// glutIgnoreKeyRepeat(true)