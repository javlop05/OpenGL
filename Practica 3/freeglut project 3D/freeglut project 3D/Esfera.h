#ifndef ESFERA_H
#define ESFERA_H

#include "ObjetoCuadrico.h"

class Esfera : public ObjetoCuadrico {
private:
	//Specifies the radius of the sphere.
	GLdouble radio;
	//Specifies the number of subdivisions around the z axis(similar to lines of longitude).
	GLint slices;
	//Specifies the number of subdivisions along the z axis(similar to lines of latitude).
	GLint stacks;
public:
	Esfera::Esfera(GLdouble radio, GLint slices, GLint stacks, TAfin* mT, Color* c);
	void Esfera::dibuja();
};

#endif