#include "Camara.h"
#include <iostream>
using namespace std;

Camara::Camara(PV3D *eye, PV3D *look, PV3D*up) {
	this->eye = eye;
	this->look = look;
	this->up = up;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye->getX(), eye->getY(), eye->getZ(),
		look->getX(), look->getY(), look->getZ(),
		up->getX(), up->getY(), up->getZ());

	actualizarVectoresCamara();
}

void Camara::actualizarVectoresCamara() {
	GLfloat x, y, z;
	x = eye->getX() - look->getX();
	y = eye->getY() - look->getY();
	z = eye->getZ() - look->getZ();
	PV3D* newn = new PV3D(x, y, z, 0);
	this->n = newn->normaliza();

	this->u = (this->up->productoVectorial(this->n))->normaliza();

	this->v = this->n->productoVectorial(this->u);
}

void Camara::recorridoEje(int x, int y, int z) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	eye->setX(eye->getX() + x);
	eye->setY(eye->getY() + y);
	eye->setZ(eye->getZ() + z);

	gluLookAt(eye->getX(), eye->getY(), eye->getZ(),
		look->getX(), look->getY(), look->getZ(),
		up->getX(), up->getY(), up->getZ());
	actualizarVectoresCamara();
}

void Camara::rotaX() {
	GLfloat x, y, z;
	double angulo;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	angulo = (5 * M_PI) / 180;
	x = eye->getX();
	y = GLfloat(cos(angulo)*eye->getY() - sin(angulo)*eye->getZ());
	z = GLfloat(sin(angulo)*eye->getY() + cos(angulo)*eye->getZ());

	eye->setX(x);
	eye->setY(y);
	eye->setZ(z);

	gluLookAt(eye->getX(), eye->getY(), eye->getZ(),
		look->getX(), look->getY(), look->getZ(),
		up->getX(), up->getY(), up->getZ());
	actualizarVectoresCamara();

}

void Camara::rotaY() {
	GLfloat x, y, z;
	double angulo;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	angulo = (5 * M_PI) / 180;
	x = GLfloat(cos(angulo)*eye->getX() + sin(angulo)*eye->getZ());
	y = eye->getY();
	z = GLfloat(-sin(angulo)*eye->getX() + cos(angulo)*eye->getZ());

	eye->setX(x);
	eye->setY(y);
	eye->setZ(z);

	gluLookAt(eye->getX(), eye->getY(), eye->getZ(),
		look->getX(), look->getY(), look->getZ(),
		up->getX(), up->getY(), up->getZ());
	actualizarVectoresCamara();
}

void Camara::rotaZ() {
	GLfloat x, y, z;
	double angulo;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	angulo = (5 * M_PI) / 180;
	x = GLfloat(cos(angulo)*eye->getX() - sin(angulo)*eye->getY());
	y = GLfloat(sin(angulo)*eye->getX() + cos(angulo)*eye->getY());
	z = eye->getZ();

	eye->setX(x);
	eye->setY(y);
	eye->setZ(z);

	gluLookAt(eye->getX(), eye->getY(), eye->getZ(),
		look->getX(), look->getY(), look->getZ(),
		up->getX(), up->getY(), up->getZ());
	actualizarVectoresCamara();
}

void Camara::roll(bool sentido) {
	GLfloat V[16]; // Matriz de vista prima
	double angulo;
	if (sentido) angulo = (5 * M_PI) / 180;
	else angulo = (-5 * M_PI) / 180;
	PV3D* uViejo = this->getU()->clona();
	this->u->setX(GLfloat(cos(angulo)*u->getX() + sin(angulo)*v->getX()));
	this->u->setY(GLfloat(cos(angulo)*u->getY() + sin(angulo)*v->getY()));
	this->u->setZ(GLfloat(cos(angulo)*u->getZ() + sin(angulo)*v->getZ()));

	this->v->setX(GLfloat(-sin(angulo)*uViejo->getX() + cos(angulo)*v->getX()));
	this->v->setY(GLfloat(-sin(angulo)*uViejo->getY() + cos(angulo)*v->getY()));
	this->v->setZ(GLfloat(-sin(angulo)*uViejo->getZ() + cos(angulo)*v->getZ()));

	V[0] = u->getX();
	V[1] = v->getX();
	V[2] = n->getX();
	V[3] = 0;

	V[4] = u->getY();
	V[5] = v->getY();
	V[6] = n->getY();
	V[7] = 0;

	V[8] = u->getZ();
	V[9] = v->getZ();
	V[10] = n->getZ();
	V[11] = 0;

	V[12] = -eye->productoEscalar(u);
	V[13] = -eye->productoEscalar(v);
	V[14] = -eye->productoEscalar(n);
	V[15] = 1;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(V);
}

