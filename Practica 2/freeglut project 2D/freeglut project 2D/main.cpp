#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
//#include <GL/glut.h>
#include "Lapiz.h"
#include "RectanguloAureo.h"
#include "Arco.h"
#include "PoligonoRegular.h"
#include "Pentagrama.h"
#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
using namespace std;

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
int WIDTH = 500, HEIGHT = 250;

// Scene visible area size
GLdouble xLeft = 0.0, xRight = 500.0, yBot = 0.0, yTop = 250.0;

// Scene variables
//GLdouble xTriangle = 100.0, yTriangle = 100.0;
//GLdouble triangleWidth = 100.0, triangleHeight = 50.0;

const GLdouble NUMAUREO = ((1 + sqrt(5)) / 2);

enum centro {puntoMedio, ojoDeDios};

bool pentagrama = true;
int numPentagramas = 1;

Lapiz *lapiz;
int numRectangulos = 1; 
bool baldosas = false;
int nCol = 2;
centro centroZoom = ojoDeDios;
const GLdouble ANCHURA = 200 * NUMAUREO;
const GLdouble ALTURA = 200;

const GLdouble LADO = 200;

enum cuadrados {izquierda, arriba, derecha, abajo};

void intitGL(){

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);

	glPointSize(4.0);
	glLineWidth(2.0);

	lapiz = new Lapiz();

	// Viewport
	glViewport(0, 0, WIDTH, HEIGHT);

	// Model transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Scene Visible Area
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xLeft, xRight, yBot, yTop);
}

void escenaRectanguloAureo() {
	GLdouble anchura = ANCHURA;
	GLdouble altura = ALTURA;
	glBegin(GL_POINTS);
	glColor3f(0.0, 1.0, 0.0);
	// Coordenadas del ojo de dios
	GLfloat ox = GLfloat(anchura*anchura / (2 * anchura - altura));
	GLfloat oy = GLfloat(altura*(anchura - altura) / (2 * anchura - altura));
	glVertex2f(ox, oy);
	glVertex2f(GLfloat(anchura / 2), GLfloat(altura / 2));
	glEnd();

	PV2D* init = new PV2D(0, 0, 1);
	GLdouble dir = 0;
	RectanguloAureo *r;
	PV2D* centroArco;
	Arco *arco;
	cuadrados c = izquierda;
	for (int i = 0; i < numRectangulos; i++) {
		if (c == izquierda) {
			//Para que no se dibuje arco al principio
			if (i > 0) {
				glColor3f(0.0, 0.0, 1.0);
				centroArco = new PV2D(GLfloat(init->getX() + anchura), init->getY(), 1);
				arco = new Arco(centroArco, anchura, 3 * M_PI / 2, -M_PI / 2);
				arco->dibuja(lapiz);
			}
			glColor3f(1.0, 0.0, 0.0);
			r = new RectanguloAureo(init, dir, anchura, altura);
			r->dibuja(lapiz);
			init = new PV2D((GLfloat)(init->getX() + altura), init->getY(), 1);
			anchura -= altura;
			c = arriba;
		}
		else if (c == arriba) {
			glColor3f(0.0, 0.0, 1.0);
			centroArco = init->clona();
			arco = new Arco(centroArco, altura, M_PI, -M_PI / 2);
			arco->dibuja(lapiz);
			lapiz->turnTo(0);
			glColor3f(1.0, 0.0, 0.0);
			r = new RectanguloAureo(init, dir, anchura, altura);
			r->dibuja(lapiz);
			//init no cambia
			altura -= anchura;
			c = derecha;
		}
		else if (c == derecha) {
			glColor3f(0.0, 0.0, 1.0);
			centroArco = new PV2D(init->getX(), GLfloat(init->getY() + altura), 1);
			arco = new Arco(centroArco, anchura, M_PI / 2, -M_PI / 2);
			arco->dibuja(lapiz);
			lapiz->turnTo(0);
			glColor3f(1.0, 0.0, 0.0);
			r = new RectanguloAureo(init, dir, anchura, altura);
			r->dibuja(lapiz);
			//init no cambia
			anchura -= altura;
			c = abajo;
		}
		// c = abajo
		else {
			glColor3f(0.0, 0.0, 1.0);
			centroArco = new PV2D(GLfloat(init->getX() + anchura), GLfloat(init->getY() + altura), 1);
			arco = new Arco(centroArco, altura, 0, -M_PI / 2);
			arco->dibuja(lapiz);
			glColor3f(1.0, 0.0, 0.0);
			r = new RectanguloAureo(init, dir, anchura, altura);
			r->dibuja(lapiz);
			init = new PV2D(init->getX(), GLfloat(init->getY() + anchura), 1);
			altura -= anchura;
			c = izquierda;
		}
	}
}

