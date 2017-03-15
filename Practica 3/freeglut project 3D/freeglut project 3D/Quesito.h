#ifndef QUESITO_H
#define QUESITO_H
#include "Malla.h"
#define _USE_MATH_DEFINES
#include <cmath>

class Quesito: public Malla {

private:
	int nDivisiones;
	GLfloat radio;
	GLfloat altura;
	int ptsPerfil;
	PV3D** perfil;
	int nRotaciones;

public:
	Quesito::Quesito(int nQ, GLfloat radio, GLfloat altura, TAfin* mT, Color* c, GLuint* tx, int numTx);
};

#endif