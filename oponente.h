#ifndef Oponente_H
#define Oponente_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "lutador.h"

class Oponente
{
    Point centro;
    float raio;
    Cor cor;
    GLfloat OponenteAngulo;
    GLfloat theta1;
    GLfloat theta2;
    GLfloat theta3;
    GLfloat theta4;

public:
    Oponente(Point pos, float raio, Cor cor, GLfloat thetaOponente);
    Point ObtemPosicao();
    float ObtemRaio();
    GLfloat ObtemAnguloJogador();
    void MudaAnguloJogador(float newangle);
    void MudaPosicao(Point pos);
    void MudaTheta1(GLfloat theta1);
    void MudaTheta2(GLfloat theta2);
    void MudaTheta3(GLfloat theta3);
    void MudaTheta4(GLfloat theta4);
    float ObtemTheta1();
    float ObtemTheta2();
    float ObtemTheta3();
    float ObtemTheta4();
    void DesenhaOponente();
    void DesenhaBraco(Point pos, GLfloat theta1, GLfloat theta2, GLfloat theta3, GLfloat theta4);
    void DesenhaCirc(GLint radius, Cor corOponente);
    void DesenhaNariz(GLint radius, Cor corOponente);
    void DesenhaRect(GLint height, GLint width, Cor corBraco);
    void GiraOponente(GLfloat dx);
    void CurvaOponente(GLfloat dr);
    void MoveOponente(float dx, float dy);
    Point verificaSocoDir(float wid, float heig, float thetaBraco, float thetaAntebraco);
    Point verificaSocoEsq(float wid, float heig, float thetaBraco, float thetaAntebraco);
    Point atualizaOponente(bool w, bool s, bool a, bool d, GLdouble timeDiff);
};

#endif /* Oponente_H */
