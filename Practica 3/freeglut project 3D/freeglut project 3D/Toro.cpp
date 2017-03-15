#include "Toro.h"
#include <iostream>
using namespace std;

Toro::Toro(GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings, TAfin* mT, Color* c) : ObjetoCuadrico(mT, c) {
	// Compuesto por dos toros y un cubo
	this->innerRadius = innerRadius;
	this->outerRadius = outerRadius;
	this->nsides = nsides;
	this->rings = rings;
}

void Toro::dibuja() {
	glColor3f(c->getR(), c->getG(), c->getB());
	GLfloat m[16];
	this->mT->getMatriz(m);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(m);
	glutSolidTorus(this->innerRadius, this->outerRadius, this->nsides, this->rings);
	glPopMatrix();
}