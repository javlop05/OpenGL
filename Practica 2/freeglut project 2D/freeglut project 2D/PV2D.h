#ifndef PV2D_H
#define PV2D_H
#include <GL/freeglut.h>

class PV2D {
private:
	GLfloat x, y;
	int pv;
public:
	PV2D::PV2D(GLfloat x, GLfloat y, int pv);
	PV2D* PV2D::normaliza();
	PV2D* PV2D::clona();
	GLfloat PV2D::productoEscalar(PV2D* v);
	PV2D* PV2D::productoVectorial(PV2D* v);
	int PV2D::getPV();
	void PV2D::setX(GLfloat x);
	void PV2D::setY(GLfloat y);
	GLfloat PV2D::getX();
	GLfloat PV2D::getY();
};

#endif