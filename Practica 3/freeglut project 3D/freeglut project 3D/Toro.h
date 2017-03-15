#ifndef TORO_H
#define TORO_H

#include "ObjetoCuadrico.h"
#include "Cubo.h"
#include <GL/freeglut.h>

class Toro : public ObjetoCuadrico{
private:
	GLdouble innerRadius;
	GLdouble outerRadius;
	GLint nsides;
	GLint rings;
	/*
	innerRadius
	Inner radius of the torus.
	outerRadius
	Outer radius of the torus.
	nsides
	Number of sides for each radial section.
	rings
	Number of radial divisions for the torus.
	*/
public:
	Toro::Toro(GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings, TAfin* mT, Color* c);
	void Toro::dibuja();
};

#endif