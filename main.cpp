#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include "lutador.h"
#include "oponente.h"
#include "arena.h"
#include "input.h"

using namespace std;

int animate = 0;
int keyStatus[256];
static char pontos[100];
void *font = GLUT_BITMAP_9_BY_15;

Arena *arenaSVG = NULL;
Lutador *lutadorPrincipal = NULL;
Oponente *lutadorOponente = NULL;

float facil = 0.5;
float medio = 0.9;
float dificil = 1.5;
bool dificuldadeFacil = false;
bool dificuldadeMedio = false;
bool dificuldadeDificil = false;

int xAntigo;
int yAntigo;
int contaSocoDirLutador = 0;
int contaSocoEsqLutador = 0;
bool lutadorGanhou = false;
bool oponenteGanhou = false;
bool flagSocoDir = false;
bool flagSocoEsq = false;

int flag1SocoDirOp = 0;
int flag1SocoEsqOp = 0;
bool flagSocoDirOp = false;
bool flagSocoEsqOp = false;
int contaSocoDirOponente = 0;
int contaSocoEsqOponente = 0;

void posInicialLutadores()
{
	//inicia ponto do lutador
	Point lutadorPoint = lutadorPrincipal->ObtemPosicao();
	lutadorPoint.x = (lutadorPoint.x - (arenaSVG->get_width() / 2));
	lutadorPoint.y = (+(arenaSVG->get_height() / 2) - lutadorPoint.y);
	lutadorPrincipal->MudaPosicao(lutadorPoint);

	//inicia ponto do oponente
	Point oponentePoint = lutadorOponente->ObtemPosicao();
	oponentePoint.x = (oponentePoint.x - (arenaSVG->get_width() / 2));
	oponentePoint.y = ((arenaSVG->get_height() / 2) - oponentePoint.y);
	lutadorOponente->MudaPosicao(oponentePoint);

	//coloca os dois de frente
	Point result = {oponentePoint.x - lutadorPoint.x, oponentePoint.y - lutadorPoint.y};
	double angle = atan2(result.y, result.x);
	lutadorPrincipal->MudaAnguloJogador(((angle * 180) / M_PI) - 90);
	lutadorOponente->MudaAnguloJogador(-((180 - (angle * 180 / M_PI)) * 2) - (((angle * 180) / M_PI) - 90));
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

void verificaSeAcertouSocoDireitoOponente(Point p, Lutador *l)
{
	float odX = l->ObtemPosicao().x + arenaSVG->get_width() / 2;
	float odY = l->ObtemPosicao().y + arenaSVG->get_height() / 2;

	float dx = sqrt(pow(p.x - odX, 2) + pow(p.y - odY, 2));

	if (dx >= lutadorOponente->ObtemRaio() / 2 + l->ObtemRaio())
	{
		flagSocoDirOp = true;
	}
	else
	{
		if (flagSocoDirOp)
		{
			contaSocoDirOponente += 1;
			flagSocoDirOp = false;
			flagSocoEsqOp = true;
		}
	}
}

void verificaSeAcertouSocoEsquerdoOponente(Point p, Lutador *l)
{
	float odX = l->ObtemPosicao().x + arenaSVG->get_width() / 2;
	float odY = l->ObtemPosicao().y + arenaSVG->get_height() / 2;

	float dx = sqrt(pow(p.x - odX, 2) + pow(p.y - odY, 2));

	if (dx >= lutadorOponente->ObtemRaio() / 2 + l->ObtemRaio())
	{
		flagSocoEsqOp = true;
	}
	else
	{
		if (flagSocoEsqOp)
		{
			contaSocoEsqOponente += 1;
			flagSocoEsqOp = false;
			flagSocoDirOp = true;
		}
	}
}

bool dentroArenaLutador(Lutador *l, Arena *a)
{
	float x1, y1, r;
	x1 = l->ObtemPosicao().x;
	y1 = l->ObtemPosicao().y;
	r = l->ObtemRaio();

	Point p = a->ObtemPos();
	Point inferiorE = {-(p.x + a->get_width() / 2), -(p.x + a->get_height() / 2)};
	Point superiorD = {(p.x + a->get_width() / 2), (p.x + a->get_height() / 2)};

	if ((x1 - r > inferiorE.x && y1 - r > inferiorE.y) && (x1 + r < superiorD.x && y1 + r < superiorD.y))
		return true;
	else
		return false;
}

bool dentroArenaOponente(Oponente *o, Arena *a)
{
	float x1, y1, r;
	x1 = o->ObtemPosicao().x;
	y1 = o->ObtemPosicao().y;
	r = o->ObtemRaio();

	Point p = a->ObtemPos();
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

bool dentroLutador(Lutador *lutadorPrincipal, Oponente *lutadorOponente)
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

void printPontuacao()
{
	if (dificuldadeFacil || dificuldadeMedio || dificuldadeDificil)
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
		else if (contaSocoDirOponente + contaSocoEsqOponente >= 10)
		{
			oponenteGanhou = true;
			char *pontuacao;
			sprintf(pontos, "VOCE PERDEU, TENTE NOVAMENTE!");
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
			sprintf(pontos, "Lutador: %2d x %2d Oponente", contaSocoDirLutador + contaSocoEsqLutador, contaSocoDirOponente + contaSocoEsqOponente);
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
	else
	{
		char *pontuacao;
		sprintf(pontos, "CLIQUE NA DIFICULDADE:    FACIL     MEDIO      DIFICIL");
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

void mouse(int botao, int estado, int x, int y)
{
	y = arenaSVG->get_height() - y;

	if (botao == GLUT_LEFT_BUTTON)
	{
		if (x > 235 && x < 290 && y > 0 && y < 25)
		{
			dificuldadeFacil = true;
			dificuldadeMedio = false;
			dificuldadeDificil = false;
		}
		else if (x > 325 && x < 380 && y > 0 && y < 25)
		{
			dificuldadeMedio = true;
			dificuldadeFacil = false;
			dificuldadeDificil = false;
		}
		else if (x > 425 && x < 500 && y > 0 && y < 25)
		{
			dificuldadeMedio = false;
			dificuldadeFacil = false;
			dificuldadeDificil = true;
		}

		if (estado == GLUT_DOWN)
		{
			xAntigo = x;
		}
		else if (estado == GLUT_UP)
		{
			lutadorPrincipal->MudaTheta1(-45);
			lutadorPrincipal->MudaTheta2(135);
			lutadorPrincipal->MudaTheta3(-45);
			lutadorPrincipal->MudaTheta4(135);
		}
	}
	glutPostRedisplay();
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
			lutadorPrincipal->MudaTheta2(135 - (x - xAntigo) * (110 / (arenaSVG->get_width() / 2)));
			Point pSocoDir = lutadorPrincipal->verificaSocoDir(arenaSVG->get_width() / 2, arenaSVG->get_height() / 2, lutadorPrincipal->ObtemTheta1(), lutadorPrincipal->ObtemTheta2());
			verificaSeAcertouSocoDireito(pSocoDir, lutadorOponente);
		}
	}
	else
	{
		if ((x - xAntigo >= (-arenaSVG->get_height() / 2)))
		{
			lutadorPrincipal->MudaTheta3(-45 - (x - xAntigo) * (135 / (arenaSVG->get_height() / 2)));
			lutadorPrincipal->MudaTheta4(135 + (x - xAntigo) * (110 / (arenaSVG->get_height() / 2)));
			Point pSocoEsq = lutadorPrincipal->verificaSocoEsq(arenaSVG->get_width() / 2, arenaSVG->get_height() / 2, -lutadorPrincipal->ObtemTheta3(), -lutadorPrincipal->ObtemTheta4());
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

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	lutadorPrincipal->DesenhaLutador();
	lutadorOponente->DesenhaOponente();
	printPontuacao();

	glutSwapBuffers();
}

void idle(void)
{
	if ((dificuldadeFacil || dificuldadeMedio || dificuldadeDificil) && (!lutadorGanhou || !oponenteGanhou))
	{
		static GLdouble previousTime = 0;
		GLdouble currentTime;
		GLdouble timeDifference;
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
		bool estaDentro = dentroArenaLutador(lutadorPrincipal, a); //trata colisao com a arena
		bool estaDentro2 = dentroOponente(lutadorPrincipal, lutadorOponente);
		if (!estaDentro || !estaDentro2)
		{
			lutadorPrincipal->MoveLutador(-dx.x, 0);
		}

		lutadorPrincipal->MoveLutador(0, dx.y);
		estaDentro = dentroArenaLutador(lutadorPrincipal, a); //trata colisao com a arena
		estaDentro2 = dentroOponente(lutadorPrincipal, lutadorOponente);
		if (!estaDentro || !estaDentro2)
		{
			lutadorPrincipal->MoveLutador(0, -dx.y);
		}

		//MOVIMENTO DO OPONENTE
		if (animate && !lutadorGanhou && !oponenteGanhou)
		{
			Point result = {lutadorOponente->ObtemPosicao().x - lutadorPrincipal->ObtemPosicao().x,
							lutadorOponente->ObtemPosicao().y - lutadorPrincipal->ObtemPosicao().y};
			double angle = atan2(result.y, result.x);
			lutadorOponente->MudaAnguloJogador(-((180 - (angle * 180 / M_PI)) * 2) - (((angle * 180) / M_PI) - 90));

			float dificuldade, angulo;
			if (dificuldadeFacil)
			{
				dificuldade = facil;
				angulo = 0.9;
			}
			else if (dificuldadeMedio)
			{
				dificuldade = medio;
				angulo = 0.85;
			}
			else if (dificuldadeDificil)
			{
				dificuldade = dificil;
				angulo = 0.75;
			}
			Point dy;
			if (result.x > 0)
			{
				dy = lutadorOponente->atualizaOponente(true, false, false, true, dificuldade * timeDifference);
			}
			else if (result.x < 0)
			{
				dy = lutadorOponente->atualizaOponente(true, false, true, false, dificuldade * timeDifference);
			}

			lutadorOponente->MoveOponente(dy.x, 0);
			bool estaDentroOp = dentroArenaOponente(lutadorOponente, a);
			bool estaDentro2Op = dentroLutador(lutadorPrincipal, lutadorOponente);
			if (!estaDentroOp || !estaDentro2Op)
			{
				lutadorOponente->MoveOponente(-dy.x, 0);
				unsigned seed = time(0);
				srand(seed);
				int i = ((int)arenaSVG->get_width() / 2 * dificuldade * 0.7) + rand() % ((int)arenaSVG->get_width() / 2);
				if (i > ((int)arenaSVG->get_width() / 2))
				{
					i = ((int)arenaSVG->get_width() / 2);
				}
				unsigned seed2 = time(0);
				srand(seed2);
				int x = rand() % 2;
				if (x % 2 == 0)
				{
					{
						lutadorOponente->MudaTheta1(-45 + i * (135 / (arenaSVG->get_width() / 2)));
						lutadorOponente->MudaTheta2(135 - i * (angulo * 135 / (arenaSVG->get_width() / 2)));
						Point pSocoDirOp = lutadorOponente->verificaSocoDirOponente(arenaSVG->get_width() / 2, arenaSVG->get_height() / 2, lutadorOponente->ObtemTheta1(), lutadorOponente->ObtemTheta2());
						if (!flag1SocoDirOp)
						{
							pSocoDirOp = {0, 0};
							flag1SocoDirOp++;
						}
						verificaSeAcertouSocoDireitoOponente(pSocoDirOp, lutadorPrincipal);
						//tentar fazer um loop devagar
					}
					lutadorOponente->MudaTheta3(-45);
					lutadorOponente->MudaTheta4(135);
				}
				else
				{
					lutadorOponente->MudaTheta1(-45);
					lutadorOponente->MudaTheta2(135);
					{
						lutadorOponente->MudaTheta3(-45 + i * (135 / (arenaSVG->get_width() / 2)));
						lutadorOponente->MudaTheta4(135 - i * (angulo * 135 / (arenaSVG->get_width() / 2)));
						Point pSocoEsqOp = lutadorOponente->verificaSocoEsqOponente(arenaSVG->get_width() / 2, arenaSVG->get_height() / 2, -lutadorOponente->ObtemTheta3(), -lutadorOponente->ObtemTheta4());
						if (!flag1SocoEsqOp)
						{
							pSocoEsqOp = {0, 0};
							flag1SocoEsqOp++;
						}
						verificaSeAcertouSocoEsquerdoOponente(pSocoEsqOp, lutadorPrincipal);
						//voltar devagar
					}
				}
			}
			else
			{
				lutadorOponente->MudaTheta1(-45);
				lutadorOponente->MudaTheta2(135);
				lutadorOponente->MudaTheta3(-45);
				lutadorOponente->MudaTheta4(135);
			}

			lutadorOponente->MoveOponente(0, dy.y);
			estaDentro = dentroArenaOponente(lutadorOponente, a);
			estaDentro2 = dentroOponente(lutadorPrincipal, lutadorOponente);
			if (!estaDentro || !estaDentro2)
			{
				lutadorOponente->MoveOponente(0, -dy.y);
			}
		}
	}
	glutPostRedisplay();
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
		cout << "Digite: ./trabalhocg config/" << endl;
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
		glutInitWindowPosition(100, 0);
		glutCreateWindow("RING");
		Cor corDeFundo = {arenaSVG->ObtemCor().r, arenaSVG->ObtemCor().g, arenaSVG->ObtemCor().b};
		init(corDeFundo, -(arenaSVG->get_width()), arenaSVG->get_width(), -(arenaSVG->get_height()), arenaSVG->get_height());
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
		cout << "Seu arquivo XML não pode estar vazio!\n";
		exit(1);
	}
}
