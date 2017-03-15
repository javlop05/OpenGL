#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
//#include <GL/glut.h>
#include "Escena.h"
#include "Camara.h"
#include "TextureLoader.h"

#include <iostream>
using namespace std;

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

Escena* escena;
Camara* camara;

const GLfloat giroCoche = 15;
GLfloat anguloCocheConZ = 270;
bool alanteUltimoMov = true; // A true si fue alante y false hacia atras

bool iluminacionGeneral;
bool farosEncendidos;
bool farola;
bool luzRemota;

GLuint texturas[2];

// Viewport size
int WIDTH = 500, HEIGHT = 500;

// Viewing frustum parameters
GLdouble xRight = 10, xLeft = -xRight, yTop = 10, yBot = -yTop, N = 1, F = 1000;
GLdouble fovy = 10;
GLdouble aspect = 2;

// Camera parameters
GLdouble eyeX = 100.0, eyeY = 100.0, eyeZ = 100.0;
GLdouble lookX = 0.0, lookY = 0.0, lookZ = 0.0;
GLdouble upX = 0, upY = 1, upZ = 0;

//bool armazon = false;
//bool normales = false;
bool baldosas = false;
int nCol = 2;
bool ortogonal = true;

GLfloat rotX = 0, rotY = 0, rotZ = 0;
GLfloat angulo = 0;

void buildSceneObjects() {
	PV3D* eye = new PV3D((GLfloat)eyeX, (GLfloat)eyeY, (GLfloat)eyeZ, 1);
	PV3D* look = new PV3D((GLfloat)lookX, (GLfloat)lookY, (GLfloat)lookZ, 0);
	PV3D* up = new PV3D((GLfloat)upX, (GLfloat)upY, (GLfloat)upZ, 0);
	camara = new Camara(eye, look, up);
	escena = new Escena(texturas);
}

void initGL() {
	glClearColor(0.6f, 0.7f, 0.8f, 1.0);
	glEnable(GL_LIGHTING);

	glEnable(GL_COLOR_MATERIAL);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.1f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	buildSceneObjects();


	iluminacionGeneral = true;
	farosEncendidos = false;
	farola = false;
	luzRemota = false;

	// Camera set up
	/*glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ);*/

	// Frustum set up
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (ortogonal) glOrtho(xLeft, xRight, yBot, yTop, N, F);
	else gluPerspective(fovy, aspect, N, F);

	// Viewport set up
	glViewport(0, 0, WIDTH, HEIGHT);

	// Light0
	glEnable(GL_LIGHT0);
	GLfloat d[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
	GLfloat a[] = { 0.3f, 0.3f, 0.3f, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, a);
	GLfloat p[] = { 25.0f, 25.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, p);
	GLfloat amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

	//Texturas
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, texturas);
	//Leer en la variable texture, el archivo que contiene la imagen
	//usando la clase lectora
	unsigned char * texture1;
	unsigned int width1;
	unsigned int height1;

	texture1 = loadBMPRaw("texturas/metal.bmp", width1, height1, true);

	glBindTexture(GL_TEXTURE_2D, texturas[0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Envolturas
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtrado de texturas. GL LINEAR toma los 4 téxeles más cercanos
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// Filtrado de texturas
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1,
		height1, 0, GL_RGB, GL_UNSIGNED_BYTE,
		texture1);
}

void drawScene(){
	// Drawing axes
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(20, 0, 0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 20, 0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 20);
	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotatef(angulo, rotX, rotY, rotZ);

	escena->dibuja();
	
	glPopMatrix();
}

void desembaldosar(){
	glViewport(0, 0, WIDTH, HEIGHT);
	drawScene();
}

void embaldosar(int nCol){
	int numVista = 0;
	GLdouble SVAratio = (xRight - xLeft) / (yTop - yBot);
	GLdouble w = (GLdouble)WIDTH / (GLdouble)nCol;
	//La altura de cada puerto se calcula proporcionalmente
	GLdouble h = w / SVAratio;
	for (GLint c = 0; c < nCol; c++){
		GLdouble currentH = 0;
		while ((currentH + h) <= HEIGHT){
			glViewport((GLint)(c*w), (GLint)currentH, (GLint)w, (GLint)h);
			// Meter un enumerado o booleano para ortogonal/perspectiva y con ifs dibujar lo que le toque
			// Hay que ir cambiando las distintas vistas			
			switch (numVista){
			case 0: camara->cambiarCamara(100, 0, 0); break;
			case 1: camara->cambiarCamara(0, 0, 100); break;
			case 2: camara->cambiarCamara(0, 100, 0); break;
			case 3: camara->cambiarCamara(100, 100, 100); break;
			}
			drawScene(); //dibujar la escena
			currentH += h;
			numVista++;
		}//while
	}//for
}

void lucesEscena() {
	if (iluminacionGeneral) {
		glEnable(GL_LIGHT0);
		GLfloat amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
	}
	else {
		glDisable(GL_LIGHT0);
		GLfloat amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

	}

	if (farosEncendidos) {
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
	}
	else {
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
	}

	if (farola) {
		glEnable(GL_LIGHT3);
		GLfloat d[] = { 1.0, 1.0, 1.0, 1.0 };
		glLightfv(GL_LIGHT3, GL_DIFFUSE, d);
		GLfloat v[] = {5.0, 10.0, 5.0, 1.0 };
		glLightfv(GL_LIGHT3, GL_POSITION, v);
	}
	else {
		glDisable(GL_LIGHT3);
	}

	if (luzRemota) {
		glEnable(GL_LIGHT4);
		GLfloat d[] = { 1.0, 1.0, 1.0, 1.0 };
		glLightfv(GL_LIGHT4, GL_DIFFUSE, d);
		GLfloat v[] = { 20.0, 20.0, 0.0, 1.0 };
		glLightfv(GL_LIGHT4, GL_POSITION, v);
	}
	else {
		glDisable(GL_LIGHT4);
	}
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	lucesEscena();

	if (baldosas) embaldosar(nCol); //modo baldosas
	else drawScene();

	glFlush();
	glutSwapBuffers();
}

void zoomProgresivo(char zoom){
	GLdouble fIncr = 0.05;
	if (zoom == 't'){
		fIncr = -fIncr;
	}
	GLdouble centroX = (xRight + xLeft) / 2;
	GLdouble centroY = (yTop + yBot) / 2;
	GLdouble fAux = 1 + fIncr;
	GLdouble anchoNew = (xRight - xLeft) / fAux;
	GLdouble altoNew = (yTop - yBot) / fAux;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ortogonal) glOrtho(centroX - anchoNew / 2.0, centroX + anchoNew / 2.0,
		centroY - altoNew / 2.0, centroY + altoNew / 2.0, N, F);
	else {
		fovy /= fAux;
		gluPerspective(fovy, aspect, N, F);
	}

	xLeft = centroX - anchoNew / 2.0;
	xRight = centroX + anchoNew / 2.0;
	yTop = centroX + altoNew / 2.0;
	yBot = centroX - altoNew / 2.0;

	display(); //glutPostRedisplay(); no funciona!
	Sleep(20);

}

