#include "Faro.h"

Faro::Faro(GLdouble radioInf, GLdouble radioSup, GLdouble altura, GLint slices, GLint stacks, bool luzDerecha) 
: Cilindro(radioInf, radioSup, altura, slices, stacks, new TAfin(), new Color(1.0f, 0.7f, 0.0f)) {
	this->faroDerecho = luzDerecha;
}

void Faro::dibuja() {
	GLUquadricObj* quadratic = gluNewQuadric();
	glColor3f(c->getR(), c->getG(), c->getB());
	GLfloat m[16];
	this->mT->getMatriz(m);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(m);
	gluQuadricDrawStyle(quadratic, GLU_FILL);
	gluCylinder(quadratic, this->radioInf, this->radioSup, this->altura, this->slices, this->stacks);
	if (faroDerecho) {
		GLfloat d[] = { 2.0, 2.0, 0.0, 1.0 }; // Color de la luz
		glLightfv(GL_LIGHT1, GL_DIFFUSE, d);
		GLfloat v[] = { 0.0f, 10.0f, -20.0f, 1.0 }; // Posición de la luz
		glLightfv(GL_LIGHT1, GL_POSITION, v);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20.0); // Ángulo con el plano XZ (cuanto más grande el número, más apunta hacia abajo)
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0); // Potencia de la luz
		GLfloat dir[] = { 0.0, 0.0, 1.0 }; // Dirección del foco (apunta hacia el eje -Z)
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir);
	}
	else {
		GLfloat d[] = { 2.0, 2.0, 0.0, 1.0 }; // Color de la luz
		glLightfv(GL_LIGHT2, GL_DIFFUSE, d);
		GLfloat v[] = { 0.0f, 10.0f, -20.0f, 1.0 }; // Posición de la luz
		glLightfv(GL_LIGHT2, GL_POSITION, v);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 20.0); // Ángulo con el plano XZ (cuanto más grande el número, más apunta hacia abajo)
		glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 1.0); // Potencia de la luz
		GLfloat dir[] = { 0.0, 0.0, 1.0 }; // Dirección del foco (apunta hacia el eje -Z)
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir);
	}
	glPopMatrix();
	gluDeleteQuadric(quadratic);
}

