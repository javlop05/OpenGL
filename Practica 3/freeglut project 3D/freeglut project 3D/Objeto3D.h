#ifndef OBJETO3D_H
#define OBJETO3D_H

#include "TAfin.h"
#include "Color.h"

class Objeto3D{
protected:
	TAfin* mT;
	Color* c;
public:
	Objeto3D::Objeto3D(TAfin* mT, Color* c);
	virtual void Objeto3D::dibuja() = 0;
	void Objeto3D::translada(PV3D* v);
	void Objeto3D::rota(GLfloat angulo, PV3D* v);
	void Objeto3D::escala(PV3D* v);
};

#endif