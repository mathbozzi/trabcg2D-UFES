#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <iterator>
#include <cmath>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "lutador.h"
#include "oponente.h"
#include "arena.h"
#include "circulo.h"
#include "input.h"

using namespace std;

int keyStatus[256];
static char pontos[32];
void *font = GLUT_BITMAP_9_BY_15;

int animate = 0;

Lutador *lutadorPrincipal = NULL;
Oponente *lutadorOponente = NULL;
Arena *arenaSVG = NULL;

int xAntigo;
int yAntigo;

GLdouble timeGameStarted;

bool lutadorGanhou = false;
bool oponenteGanhou = false;

bool flagSocoDir = false;
bool flagSocoEsq = false;
int contaSocoDirLutador = 0;
int contaSocoEsqLutador = 0;

void posInicialLutadores()
{
	//inicia ponto do lutador
	Point lutadorPoint = lutadorPrincipal->ObtemPosicao();
	lutadorPoint.x = (lutadorPoint.x - (arenaSVG->get_width() / 2));
	lutadorPoint.y = (-(arenaSVG->get_height() / 2) + lutadorPoint.y);
	lutadorPrincipal->MudaPosicao(lutadorPoint);

	//inicia ponto do oponente
	Point oponentePoint = lutadorOponente->ObtemPosicao();
	oponentePoint.x = (oponentePoint.x - (arenaSVG->get_width() / 2));
	oponentePoint.y = (-(arenaSVG->get_height() / 2) + oponentePoint.y);
	lutadorOponente->MudaPosicao(oponentePoint);

	//coloca os dois de frente
	Point result = {oponentePoint.x - lutadorPoint.x, oponentePoint.y - lutadorPoint.y};
	double angle = atan2(result.y, result.x);
	lutadorPrincipal->MudaAnguloJogador(((angle * 180) / M_PI) - 90);
	lutadorOponente->MudaAnguloJogador(-((180 - (angle * 180 / M_PI)) * 2) - (((angle * 180) / M_PI) - 90));
}

void mouse(int botao, int estado, int x, int y)
{
	// Changing y axis orientation
	y = arenaSVG->get_height() - y;

	if (botao == GLUT_LEFT_BUTTON)
	{
		// cout << x << endl;
		// cout << y << endl;
		if (estado == GLUT_DOWN)
		{
			xAntigo = x;
			// lutadorPrincipal->MudaTheta1(0);
		}
		else if (estado == GLUT_UP)
		{
			// cout << x - xAntigo << endl;
			lutadorPrincipal->MudaTheta1(-45);
			lutadorPrincipal->MudaTheta2(135);
			lutadorPrincipal->MudaTheta3(-45);
			lutadorPrincipal->MudaTheta4(135);
		}
	}
	glutPostRedisplay();
}

void verificaSeAcertouSocoDireito(Point p, Oponente *o)
{

	float odX = o->ObtemPosicao().x + arenaSVG->get_width() / 2;
	float odY = o->ObtemPosicao().y + arenaSVG->get_height() / 2;

	float dx = sqrt(pow(p.x - odX, 2) + pow(p.y - odY, 2));

	if (dx >= lutadorPrincipal->ObtemRaio() / 2 + o->ObtemRaio())
	{
		flagSocoDir = true;
	}
	else
	{
		if (flagSocoDir)
		{
			contaSocoDirLutador += 1;
			flagSocoDir = false;
		}
	}
}

void verificaSeAcertouSocoEsquerdo(Point p, Oponente *o)
{

	float odX = o->ObtemPosicao().x + arenaSVG->get_width() / 2;
	float odY = o->ObtemPosicao().y + arenaSVG->get_height() / 2;

	float dx = sqrt(pow(p.x - odX, 2) + pow(p.y - odY, 2));

	if (dx >= lutadorPrincipal->ObtemRaio() / 2 + o->ObtemRaio())
	{
		flagSocoEsq = true;
	}
	else
	{
		if (flagSocoEsq)
		{
			contaSocoEsqLutador += 1;
			flagSocoEsq = false;
		}
	}
}

