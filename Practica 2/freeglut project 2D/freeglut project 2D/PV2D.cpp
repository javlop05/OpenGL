#include "PV2D.h"
#include <cmath>

PV2D::PV2D(GLfloat x, GLfloat y, int pv) {
	this->x = x;
	this->y = y;
	this->pv = pv;
}

PV2D* PV2D::normaliza() {
	// Suma de los cuadrados, raíz cuadrada
	GLfloat modulo = sqrt(pow(this->x, 2) + pow(this->y, 2));

	return new PV2D(this->x / modulo, this->y / modulo, 0);
}

PV2D* PV2D::clona() {
	return new PV2D(this->x, this->y, this->pv);
}

GLfloat PV2D::productoEscalar(PV2D* v) {
	return (this->x * v->x + this->y * v->y);
}

int PV2D::getPV() {
	return this->pv;
}

void PV2D::setX(GLfloat x) {
	this->x = x;
}

void PV2D::setY(GLfloat y) {
	this->y = y;
}

GLfloat PV2D::getX() {
	return this->x;
}

GLfloat PV2D::getY() {
	return this->y;
}
