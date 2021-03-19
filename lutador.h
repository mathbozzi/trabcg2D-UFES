#ifndef LUTADOR_H
#define LUTADOR_H
#include <GL/gl.h>
#include <GL/glu.h>


typedef struct tPoint
{
    float x;
    float y;
} Point;

typedef struct tColor
{
    float r;
    float g;
    float b;
} Color;

// Angle must be in degrees
Point rotateBy(Point p, float angle);

// This assumes that the coordinates of oldOrigin are expressed in terms
// of the new coordinate system
Point translateFrom(Point p, Point oldOrigin);

class Lutador
{
    Point centro;
    float raio;
    Color cor;
    GLfloat lutadorAngulo;
    GLfloat theta1;
    GLfloat theta2;
    GLfloat theta3;
    GLfloat theta4;

public:
    Lutador(Point pos, float raio, Color cor, GLfloat thetaLutador);
    Point ObtemPosicao();
    float ObtemRaio();
    GLfloat ObtemAnguloJogador();
    void MudaAnguloJogador(float newangle);
    void MudaPosicao(Point pos);
    void MudaTheta1(GLfloat theta1);
    void MudaTheta2(GLfloat theta2);
    void MudaTheta3(GLfloat theta3);
    void MudaTheta4(GLfloat theta4);
    void DesenhaLutador();
    void DesenhaBraco(Point pos, GLfloat theta1, GLfloat theta2,GLfloat theta3, GLfloat theta4);
    void DesenhaCirc(GLint radius, Color corlutador);
    void DesenhaNariz(GLint radius, Color corlutador);
    void DesenhaRect(GLint height, GLint width, Color corBraco);
    void GiraLutador(GLfloat dx);
    void CurvaLutador(GLfloat dr);
    // void MoveLutador(GLfloat dx);
    void MoveLutador(float dx, float dy);
    // int estaDentro(Arena *a);
    Point atualizaLutador(bool w, bool s, bool a, bool d, GLdouble timeDiff);
};

#endif /* LUTADOR_H */