void movimentoBraco(int x, int y)
{

	int newX = x;
	int newY = arenaSVG->get_height() - y;

	if (x - xAntigo > 0)
	{
		if (x - xAntigo <= arenaSVG->get_width() / 2)
		{
			lutadorPrincipal->MudaTheta1(-45 + (x - xAntigo) * (135 / (arenaSVG->get_width() / 2)));
			lutadorPrincipal->MudaTheta2(135 - (x - xAntigo) * (135 / (arenaSVG->get_width() / 2)));
			Point pSocoDir = lutadorPrincipal->verificaSocoDir(arenaSVG->get_height() / 2, arenaSVG->get_height() / 2, lutadorPrincipal->ObtemTheta1(), lutadorPrincipal->ObtemTheta2());
			verificaSeAcertouSocoDireito(pSocoDir, lutadorOponente);
		}
	}
	else
	{
		if ((x - xAntigo >= (-arenaSVG->get_height() / 2)))
		{
			lutadorPrincipal->MudaTheta3(-45 - (x - xAntigo) * (135 / (arenaSVG->get_width() / 2)));
			lutadorPrincipal->MudaTheta4(135 + (x - xAntigo) * (135 / (arenaSVG->get_width() / 2)));
			Point pSocoEsq = lutadorPrincipal->verificaSocoEsq(arenaSVG->get_height() / 2, arenaSVG->get_height() / 2, -lutadorPrincipal->ObtemTheta3(), -lutadorPrincipal->ObtemTheta4());
			verificaSeAcertouSocoEsquerdo(pSocoEsq, lutadorOponente);
		}
	}
}

void keyUp(unsigned char key, int x, int y)
{
	keyStatus[key] = 0;
	glutPostRedisplay();
}

void keyPress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		animate = !animate;
		break;
	case 'a':
	case 'A':
		keyStatus[(int)('a')] = 1;
		break;
	case 'd':
	case 'D':
		keyStatus[(int)('d')] = 1;
		break;
	case 's':
	case 'S':
		keyStatus[(int)('s')] = 1;
		break;
	case 'w':
	case 'W':
		keyStatus[(int)('w')] = 1;
		break;
	case 27:
		exit(0);
	}
	glutPostRedisplay();
}

void ResetKeyStatus()
{
	int i;
	//Initialize keyStatus
	for (i = 0; i < 256; i++)
		keyStatus[i] = 0;
}

bool dentroArena(Lutador *l, Arena *a)
{
	float x1, y1, r;
	x1 = l->ObtemPosicao().x;
	y1 = l->ObtemPosicao().y;
	r = l->ObtemRaio();

	Point p = a->get_vertex();
	Point inferiorE = {-(p.x + a->get_width() / 2), -(p.x + a->get_height() / 2)};
	Point superiorD = {(p.x + a->get_width() / 2), (p.x + a->get_height() / 2)};

	if ((x1 - r > inferiorE.x && y1 - r > inferiorE.y) && (x1 + r < superiorD.x && y1 + r < superiorD.y))
		return true;
	else
		return false;
}

bool dentroOponente(Lutador *lutadorPrincipal, Oponente *lutadorOponente)
{
	float rlp, rlo, dx;

	Point p = lutadorPrincipal->ObtemPosicao();
	rlp = lutadorPrincipal->ObtemRaio();
	Point o = lutadorOponente->ObtemPosicao();
	rlo = lutadorOponente->ObtemRaio();

	dx = sqrt(pow(p.x - o.x, 2) + pow(p.y - o.y, 2));

	if (dx >= rlp * 2 + rlo * 2)
		return true;
	else
		return false;
}

