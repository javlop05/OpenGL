#include "Lapiz.h"

#include <cmath>

const GLdouble PI = 3.14159265358979323846;

Lapiz::Lapiz() {
	this->posicion = new PV2D(0, 0, 1);
	this->dir = 0;
}

Lapiz::Lapiz(PV2D* posicion, GLdouble dir) {
	this->posicion = posicion;
	this->dir = dir;
}

PV2D* Lapiz::getPosicion() {
	return this->posicion;
}

void Lapiz::moveTo(PV2D* posicion, bool draw) {
	if (draw) {
		glLineWidth(1.0);
		glBegin(GL_LINES);
		glVertex2d(this->posicion->getX(), this->posicion->getY());
		glVertex2d(posicion->getX(), posicion->getY());
		glEnd();
	}

	this->posicion = posicion;
}

GLdouble Lapiz::getDir() {
	return this->dir;
}

void Lapiz::turnTo(GLdouble a) {
	this->dir = a;
	//Esto limita el rango del angulo entre 0 y 2*PI
	while (this->dir >= (2 * PI)) {
		this->dir -= (2 * PI);
	}
}

void Lapiz::turn(GLdouble a) {
	//Si a > 0 giro a la izquierda
	//Si a < 0 giro a la derecha 
	this->dir += a;
	//Esto limita el rango del angulo entre 0 y 2*PI
	while (this->dir >= (2 * PI)) {
		this->dir -= (2 * PI);
	}

}

void Lapiz::forward(GLdouble dist, bool draw) {

	PV2D* posVieja = this->posicion->clona();
	this->posicion->setX(this->posicion->getX() + dist*cos(dir));
	this->posicion->setY(this->posicion->getY() + dist*sin(dir));

	if (draw) {
		glLineWidth(1.0);
		glBegin(GL_LINES);
		glVertex2d(posVieja->getX(), posVieja->getY());
		glVertex2d(posicion->getX(), posicion->getY());
		glEnd();
	}

	//probar a borrar posVieja
}