#ifndef QUESITO_H
#define QUESITO_H
#include "Malla.h"
#define _USE_MATH_DEFINES
#include <cmath>

class Quesito: public Malla{

private:
	int nDivisiones;
	float radio;
	float altura;
	int ptsPerfil;
	PV3D** perfil;
	int nRotaciones;

public:
	Quesito::Quesito(int nQ, float radio, float altura);
	void Quesito::dibuja(bool armazon);
};

#endif