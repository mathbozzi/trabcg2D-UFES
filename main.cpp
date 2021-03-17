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
#include "retangulo.h"
#include "circulo.h"
#include "input.h"

using namespace std;

#define INC_KEY 1
#define INC_KEYIDLE 0.01
int keyStatus[256];
static char str[32];
void *font = GLUT_BITMAP_9_BY_15;

// Viewing dimensions
const GLint ViewingWidth = 600;
const GLint ViewingHeight = 600;

int animate = 0;

Lutador *lutadorPrincipal = NULL;
Oponente *lutadorOponente = NULL;
Retangulo *arenaSVG = NULL;

// Global to save last mouse position
float lastMouseX;
float lastMouseY;

// Global to save the mouse status
bool mousePressed;

// Says whether the game has started or not
bool gameStarted = false;
GLdouble timeGameStarted;

// Says if the game is over
bool gameOver = false;

// Says if the player has won or lost
bool playerWon;

// This function calculates the deltas to adjust all coordinates so the center
// of the arena is the new origin
void setNewOrigin()
{
	//inicia ponto do lutador 
	Point lutadorPoint = lutadorPrincipal->ObtemPosicao();
	lutadorPoint.x = (lutadorPoint.x - (arenaSVG->get_height() / 2));
	lutadorPoint.y = ((arenaSVG->get_height() / 2) - lutadorPoint.y);
	lutadorPrincipal->MudaPosicao(lutadorPoint);

	//inicia ponto do oponente 
	Point oponentePoint = lutadorOponente->ObtemPosicao();
	oponentePoint.x = (oponentePoint.x - (arenaSVG->get_height() / 2));
	oponentePoint.y = ((arenaSVG->get_height() / 2) - oponentePoint.y);
	lutadorOponente->MudaPosicao(oponentePoint);

	//coloca os dois de frente 
	Point result = {oponentePoint.x - lutadorPoint.x, oponentePoint.y - lutadorPoint.y};
	double angle = atan2(result.y,result.x);	
	lutadorPrincipal->MudaAnguloJogador(((angle*180)/M_PI)-90);
	lutadorOponente->MudaAnguloJogador(-((180-(angle*180/M_PI))*2)-(((angle*180)/M_PI)-90));
}