void escenaPentagrama() {
	PV2D* init = new PV2D(0, 0, 1);
	GLdouble lado = LADO;
	GLdouble diagonal = LADO*NUMAUREO;

	glBegin(GL_POINTS);
	glColor3f(0.0, 1.0, 0.0);
	
	GLfloat ox = GLfloat(LADO / 2);
	GLfloat oy = GLfloat((tan(54 * M_PI / 180))*(LADO / 2));
	glVertex2f(ox, oy);
	glEnd();

	PoligonoRegular *p = new PoligonoRegular(init, 0, lado, 5); //5 es el numLados
	p->dibuja(lapiz);

	PV2D* initPentagrama = init->clona();
	GLdouble dir;

	for (int i = 0; i < numPentagramas; i++) {

		if (i % 2 == 0) dir = 36 * M_PI / 180;
		else dir = 72 * M_PI / 180;

		Pentagrama *pentagrama = new Pentagrama(dir, lado);
		pentagrama->dibuja(lapiz);

		/*	NUMAUREO*lado = tamDiagonal */
		lado = NUMAUREO*lado - 2 * (NUMAUREO*lado - lado);
		diagonal = lado*NUMAUREO;

		/*El pentagrama siempre se empieza a dibujar desde 
			la esquina inferior izquierda del pentagono*/
		if (i % 2 == 1) lapiz->turnTo(108 * M_PI / 180);
		lapiz->forward(diagonal, false);
	}
}

void drawScene() {
	if (pentagrama) escenaPentagrama();
	else escenaRectanguloAureo();
}

void desembaldosar(){
	glViewport(0, 0, WIDTH, HEIGHT);
	drawScene();
}

void embaldosar(int nCol){
	GLdouble SVAratio = (xRight - xLeft) / (yTop - yBot);
	GLdouble w = (GLdouble)WIDTH / (GLdouble)nCol;
	//La altura de cada puerto se calcula proporcionalmente
	GLdouble h = w / SVAratio;
	for (GLint c = 0; c<nCol; c++){
		GLdouble currentH = 0;
		while ((currentH + h) <= HEIGHT){
			glViewport((GLint)(c*w), (GLint)currentH, (GLint)w, (GLint)h);
			drawScene(); //dibujar la escena
			currentH += h;
		}//while
	}//for
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);

	if (baldosas) embaldosar(nCol); //modo baldosas
	else drawScene();

	glEnd();
	glFlush();
	glutSwapBuffers();
}

void zoomProgresivo(char zoom){
	GLdouble fIncr = 0.01;
	if (zoom == 't'){
		fIncr = -fIncr;
	}

	GLdouble centroX;
	GLdouble centroY;
	if (pentagrama) {
		centroX = LADO / 2;
		centroY = tan(54 * M_PI / 180)*(LADO / 2);
	}
	else {

		if (centroZoom == ojoDeDios) {
			centroX = ANCHURA*ANCHURA / (2 * ANCHURA - ALTURA);
			centroY = (ALTURA*(ANCHURA - ALTURA) / (2 * ANCHURA - ALTURA));
		}
		else {
			centroX = ANCHURA / 2;
			centroY = ALTURA / 2;
		}
	}

	GLdouble fAux = 1 + fIncr;
	GLdouble anchoNew = (xRight - xLeft) / fAux;
	GLdouble altoNew = (yTop - yBot) / fAux;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(centroX - anchoNew / 2.0, centroX + anchoNew / 2.0,
		centroY - altoNew / 2.0, centroY + altoNew / 2.0);

	xLeft = centroX - anchoNew / 2.0;
	xRight = centroX + anchoNew / 2.0;
	yTop = centroX + altoNew / 2.0;
	yBot = centroX - altoNew / 2.0;

	display(); //glutPostRedisplay(); no funciona!
	Sleep(10);

}

