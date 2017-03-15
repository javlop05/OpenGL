#ifndef CILINDRO_H
#define CILINDRO_H
#include "ObjetoCuadrico.h"

class Cilindro : public ObjetoCuadrico {
protected:
	//Specifies the radius of the cylinder at z = 0.
	GLdouble radioInf;
	//Specifies the radius of the cylinder.
	GLdouble radioSup;
	//Specifies the height of the cylinder.
	GLdouble altura;
	//Specifies the number of subdivisions around the z axis.
	GLint slices;
	//Specifies the number of subdivisions along the z axis.
	GLint stacks;

public:
	Cilindro::Cilindro(GLdouble base, GLdouble top, 
		GLdouble height, GLint slices, GLint stacks, TAfin* mT, Color* c);
	void Cilindro::dibuja();
};

#endif