void idle(void)
{

	static GLdouble previousTime = 0;
	GLdouble currentTime;
	GLdouble timeDifference;

	// Get time from the beginning of the game
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	timeDifference = currentTime - previousTime;
	previousTime = currentTime;

	bool wCheck;
	bool aCheck;
	bool sCheck;
	bool dCheck;

	dCheck = (keyStatus['D'] == 1 || keyStatus['d'] == 1);
	aCheck = (keyStatus['A'] == 1 || keyStatus['a'] == 1);
	wCheck = keyStatus['W'] == 1 || keyStatus['w'] == 1;
	sCheck = keyStatus['S'] == 1 || keyStatus['s'] == 1;

	Point dx = lutadorPrincipal->atualizaLutador(wCheck, sCheck, aCheck, dCheck, timeDifference);

	Arena *a = arenaSVG;
	lutadorPrincipal->MoveLutador(dx.x, 0);

	bool estaDentro = dentroArena(lutadorPrincipal, a); //trata colisao com a arena
	bool estaDentro2 = dentroOponente(lutadorPrincipal, lutadorOponente);
	if (!estaDentro || !estaDentro2)
	{
		lutadorPrincipal->MoveLutador(-dx.x, 0);
	}

	lutadorPrincipal->MoveLutador(0, dx.y);

	estaDentro = dentroArena(lutadorPrincipal, a); //trata colisao com a arena
	estaDentro2 = dentroOponente(lutadorPrincipal, lutadorOponente);
	if (!estaDentro || !estaDentro2)
	{
		lutadorPrincipal->MoveLutador(0, -dx.y);
	}

	if (animate && !lutadorGanhou)
	{
		Point result = {lutadorOponente->ObtemPosicao().x - lutadorPrincipal->ObtemPosicao().x,
						lutadorOponente->ObtemPosicao().y - lutadorPrincipal->ObtemPosicao().y};
		double angle = atan2(result.y, result.x);
		lutadorOponente->MudaAnguloJogador(-((180 - (angle * 180 / M_PI)) * 2) - (((angle * 180) / M_PI) - 90));

		lutadorOponente->MoveOponente(0.1,0);
		lutadorOponente->MoveOponente(0,0.1);


	}

	glutPostRedisplay();
}

void printPontuacao()
{
	if (contaSocoDirLutador + contaSocoEsqLutador >= 10)
	{
		lutadorGanhou = true;
		char *pontuacao;
		sprintf(pontos, "PARABENS, VOCE GANHOU! :D");
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos2f(-(arenaSVG->get_width() / 2) + 5, -(arenaSVG->get_height() / 2) + 10);

		pontuacao = pontos;
		while (*pontuacao)
		{
			glutBitmapCharacter(font, *pontuacao);
			pontuacao++;
		}
	}
	else
	{
		char *pontuacao;
		sprintf(pontos, "Lutador: %2d x %2d Oponente", contaSocoDirLutador + contaSocoEsqLutador, 0);
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos2f(-(arenaSVG->get_width() / 2) + 5, -(arenaSVG->get_height() / 2) + 10);

		pontuacao = pontos;
		while (*pontuacao)
		{
			glutBitmapCharacter(font, *pontuacao);
			pontuacao++;
		}
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	lutadorPrincipal->DesenhaLutador();
	lutadorOponente->DesenhaOponente();
	printPontuacao();

	glFlush();
	glutSwapBuffers();
}

void init(Cor bgCor, float xlim1, float xlim2, float ylim1, float ylim2)
{
	float r = bgCor.r;
	float g = bgCor.g;
	float b = bgCor.b;
	glClearColor((GLfloat)r, (GLfloat)g, (GLfloat)b, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(xlim1 / 2, xlim2 / 2, ylim1 / 2, ylim2 / 2, -100, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv)
{
	string arquivo;
	if (argc > 1)
	{
		arquivo = argv[1];
		arquivo += "config.xml";
	}
	else
	{
		cout << "Digite: ./trabalhocg ./" << endl;
		return 0;
	}
	if (arquivo != "")
	{
		string arenaFile = parseXMLFile(arquivo);

		if (arenaFile != "")
			parseSVGFile(arenaFile);

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		glutInitWindowSize(arenaSVG->get_width(), arenaSVG->get_height());
		glutInitWindowPosition(100, 50);
		glutCreateWindow("Ring");
		Cor bgCor = {arenaSVG->get_color().r, arenaSVG->get_color().g, arenaSVG->get_color().b};
		init(bgCor, -(arenaSVG->get_width()), arenaSVG->get_width(), -(arenaSVG->get_height()), arenaSVG->get_height());
		posInicialLutadores();
		glutDisplayFunc(display);
		glutKeyboardFunc(keyPress);
		glutMouseFunc(mouse);
		glutMotionFunc(movimentoBraco);
		glutKeyboardUpFunc(keyUp);
		glutIdleFunc(idle);
		glutMainLoop();
	}
	else
	{
		cout << "Nome do arquivo da arena vazio. Por favor verifique o seu config.xml\n";
		exit(1);
	}
}
