#ifndef ARCO_H
#define ARCO_H

#include "PV2D.h"
#include "Lapiz.h"

const int NUMLADOSARCO = 40;

class Arco {
private:
	PV2D* centro;
	GLdouble radio;
	GLdouble angInicio;
	GLdouble angulo;
public:
	Arco::Arco(PV2D* centro, GLdouble radio, GLdouble angInicio, GLdouble angulo);
	void Arco::dibuja(Lapiz *lapiz);
};

#endif