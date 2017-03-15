#include "Esfera.h"

Esfera::Esfera(GLdouble radio, GLint slices, GLint stacks, TAfin* mT, Color* c) : ObjetoCuadrico(mT, c) {
	this->radio = radio;
	this->slices = slices;
	this->stacks = stacks;
}

void Esfera::dibuja() {
	GLUquadricObj* quadratic = gluNewQuadric();
	glColor3f(c->getR(), c->getG(), c->getB());
	GLfloat m[16];
	this->mT->getMatriz(m);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(m);
	gluQuadricDrawStyle(quadratic, GLU_FILL);
	gluSphere(quadratic, this->radio, this->slices, this->stacks);
	glPopMatrix();
	gluDeleteQuadric(quadratic);
}