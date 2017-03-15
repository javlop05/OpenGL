#ifndef CUBO_H
#define CUBO_H
#include "Malla.h"

class Cubo : public Malla {
public:
	Cubo::Cubo(bool armazon, bool normales, TAfin* mT, Color* c, GLuint* tx, int numTx);
};

#endif