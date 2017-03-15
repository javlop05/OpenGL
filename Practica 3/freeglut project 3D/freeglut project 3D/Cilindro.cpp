#include "Cilindro.h"

Cilindro::Cilindro(GLdouble radioInf, GLdouble radioSup, GLdouble altura, 
	GLint slices, GLint stacks, TAfin* mT, Color* c) : ObjetoCuadrico(mT, c) {
	this->radioInf = radioInf;
	this->radioSup = radioSup;
	this->altura = altura;
	this->slices = slices;
	this->stacks = stacks;
}

void Cilindro::dibuja() {
	GLUquadricObj* quadratic = gluNewQuadric();
	glColor3f(c->getR(), c->getG(), c->getB());
	GLfloat m[16];
	this->mT->getMatriz(m);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(m);
	gluQuadricDrawStyle(quadratic, GLU_FILL);
	gluCylinder(quadratic, this->radioInf, this->radioSup, this->altura, this->slices, this->stacks);
	glPopMatrix();
	gluDeleteQuadric(quadratic);
}