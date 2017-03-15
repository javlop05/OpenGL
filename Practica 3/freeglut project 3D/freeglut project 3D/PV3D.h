#ifndef PV3D_H
#define PV3D_H
#include <GL/freeglut.h>

class PV3D {
private:
	GLfloat x, y, z;
	int pv;
public:
	PV3D::PV3D(GLfloat x, GLfloat y, GLfloat z, int pv);
	PV3D* PV3D::normaliza();
	PV3D* PV3D::clona();
	GLfloat PV3D::productoEscalar(PV3D* v);
	PV3D* PV3D::productoVectorial(PV3D* v);
	int PV3D::getPV();
	void PV3D::setX(GLfloat x);
	void PV3D::setY(GLfloat y);
	void PV3D::setZ(GLfloat z);
	GLfloat PV3D::getX();
	GLfloat PV3D::getY();
	GLfloat PV3D::getZ();
};

#endif