void resize(int newWidth, int newHeight){
	//Resize Viewport
	WIDTH = newWidth;
	HEIGHT = newHeight;
	GLdouble RatioViewPort = (float)WIDTH / (float)HEIGHT;
	glViewport(0, 0, WIDTH, HEIGHT);

	//Resize Scene Visible Area 
	//Se actualiza el área visible de la escena
	//para que su ratio coincida con ratioViewPort
	GLdouble SVAWidth = xRight - xLeft;
	GLdouble SVAHeight = yTop - yBot;
	GLdouble SVARatio = SVAWidth / SVAHeight;
	if (SVARatio >= RatioViewPort) {
		// Increase SVAHeight
		GLdouble newHeight = SVAWidth / RatioViewPort;
		GLdouble yMiddle = (yBot + yTop) / 2.0;
		yTop = yMiddle + newHeight / 2.0;
		yBot = yMiddle - newHeight / 2.0;
	}
	else {
		//Increase SVAWidth
		GLdouble newWidth = SVAHeight*RatioViewPort;
		GLdouble xMiddle = (xLeft + xRight) / 2.0;
		xRight = xMiddle + newWidth / 2.0;
		xLeft = xMiddle - newWidth / 2.0;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xLeft, xRight, yBot, yTop);
}

void key(unsigned char key, int x, int y){

	bool need_redisplay = true;

	switch (key) {
	case 27:  /* Escape key */
		//continue_in_main_loop = false; // (**)
		glutLeaveMainLoop(); //Freeglut's sentence for stopping glut's main loop (*)
		break;

	/* Añadir rectángulo o quitar */
	case 'a': numRectangulos++;  display(); break;
	case 'b': if (numRectangulos > 0) numRectangulos--; display(); break;

	/*Centrar el area visible de la escena en el centro del rectangulo o ojo de dios */
	case 'd': centroZoom = puntoMedio; break;
	case 'c': centroZoom = ojoDeDios; break;

	/* Zoom */
	case 't': zoomProgresivo('t'); break;
	case 'y': zoomProgresivo('y'); break;

	/* Embaldosado */
	case 'f': baldosas = true; display(); break;
	case 'v': baldosas = false; desembaldosar(); break;

	/* Cambiar escena a pentagrama o a rectanguloAureo*/
	case 'p': 
		if (pentagrama) pentagrama = false;
		else pentagrama = true;
		break;

	case 'i': numPentagramas++; break;
	case 'o': if (numPentagramas > 0) numPentagramas--; break;

	default:
		need_redisplay = false;
		break;
	}//switch

	if (need_redisplay)
		glutPostRedisplay();
}

int main(int argc, char *argv[]){
	cout << "Starting console..." << endl;

	int my_window; //my window's identifier

	//Initialization
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(140, 140);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInit(&argc, argv);

	//Window construction
	my_window = glutCreateWindow("Freeglut 2D-project");

	//Callback registration
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutDisplayFunc(display);

	//OpenGL basic setting
	intitGL();


	// Freeglut's main loop can be stopped executing (**)
	//while ( continue_in_main_loop )
	//  glutMainLoopEvent();

	// Classic glut's main loop can be stopped after X-closing the window,
	// using the following freeglut's setting (*)
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	// Classic glut's main loop can be stopped in freeglut using (*)
	glutMainLoop();

	// We would never reach this point using classic glut
	system("PAUSE");

	return 0;
}
