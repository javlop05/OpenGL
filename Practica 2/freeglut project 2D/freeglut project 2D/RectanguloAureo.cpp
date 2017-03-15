#include "RectanguloAureo.h"

const GLdouble PI = 3.14159265358979323846;

RectanguloAureo::RectanguloAureo(PV2D* init, GLdouble dir, GLdouble anchura, GLdouble altura) {
	this->init = init;
	this->dir = dir;
	this->anchura = anchura;
	this->altura = altura;
}

void RectanguloAureo::dibuja(Lapiz *lapiz) {
	lapiz->turnTo(dir);

	lapiz->moveTo(init, false);

	lapiz->forward(anchura, true);
	lapiz->turn(PI / 2); // gira 90º

	lapiz->forward(altura, true);
	lapiz->turn(PI / 2); // gira 90º

	lapiz->forward(anchura, true);
	lapiz->turn(PI / 2); // gira 90º

	lapiz->forward(altura, true);
	lapiz->turn(PI / 2); // gira 90º
}