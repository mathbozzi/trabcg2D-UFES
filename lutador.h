#ifndef LUTADOR_H
#define LUTADOR_H
#include <GL/gl.h>
#include <GL/glu.h>

typedef struct tPoint
{
    float x;
    float y;
} Point;

typedef struct tCor
{
    float r;
    float g;
    float b;
} Cor;

class Lutador
{
    Point centro;
    float raio;
    Cor cor;
    GLfloat lutadorAngulo;
    GLfloat theta1;
    GLfloat theta2;
    GLfloat theta3;
    GLfloat theta4;

public:
    Lutador(Point pos, float raio, Cor cor, GLfloat thetaLutador);
    GLfloat ObtemAnguloJogador();
    Point ObtemPosicao();
    Point atualizaLutador(bool w, bool s, bool a, bool d, GLdouble time);
    Point verificaSocoDir(float wid, float heig, float thetaBraco, float thetaAntebraco);
    Point verificaSocoEsq(float wid, float heig, float thetaBraco, float thetaAntebraco);
    Point rotated(Point p, float angle);
    Point translated(Point p, Point pAntigo);
    void MudaAnguloJogador(float newangle);
    void MudaPosicao(Point pos);
    void MudaTheta1(GLfloat theta1);
    void MudaTheta2(GLfloat theta2);
    void MudaTheta3(GLfloat theta3);
    void MudaTheta4(GLfloat theta4);
    void DesenhaLutador();
    void GiraLutador(GLfloat dx);
    void CurvaLutador(GLfloat dr);
    void MoveLutador(float dx, float dy);
    void DesenhaCirc(GLint radius, Cor corlutador);
    void DesenhaNariz(GLint radius, Cor corlutador);
    void DesenhaRect(GLint height, GLint width, Cor corBraco);
    void DesenhaBraco(Point pos, GLfloat theta1, GLfloat theta2, GLfloat theta3, GLfloat theta4);
    float ObtemRaio();
    float ObtemTheta1();
    float ObtemTheta2();
    float ObtemTheta3();
    float ObtemTheta4();
};

#endif /* LUTADOR_H */
