#ifndef LAPIZ_H
#define LAPIZ_H

#include "PV2D.h"

class Lapiz {
private:
	PV2D* posicion; //Posicion actual
	GLdouble dir; //Direccion actual
public:
	Lapiz::Lapiz();
	Lapiz::Lapiz(PV2D* posicion, GLdouble dir);
	PV2D* Lapiz::getPosicion();
	void Lapiz::moveTo(PV2D* posicion, bool draw);
	GLdouble Lapiz::getDir();
	void Lapiz::turnTo(GLdouble a);
	void Lapiz::turn(GLdouble a);
	void Lapiz::forward(GLdouble dist, bool draw);
};

#endif