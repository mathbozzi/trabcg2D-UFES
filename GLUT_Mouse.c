// **************************************************
//  GLUT_Mouse.c
//
// Exemplo de programa pra controlar o mouse em uma 
// janela OpenGL
//
//
// **************************************************

#include <stdio.h>
#include <GL/glut.h>

// Called to draw scene
void RenderScene(void)
{
        // Clear the window with current clearing color
        glClear(GL_COLOR_BUFFER_BIT);

        // Set current drawing color to red
        //      R     G         B
        glColor3f(1.0f, 0.0f, 0.0f);

        // Draw a filled rectangle with current color
        glRectf(100.0f, 150.0f, 150.0f, 100.0f);

        // Flush drawing commands
        glFlush();
}


// Setup the rendering state
void SetupRC(void)
{
    // Set clear color to blue
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}


// Called by GLUT library when the window has changed size
void ChangeSize(GLsizei w, GLsizei h)
{
        // Prevent a divide by zero
        if(h == 0)
     h = 1;
     
        // Set Viewport to window dimensions
        glViewport(0, 0, w, h);

        // Reset coordinate system
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        // Establish clipping volume (left, right, bottom, top, near, far)
        if (w <= h) 
     glOrtho (0.0f, 250.0f, 0.0f, 250.0f*h/w, 1.0, -1.0);
        else 
     glOrtho (0.0f, 250.0f*w/h, 0.0f, 250.0f, 1.0, -1.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}
// **************************************************
// Fun��o chamada quando o mouse � pressionado 
// ou liberado
// **************************************************
void MouseClick (int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON: printf("Botao esquerdo.");
                                                        break;
        case GLUT_RIGHT_BUTTON: printf("Botao direito.");
                                                        break;
        case GLUT_MIDDLE_BUTTON: printf("Botao do meio.");
                                                        break;
    }
    if (state == GLUT_DOWN)
        printf("Pressionado na posi��o: ");
    if (state == GLUT_UP)
        printf("Liberado na posi��o: ");
    printf("(%d, %d)\n", x,y);
}

// **************************************************
// Fun��o chamada quando o mouse anda sobre a janele
// e N�O H� bot�o pressionado 
// **************************************************
void MouseAndandoNaoPressionado (int x, int y)
{
    printf("Mouse ANDANDO solto na janela. Posi��o: (%d, %d)\n", x,y);
}

// **************************************************
// Fun��o chamada quando o mouse anda sobre a janele
// e H� bot�o pressionado 
// **************************************************
void MouseAndandoPressionado (int x, int y)
{
    printf("Mouse ANDANDO pressionado na janela. Posi��o: (%d, %d)\n", x,y);
}

// **************************************************
// Programa principal
// **************************************************
void main(void)
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // define o tamnaho da janela na tela
    glutInitWindowSize(400,350);
    // posiciona a janela na tela
    glutInitWindowPosition(10,10);
    // define o t�tulo da janela
    glutCreateWindow("Programa Exemplo para controle do mouse");
    // define a rotina de exibi��o dos objetos OpenGL
    glutDisplayFunc(RenderScene);
    
    glutReshapeFunc(ChangeSize);

    // Define as fun��es de MOUSE
 
    // movimento SEM bot�o pressionado
    glutPassiveMotionFunc(MouseAndandoNaoPressionado);

    // movimento COM bot�o pressionado
    glutMotionFunc(MouseAndandoPressionado);

    // Click em um bot�o 
    glutMouseFunc(MouseClick);


    SetupRC();
    glutMainLoop();
}


           
