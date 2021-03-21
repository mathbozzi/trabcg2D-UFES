#include <stdio.h>
#include <math.h>
#include "oponente.h"
#include "input.h"

Oponente::Oponente(Point pos, float raio, Cor cor, GLfloat thetaOponente)
{

    this->centro = pos;
    this->cor = cor;
    this->raio = raio;
    this->thetaOponente = thetaOponente;
    this->theta1 = -45;
    this->theta2 = 135;
    this->OponenteAngulo = 0;
}

Point Oponente::ObtemPosicao()
{
    return this->centro;
}


float Oponente::ObtemRaio()
{
    return this->raio;
}

void Oponente::MudaPosicao(Point pos)
{
    this->centro = pos;
}


void Oponente::DesenhaRect(GLint height, GLint width, Cor corBraco)
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

void Oponente::DesenhaCirc(GLint radius, Cor corOponente)
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

void Oponente::DesenhaNariz(GLint radius, Cor corOponente)
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
    Cor GRAY = {0.5, 0.5, 0.5};
    Cor RED = {1, 0, 0};
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
    float playerAngle = this->OponenteAngulo;

    if (d){
        this->OponenteAngulo -= 1;
    }

    if (a)
        this->OponenteAngulo += 1;

    if (w)
    {
        dy = playerSpeed * cos(M_PI * playerAngle / 180.0);
        dx = -playerSpeed * sin(M_PI * playerAngle / 180.0);
    }

    if (s)
    {
        dy = -playerSpeed * cos(M_PI * playerAngle / 180.0);
        dx = +playerSpeed * sin(M_PI * playerAngle / 180.0);
    }


    Point p = {dx, dy};

    return p;
}

// glutIgnoreKeyRepeat(true)