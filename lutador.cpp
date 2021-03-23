#include <stdio.h>
#include <math.h>
#include "lutador.h"
#include "input.h"
#include "arena.h"

Lutador::Lutador(Point pos, float raio, Cor cor, GLfloat thetaLutador)
{

    this->centro = pos;
    this->cor = cor;
    this->raio = raio;
    this->theta1 = -45;
    this->theta2 = 135;
    this->theta3 = -45;
    this->theta4 = 135;
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

GLfloat Lutador::ObtemAnguloJogador()
{
    return this->lutadorAngulo;
}

float Lutador::ObtemRaio()
{
    return this->raio;
}

float Lutador::ObtemTheta1()
{
    return this->theta1;
}

float Lutador::ObtemTheta2()
{
    return this->theta2;
}

float Lutador::ObtemTheta3()
{
    return this->theta3;
}

float Lutador::ObtemTheta4()
{
    return this->theta4;
}

void Lutador::MudaAnguloJogador(float newangle)
{
    this->lutadorAngulo = newangle;
}

void Lutador::MudaTheta1(GLfloat theta1)
{
    this->theta1 = theta1;
}

void Lutador::MudaTheta2(GLfloat theta2)
{
    this->theta2 = theta2;
}

void Lutador::MudaTheta3(GLfloat theta3)
{
    this->theta3 = theta3;
}

void Lutador::MudaTheta4(GLfloat theta4)
{
    this->theta4 = theta4;
}

void Lutador::MoveLutador(float dx, float dy)
{
    this->centro.x += dx;
    this->centro.y += dy;
}

void Lutador::DesenhaRect(GLint height, GLint width, Cor corBraco)
{
    glColor3f(corBraco.r, corBraco.g, corBraco.b);

    glBegin(GL_QUADS);
    glVertex2f(-height + height, width);
    glVertex2f(-height + height, -width);
    glVertex2f(height + height, -width);
    glVertex2f(height + height, width);
    glEnd();
}

void Lutador::DesenhaCirc(GLint radius, Cor corlutador)
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

void Lutador::DesenhaNariz(GLint radius, Cor corlutador)
{
    glPushMatrix();
    glTranslatef(0, (radius) + (0.1 * radius), 0);
    DesenhaCirc((radius * 0.2), corlutador);
    glPopMatrix();
}

void Lutador::DesenhaBraco(Point pos, GLfloat theta1, GLfloat theta2, GLfloat theta3, GLfloat theta4)
{
    Cor GRAY = {0.5, 0.5, 0.5};
    Cor RED = {1, 0, 0};
    glPushMatrix();

    glPushMatrix();
    glTranslatef(this->raio, 0, 0);
    glRotatef(theta1, 0, 0, 1);
    DesenhaRect(this->raio * sqrt(2) / 2, this->raio * 0.1, GRAY);

    glTranslatef(this->raio * sqrt(2), 0, 0);
    glRotatef(theta2, 0, 0, 1);
    DesenhaRect(this->raio * sqrt(2) / 2, this->raio * 0.1, GRAY);

    glTranslatef(this->raio * sqrt(2), 0, 0);
    DesenhaCirc((this->raio / 2), RED);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-(this->raio), 0, 0);
    glRotatef(-theta3, 0, 0, 1);
    DesenhaRect(-(this->raio * sqrt(2) / 2), this->raio * 0.1, GRAY);

    glTranslatef(-(this->raio * sqrt(2)), 0, 0);
    glRotatef(-theta4, 0, 0, 1);
    DesenhaRect(-(this->raio * sqrt(2) / 2), this->raio * 0.1, GRAY);

    glTranslatef(-(this->raio * sqrt(2)), 0, 0);
    DesenhaCirc((this->raio / 2), RED);
    glPopMatrix();

    glPopMatrix();
}

void Lutador::DesenhaLutador()
{
    glPushMatrix();
    glTranslatef(this->centro.x, this->centro.y, 0);
    glRotatef(this->lutadorAngulo, 0, 0, 1);
    DesenhaBraco(this->centro, theta1, theta2, theta3, theta4);
    DesenhaNariz(this->raio, this->cor);
    DesenhaCirc(this->raio, this->cor);
    glPopMatrix();
}

Point Lutador::atualizaLutador(bool w, bool s, bool a, bool d, GLdouble time)
{
    float dx = 0, dy = 0;
    float velocidadeLutador = 0.1 * time;

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
        dy = velocidadeLutador * cos(M_PI * this->lutadorAngulo / 180.0);
        dx = -velocidadeLutador * sin(M_PI * this->lutadorAngulo / 180.0);
    }
    if (s)
    {
        dy = -velocidadeLutador * cos(M_PI * this->lutadorAngulo / 180.0);
        dx = +velocidadeLutador * sin(M_PI * this->lutadorAngulo / 180.0);
    }

    Point p = {dx, dy};
    return p;
}

Point Lutador::verificaSocoDir(float wid, float heig, float thetaBraco, float thetaAntebraco)
{
    Point luvaDir = {0, 0};

    // antebraço + rotação
    Point a = {(this->raio * (float)sqrt(2)), 0};
    luvaDir = translated(luvaDir, a);
    luvaDir = rotated(luvaDir, thetaAntebraco);

    // braco direito ate cotovelo + rotacao
    Point b = {(float)sqrt(2.0) * this->raio, 0};
    luvaDir = translated(luvaDir, b);
    luvaDir = rotated(luvaDir, thetaBraco);

    //centro(rodado) +raio
    Point c = {this->raio, 0};
    luvaDir = translated(luvaDir, c);

    //angulo jogador central
    luvaDir = rotated(luvaDir, this->lutadorAngulo);

    //centro
    luvaDir = translated(luvaDir, this->ObtemPosicao());

    luvaDir = {luvaDir.x + wid, luvaDir.y + heig};
    // printf("%f,%f\n", luvaDir.x, luvaDir.y);
    return luvaDir;
}

Point Lutador::verificaSocoEsq(float wid, float heig, float thetaBraco, float thetaAntebraco)
{
    Point luvaEsq = {0, 0};

    // antebraço + rotação
    Point a = {-(this->raio * (float)sqrt(2)), 0};
    luvaEsq = translated(luvaEsq, a);
    luvaEsq = rotated(luvaEsq, thetaAntebraco);

    // braco direito ate cotovelo + rotacao
    Point b = {-(float)sqrt(2.0) * this->raio, 0};
    luvaEsq = translated(luvaEsq, b);
    luvaEsq = rotated(luvaEsq, thetaBraco);

    //centro(rodado) +raio
    Point c = {-this->raio, 0};
    luvaEsq = translated(luvaEsq, c);

    //angulo jogador central
    luvaEsq = rotated(luvaEsq, this->lutadorAngulo);

    //centro
    luvaEsq = translated(luvaEsq, this->ObtemPosicao());

    luvaEsq = {luvaEsq.x + wid, luvaEsq.y + heig};
    // printf("%f,%f\n", luvaEsq.x, luvaEsq.y);
    return luvaEsq;
}

Point Lutador::translated(Point p, Point pAntigo)
{
    p.x += pAntigo.x;
    p.y += pAntigo.y;
    return p;
}

Point Lutador::rotated(Point p, float angle)
{
    Point rotated;
    rotated.x = p.x * cos(M_PI * angle / 180.0) - p.y * sin(M_PI * angle / 180.0);
    rotated.y = p.x * sin(M_PI * angle / 180.0) + p.y * cos(M_PI * angle / 180.0);
    return rotated;
}
