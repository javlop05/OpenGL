#include "PoligonoRegular.h"

const GLdouble PI = 3.14159265358979323846;

PoligonoRegular::PoligonoRegular(PV2D* init, GLdouble dir, GLdouble lado, int numLados) {
	this->init = init;
	this->dir = dir;
	this->lado = lado;
	this->numLados = numLados;
}

void PoligonoRegular::dibuja(Lapiz *lapiz) {
	GLdouble alfa = 2 * PI / this->numLados;
	GLdouble beta = (PI - alfa) / 2;

	lapiz->moveTo(init, false);
	lapiz->turnTo(dir);

	for (int i = 0; i < this->numLados; i++) {
		lapiz->forward(this->lado, true);
		lapiz->turn(alfa);
	}

}