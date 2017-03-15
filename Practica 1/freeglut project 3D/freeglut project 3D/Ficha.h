#ifndef FICHA_H
#define FICHA_H
#include "Malla.h"
#define _USE_MATH_DEFINES
#include <cmath>

class Ficha: public Malla {
private:
	int numQuesitos;
public:
	Ficha::Ficha(int nDivisiones, float radio, float altura);
	void Ficha::dibuja(bool armazon);
};

#endif