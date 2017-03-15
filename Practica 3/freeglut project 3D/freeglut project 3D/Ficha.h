#ifndef FICHA_H
#define FICHA_H
#include "ObjetoCompuesto3D.h"
#include "Quesito.h"
#define _USE_MATH_DEFINES
#include <cmath>

class Ficha : public ObjetoCompuesto3D {
public:
	Ficha::Ficha(int nDivisiones, GLfloat radio, GLfloat altura, GLuint* tx, int numTx);
};

#endif