#ifndef PENTAGRAMA_H
#define PENTAGRAMA_H

#include "PV2D.h"
#include "Lapiz.h"

class Pentagrama {
private:
	GLdouble dir;
	GLdouble lado; //medida del lado del pentagono en el que esta inscrito

public:
	Pentagrama::Pentagrama(GLdouble dir, GLdouble lado);
	void Pentagrama::dibuja(Lapiz *lapiz);
};

#endif