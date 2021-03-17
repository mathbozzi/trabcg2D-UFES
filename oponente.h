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
    Color cor;
    GLfloat OponenteAngulo;
    GLfloat wheelAngulo;
    GLfloat theta1;
    GLfloat theta2;

public:
    Oponente(Point pos, float raio, Color cor, GLfloat thetaOponente);
    Point ObtemPosicao();
    GLfloat ObtemAngulo();
    GLfloat ObtemAnguloJogador();
    void MudaAnguloJogador(float newangle);
    void MudaPosicao(Point pos);
    void DesenhaOponente();
    void DesenhaBraco(Point pos, GLfloat theta1, GLfloat theta2);
    void DesenhaCirc(GLint radius, Color corOponente);
    void DesenhaNariz(GLint radius, Color corOponente);
    void DesenhaRect(GLint height, GLint width, Color corBraco);
    void GiraOponente(GLfloat dx);
    void CurvaOponente(GLfloat dr);
    // void MoveOponente(GLfloat dx);
    void MoveOponente(float dx, float dy);
    Point update(bool w, bool s, bool a, bool d, GLdouble timeDiff);

};

#endif /* Oponente_H */
