#ifndef Oponente_H
#define Oponente_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "lutador.h"


class Oponente
{
    Point centro;
    float raio;
    GLfloat thetaOponente;
    Cor cor;
    GLfloat OponenteAngulo;
    GLfloat theta1;
    GLfloat theta2;

public:
    Oponente(Point pos, float raio, Cor cor, GLfloat thetaOponente);
    Point ObtemPosicao();
    float ObtemRaio();
    GLfloat ObtemAngulo();
    GLfloat ObtemAnguloJogador();
    void MudaAnguloJogador(float newangle);
    void MudaPosicao(Point pos);
    void DesenhaOponente();
    void DesenhaBraco(Point pos, GLfloat theta1, GLfloat theta2);
    void DesenhaCirc(GLint radius, Cor corOponente);
    void DesenhaNariz(GLint radius, Cor corOponente);
    void DesenhaRect(GLint height, GLint width, Cor corBraco);
    void GiraOponente(GLfloat dx);
    void CurvaOponente(GLfloat dr);
    // void MoveOponente(GLfloat dx);
    void MoveOponente(float dx, float dy);
    Point update(bool w, bool s, bool a, bool d, GLdouble timeDiff);

};

#endif /* Oponente_H */
