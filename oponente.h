#ifndef Oponente_H
#define Oponente_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "lutador.h"

class Oponente
{
    Point centro;
    Cor cor;
    float raio;
    GLfloat theta1;
    GLfloat theta2;
    GLfloat theta3;
    GLfloat theta4;
    GLfloat OponenteAngulo;

public:
    Oponente(Point pos, float raio, Cor cor, GLfloat thetaOponente);
    GLfloat ObtemAnguloJogador();
    Point ObtemPosicao();
    Point atualizaOponente(bool w, bool s, bool a, bool d, GLdouble time);
    Point verificaSocoEsqOponente(float wid, float heig, float thetaBraco, float thetaAntebraco);
    Point verificaSocoDirOponente(float wid, float heig, float thetaBraco, float thetaAntebraco);
    Point rotated(Point p, float angle);
    Point translated(Point p, Point pAntigo);
    void DesenhaOponente();
    void MudaPosicao(Point pos);
    void MudaTheta1(GLfloat theta1);
    void MudaTheta2(GLfloat theta2);
    void MudaTheta3(GLfloat theta3);
    void MudaTheta4(GLfloat theta4);
    void CurvaOponente(GLfloat dr);
    void GiraOponente(GLfloat dx);
    void MoveOponente(float dx, float dy);
    void MudaAnguloJogador(float newangle);
    void DesenhaCirc(GLint radius, Cor corOponente);
    void DesenhaNariz(GLint radius, Cor corOponente);
    void DesenhaRect(GLint height, GLint width, Cor corBraco);
    void DesenhaBraco(Point pos, GLfloat theta1, GLfloat theta2, GLfloat theta3, GLfloat theta4);
    float ObtemRaio();
    float ObtemTheta1();
    float ObtemTheta2();
    float ObtemTheta3();
    float ObtemTheta4();
};

#endif /* Oponente_H */