void Camara::yaw(bool sentido) {
	GLfloat V[16]; // Matriz de vista prima
	double angulo;
	if (sentido) angulo = (0.2 * M_PI) / 180;
	else angulo = (-0.2 * M_PI) / 180;
	PV3D* uViejo = this->getU()->clona();
	this->u->setX(GLfloat(cos(angulo)*u->getX() - sin(angulo)*n->getX()));
	this->u->setY(GLfloat(cos(angulo)*u->getY() - sin(angulo)*n->getY()));
	this->u->setZ(GLfloat(cos(angulo)*u->getZ() - sin(angulo)*n->getZ()));

	this->n->setX(GLfloat(sin(angulo)*uViejo->getX() + cos(angulo)*n->getX()));
	this->n->setY(GLfloat(sin(angulo)*uViejo->getY() + cos(angulo)*n->getY()));
	this->n->setZ(GLfloat(sin(angulo)*uViejo->getZ() + cos(angulo)*n->getZ()));

	V[0] = u->getX();
	V[1] = v->getX();
	V[2] = n->getX();
	V[3] = 0;

	V[4] = u->getY();
	V[5] = v->getY();
	V[6] = n->getY();
	V[7] = 0;

	V[8] = u->getZ();
	V[9] = v->getZ();
	V[10] = n->getZ();
	V[11] = 0;

	V[12] = -eye->productoEscalar(u);
	V[13] = -eye->productoEscalar(v);
	V[14] = -eye->productoEscalar(n);
	V[15] = 1;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(V);

}

void Camara::pitch(bool sentido) {
	GLfloat V[16]; // Matriz de vista prima
	double angulo;
	if (sentido) angulo = (0.2 * M_PI) / 180;
	else angulo = (-0.2 * M_PI) / 180;
	PV3D* vViejo = this->getV()->clona();
	this->v->setX(GLfloat(cos(angulo)*v->getX() + sin(angulo)*n->getX()));
	this->v->setY(GLfloat(cos(angulo)*v->getY() + sin(angulo)*n->getY()));
	this->v->setZ(GLfloat(cos(angulo)*v->getZ() + sin(angulo)*n->getZ()));

	this->n->setX(GLfloat(-sin(angulo)*vViejo->getX() + cos(angulo)*n->getX()));
	this->n->setY(GLfloat(-sin(angulo)*vViejo->getY() + cos(angulo)*n->getY()));
	this->n->setZ(GLfloat(-sin(angulo)*vViejo->getZ() + cos(angulo)*n->getZ()));

	V[0] = u->getX();
	V[1] = v->getX();
	V[2] = n->getX();
	V[3] = 0;

	V[4] = u->getY();
	V[5] = v->getY();
	V[6] = n->getY();
	V[7] = 0;

	V[8] = u->getZ();
	V[9] = v->getZ();
	V[10] = n->getZ();
	V[11] = 0;

	V[12] = -eye->productoEscalar(u);
	V[13] = -eye->productoEscalar(v);
	V[14] = -eye->productoEscalar(n);
	V[15] = 1;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(V);

}

PV3D* Camara::getEye() {
	return this->eye;
}

void Camara::setEye(PV3D* eye) {
	this->eye = eye;
}

PV3D* Camara::getLook() {
	return this->look;
}

void Camara::setLook(PV3D* look) {
	this->look = look;
}

PV3D* Camara::getUp() {
	return this->up;
}

void Camara::setUp(PV3D* up) {
	this->up = up;
}

PV3D* Camara::getU() {
	return this->u;
}

void Camara::setU(PV3D* u) {
	this->u = u;
}

PV3D* Camara::getV() {
	return this->v;
}

void Camara::setV(PV3D* v) {
	this->v = v;
}

PV3D* Camara::getN() {
	return this->n;
}

void Camara::setN(PV3D* n) {
	this->n = n;
}

void Camara::cambiarCamara(GLfloat x, GLfloat y, GLfloat z) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	eye->setX(x);
	eye->setY(y);
	eye->setZ(z);

	if ((x == 0) && (z == 0)) {
		up->setX(1);
		up->setY(0);
		up->setZ(0);
	}
	else {
		up->setX(0);
		up->setY(1);
		up->setZ(0);
	}

	gluLookAt(eye->getX(), eye->getY(), eye->getZ(),
		look->getX(), look->getY(), look->getZ(),
		up->getX(), up->getY(), up->getZ());
	actualizarVectoresCamara();

	// Light0
	glEnable(GL_LIGHT0);
	GLfloat d[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
	GLfloat a[] = { 0.3f, 0.3f, 0.3f, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, a);
	GLfloat p[] = { 25.0, 25.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, p);
}


void Camara::moverCamara(PV3D* vector, GLfloat angulo) {

	GLfloat V[16]; // Matriz de vista prima

	eye->setX(eye->getX() + vector->getX()*sin(angulo * M_PI / 180));
	eye->setY(eye->getY() + vector->getY());
	eye->setZ(eye->getZ() + vector->getZ()*cos(angulo * M_PI / 180));

	V[0] = u->getX();
	V[1] = v->getX();
	V[2] = n->getX();
	V[3] = 0;

	V[4] = u->getY();
	V[5] = v->getY();
	V[6] = n->getY();
	V[7] = 0;

	V[8] = u->getZ();
	V[9] = v->getZ();
	V[10] = n->getZ();
	V[11] = 0;

	V[12] = -eye->productoEscalar(u);
	V[13] = -eye->productoEscalar(v);
	V[14] = -eye->productoEscalar(n);
	V[15] = 1;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(V);
}