void mouse(int botao, int estado, int x, int y)
{
	// Changing y axis orientation
	y = ViewingHeight - y;

	if (botao == GLUT_LEFT_BUTTON)
	{

		if (estado == GLUT_DOWN)
			mousePressed = true;
		else if (mousePressed)
		{
			// In this case the mouse was pressed.
			// trying to detect a press+release task
			printf("%i", y);
		}
	}

	glutPostRedisplay();
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
		keyStatus[(int)('a')] = 1; //Using keyStatus trick
		break;
	case 'd':
	case 'D':
		keyStatus[(int)('d')] = 1; //Using keyStatus trick
		break;
	case 's':
	case 'S':
		keyStatus[(int)('s')] = 1; //Using keyStatus trick
		break;
	case 'w':
	case 'W':
		keyStatus[(int)('w')] = 1; //Using keyStatus trick
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

void idle(void)
{

	static GLdouble previousTime = 0;
	GLdouble currentTime;
	GLdouble timeDifference;

	// Get time from the beginning of the game
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	timeDifference = currentTime - previousTime;
	previousTime = currentTime;

	float wheelAngle = lutadorPrincipal->ObtemAngulo();
	bool wCheck;
	bool aCheck;
	bool sCheck;
	bool dCheck;

	dCheck = (keyStatus['D'] == 1 || keyStatus['d'] == 1) && wheelAngle > -45 - 1;
	aCheck = (keyStatus['A'] == 1 || keyStatus['a'] == 1) && wheelAngle < 45 + 1;
	wCheck = keyStatus['W'] == 1 || keyStatus['w'] == 1;
	sCheck = keyStatus['S'] == 1 || keyStatus['s'] == 1;

	Point delta = lutadorPrincipal->update(wCheck, sCheck, aCheck, dCheck, timeDifference);
	Point oldPos = lutadorPrincipal->ObtemPosicao();

	lutadorPrincipal->MoveLutador(delta.x, 0);
	//tratar colisao
	lutadorPrincipal->MoveLutador(0, delta.y);
	//tratar colisao
	Point newPos = lutadorPrincipal->ObtemPosicao(); //muda posicao lutador

	//Control animation
	// if (animate)
	// {
	// 	static int dir = 1;
	// 	if (lutadorOponente->ObtemX() > (ViewingWidth / 2))
	// 	{
	// 		dir *= -1;
	// 	}
	// 	else if (lutadorOponente->ObtemX() < -(ViewingWidth / 2))
	// 	{
	// 		dir *= -1;
	// 	}
	// 	lutadorOponente->MoveEmX(dir * INC_KEYIDLE);
	// }

	glutPostRedisplay();
}

void printTimer()
{

	static int minutes = 0;
	static GLdouble seconds = 0;
	GLdouble currentTime;
	GLdouble elapsed;

	if (gameStarted && !gameOver)
	{
		// Get time from the beginning of the game
		currentTime = glutGet(GLUT_ELAPSED_TIME);

		elapsed = currentTime - timeGameStarted;
		minutes = (int)elapsed / 60000;
		seconds = elapsed / 1000 - minutes * 60;
	}

	//Create a string to be printed
	char *tmpStr;
	sprintf(str, "Time: %2d:%02.2f", minutes, seconds);
	//Define the position to start printing
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(ViewingHeight / 2 - 15 * 9, ViewingHeight / 2 - 20);
	//Print  the first Char with a certain font
	//glutBitmapLength(font,(unsigned char*)str);
	tmpStr = str;
	//Print each of the other Char at time

	while (*tmpStr)
	{
		glutBitmapCharacter(font, *tmpStr);
		tmpStr++;
	}
}

void display(void)
{
	// Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT);

	lutadorPrincipal->DesenhaLutador();
	lutadorOponente->DesenhaOponente();

	// printPontuacao();
	glFlush();

	glutSwapBuffers(); // Desenha the new frame of the game.
}

void init(Color bgColor, float xlim1, float xlim2, float ylim1, float ylim2)
{
	/*select background color */
	float r = bgColor.r;
	float g = bgColor.g;
	float b = bgColor.b;
	glClearColor((GLfloat)r, (GLfloat)g, (GLfloat)b, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(xlim1 / 2, xlim2 / 2, ylim1 / 2, ylim2 / 2, -100.0, 100.0);

	// glMatrixMode(GL_MODELVIEW); // Select the projection matrix
	// glLoadIdentity();
}

int main(int argc, char **argv)
{
	string filePath;

	// Confere se o arquivo XML foi passado como parametro de entrada
	if (argc > 1)
	{
		filePath = argv[1];
		filePath += "config.xml";
	}
	else
	{
		cout << "Por favor entre com o arquivo XML" << endl;
		cout << "Ex: trabalhocg <caminho para pasta de config.xml>" << endl;
		return 0;
	}

	if (filePath != "")
	{
		string arenaFile = parseXMLFile(filePath);

		if (arenaFile != "")
			parseSVGFile(arenaFile);

		glutInit(&argc, argv);

		// Utilizar Double Buffer e esquema de cores RGB
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

		// cout << arenaSVG->get_height() <<endl;
		// cout << arenaSVG->get_width() <<endl;

		glutInitWindowSize(arenaSVG->get_width(), arenaSVG->get_height());

		// Escolher posicao da janela na tela
		glutInitWindowPosition(100, 50);

		// Definindo o titulo da janela
		glutCreateWindow("Ring");

		//Cor de fundo
		Color bgColor = {arenaSVG->get_color().r, arenaSVG->get_color().g, arenaSVG->get_color().b};

		init(bgColor, -(arenaSVG->get_width()), arenaSVG->get_width(), -(arenaSVG->get_height()), arenaSVG->get_height());
		setNewOrigin();
		glutDisplayFunc(display);
		glutKeyboardFunc(keyPress);
		// glutMouseFunc(mouse);
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
