#include "ObjetoCompuesto3D.h"
#include <iostream>
using namespace std;

ObjetoCompuesto3D::ObjetoCompuesto3D(int numHijos, TAfin* mT, Color* c) : Objeto3D(mT, c) {
	this->numHijos = numHijos;
	this->hijoAct = 0;
	this->hijo = new Objeto3D*[numHijos];
}

void ObjetoCompuesto3D::introduceObjeto(Objeto3D* objeto) {
	if (hijoAct < numHijos) {
		this->hijo[hijoAct] = objeto;
		this->hijoAct++;
	}
}

void ObjetoCompuesto3D::dibuja() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	GLfloat m[16];
	this->mT->getMatriz(m);
	glMultMatrixf(m);
	for (int i = 0; i < this->numHijos; i++) {
		hijo[i]->dibuja();
	}
	glPopMatrix();
}