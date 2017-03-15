#include "PV3D.h"
#include <cmath>

PV3D::PV3D(GLfloat x, GLfloat y, GLfloat z, int pv) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->pv = pv;
}

PV3D* PV3D:: normaliza() {
	// Suma de los cuadrados, raíz cuadrada
	GLfloat modulo = sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));

	return new PV3D(this->x/modulo, this->y/modulo, this->z/modulo, 0);
}

PV3D* PV3D::clona() {
	return new PV3D(this->x, this->y, this->z, this->pv);
}

GLfloat PV3D::productoEscalar(PV3D* v) {
	return (this->x * v->x + this->y * v->y + this->z * v->z);
}

PV3D* PV3D::productoVectorial(PV3D* v) {
	GLfloat i, j, k;
	i = this->y * v->z - this->z * v->y;
	j = this->z * v->x - this->x * v->z;
	k = this->x * v->y - this->y * v->x;
	return new PV3D(i, j, k, 0);
}

int PV3D::getPV() {
	return this->pv;
}

void PV3D::setX(GLfloat x) {
	this->x = x;
}

void PV3D::setY(GLfloat y) {
	this->y = y;
}

void PV3D::setZ(GLfloat z) {
	this->z = z;
}

GLfloat PV3D::getX() {
	return this->x;
}

GLfloat PV3D::getY() {
	return this->y;
}

GLfloat PV3D::getZ() {
	return this->z;
}
