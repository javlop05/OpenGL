#include "Arco.h"

const GLdouble PI = 3.14159265358979323846;
#include <cmath>

Arco::Arco(PV2D* centro, GLdouble radio, GLdouble angInicio, GLdouble angulo) {
	this->centro = centro;
	this->radio = radio;
	this->angInicio = angInicio;
	this->angulo = angulo;
}

void Arco::dibuja(Lapiz *lapiz) {
	lapiz->moveTo(this->centro, false);

	lapiz->turnTo(this->angInicio);

	lapiz->forward(this->radio, false);

	GLdouble alfa = angulo / NUMLADOSARCO; //angulo que abarca cada lado
	GLdouble beta = (PI - alfa) / 2;  //
	GLdouble ganma = PI - beta; //Angulo complementario a beta
	GLdouble l = 2 * radio*cos(beta);

	lapiz->turn(ganma);

	for (int i = 0; i < NUMLADOSARCO; i++) {
		lapiz->forward(l, true);
		lapiz->turn(alfa);
	}
}