#include "Objeto3D.h"

Objeto3D::Objeto3D(TAfin* mT, Color* c) {
	this->mT = mT;
	this->c = c;
}

void Objeto3D::translada(PV3D* v) {
	this->mT->traslada(v);
}

void Objeto3D::rota(GLfloat angulo, PV3D* v) {
	this->mT->rota(angulo, v);
}

void Objeto3D::escala(PV3D* v) {
	this->mT->escala(v);
}