void cambiarProyeccion() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ortogonal) glOrtho(xLeft, xRight, yBot, yTop, N, F);
	else gluPerspective(fovy, aspect, N, F);
}

void resize(int newWidth, int newHeight) {
	WIDTH = newWidth;
	HEIGHT = newHeight;
	GLdouble RatioViewPort = (float)WIDTH / (float)HEIGHT;
	glViewport(0, 0, WIDTH, HEIGHT);

	GLdouble SVAWidth = xRight - xLeft;
	GLdouble SVAHeight = yTop - yBot;
	GLdouble SVARatio = SVAWidth / SVAHeight;
	if (SVARatio >= RatioViewPort) {
		GLdouble newHeight = SVAWidth / RatioViewPort;
		GLdouble yMiddle = (yBot + yTop) / 2.0;
		yTop = yMiddle + newHeight / 2.0;
		yBot = yMiddle - newHeight / 2.0;
	}
	else {
		GLdouble newWidth = SVAHeight*RatioViewPort;
		GLdouble xMiddle = (xLeft + xRight) / 2.0;
		xRight = xMiddle + newWidth / 2.0;
		xLeft = xMiddle - newWidth / 2.0;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (ortogonal) glOrtho(xLeft, xRight, yBot, yTop, N, F);
	else gluPerspective(fovy, aspect, N, F);
}

void calcularGiroCamara(bool dir) { //true derecha y false izquierda
	if (dir) anguloCocheConZ -= giroCoche;
	else anguloCocheConZ += giroCoche;
	if (anguloCocheConZ >= 360) anguloCocheConZ -= 360;
	if (anguloCocheConZ < 0) anguloCocheConZ += 360;
}

void moverCamara() {
	if (alanteUltimoMov) camara->moverCamara(new PV3D(1, 0, 1, 0), anguloCocheConZ);
	else camara->moverCamara(new PV3D(-1, 0, -1, 0), anguloCocheConZ);
}

void key(unsigned char key, int x, int y){
	bool need_redisplay = true;
	switch (key) {
	case 27:  /* Escape key */
		//continue_in_main_loop = false; // (**)
		//Freeglut's sentence for stopping glut's main loop (*)
		glutLeaveMainLoop();
		break;
		//Rota X
	case 'w': angulo += 5; rotX = 1.0; rotY = 0.0; rotZ = 0.0; display(); break;
	case 's': angulo -= 5; rotX = 1.0; rotY = 0.0; rotZ = 0.0; display(); break;

		//Rota Y
	case 'a': angulo -= 5; rotX = 0.0; rotY = 1.0; rotZ = 0.0; display(); break;
	case 'd': angulo += 5; rotX = 0.0; rotY = 1.0; rotZ = 0.0; display(); break;

	//Movimientos del coche
	case 'i': 
		alanteUltimoMov = true;
		escena->moverCoche('f', alanteUltimoMov); //front
		moverCamara();
		break; 
	case 'j': 
		escena->moverCoche('l', alanteUltimoMov); //left
		calcularGiroCamara(false);
		moverCamara();
		break; 
	case 'l': 
		escena->moverCoche('r', alanteUltimoMov); //right
		calcularGiroCamara(true);
		moverCamara();
		break; 
	case 'k': 
		alanteUltimoMov = false;
		escena->moverCoche('b', alanteUltimoMov); //back
		moverCamara();
		break; 

	case '.':
		escena->moverPuerta('u');
		break;
	case '-':
		escena->moverPuerta('d');
		break;

		//Embaldosado
	case 'p': baldosas = true; display(); break;
	case 'o': baldosas = false; desembaldosar(); break;

		//Translacion de la figura
		// Eje X
	case 'z': glTranslated(-1, 0, 0); display(); break;
	case 'x': glTranslated(1, 0, 0); display(); break;
		//Eje Y
	case 'c': glTranslated(0, -1, 0); display(); break;
	case 'v': glTranslated(0, 1, 0); display(); break;
		//Eje Z
	case 'b': glTranslated(0, 0, -1); display(); break;
	case 'n': glTranslated(0, 0, 1); display(); break;

		//Zoom

		// Acercar
	case 'y': zoomProgresivo('y'); break;
		// Alejar
	case 't': zoomProgresivo('t'); break;

		//Iluminacion
	case '1': iluminacionGeneral = !iluminacionGeneral; break;
		//Faros del coche
	case '2': farosEncendidos = !farosEncendidos; break;
		//Luz de la farola
	case '3': farola = !farola;  break;
	case '4': luzRemota = !luzRemota;  break;

		// TECLAS DE LA CAMARA
	case 'E': camara->recorridoEje(3, 0, 0); break;
	case 'R': camara->recorridoEje(-3, 0, 0); break;
	case 'F': camara->recorridoEje(0, 3, 0); break;
	case 'G': camara->recorridoEje(0, -3, 0); break;
	case 'V': camara->recorridoEje(0, 0, 3); break;
	case 'B': camara->recorridoEje(0, 0, -3); break;

	case 'X': camara->rotaX(); break;
	case 'Y': camara->rotaY(); break;
	case 'Z': camara->rotaZ(); break;

		/*
		TRUE y FALSE para cambiar los sentidos
		El movimiento pitch es una rotación con respecto al eje U
		El movimiento yaw es una rotación con respecto al eje V
		El movimiento roll es una rotación con respecto al eje N
		*/
	case 'U': camara->roll(true); break;
	case 'I': camara->roll(false); break;
	case 'J': camara->yaw(true); break;
	case 'K': camara->yaw(false); break;
	case 'N': camara->pitch(true); break;
	case 'M': camara->pitch(false); break;

		/*
		W = vista cenital
		A = vista lateral
		S = vista frontal
		D = vista esquina
		*/
	case 'W': camara->cambiarCamara(0, 100, 0); break;
	case 'A': camara->cambiarCamara(0, 0, 100); break;
	case 'S': camara->cambiarCamara(100, 0, 0); break;
	case 'D': camara->cambiarCamara(100, 100, 100); break;

	case 'P':
		if (ortogonal) ortogonal = false;
		else ortogonal = true;
		cambiarProyeccion();
		break;

	default:
		need_redisplay = false;
		break;
	}

	if (need_redisplay)
		glutPostRedisplay();
}

int main(int argc, char *argv[]){
	cout << "Starting console..." << endl;

	int my_window; // my window's identifier

	// Initialization
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(140, 140);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	// Window construction
	my_window = glutCreateWindow("Freeglut 3D-project");

	// Callback registration
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutDisplayFunc(display);

	// OpenGL basic setting
	initGL();

	// Freeglut's main loop can be stopped executing (**)
	// while (continue_in_main_loop) glutMainLoopEvent();

	// Classic glut's main loop can be stopped after X-closing the window,
	// using the following freeglut's setting (*)
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	// Classic glut's main loop can be stopped in freeglut using (*)
	glutMainLoop();

	// We would never reach this point using classic glut
	system("PAUSE");

	return 0;
}
