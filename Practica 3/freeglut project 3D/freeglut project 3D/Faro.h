#ifndef FARO_H
#define FARO_H

#include "Cilindro.h"

class Faro : public Cilindro {
private:
	bool faroDerecho;
public:
	Faro::Faro(GLdouble radioInf, GLdouble radioSup, GLdouble altura, GLint slices, GLint stacks, bool luzDerecha);
	void Faro::dibuja();
};

#endif