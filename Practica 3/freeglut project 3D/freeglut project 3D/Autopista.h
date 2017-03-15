#ifndef AUTOPISTA_H
#define AUTOPISTA_H

#include "ObjetoCompuesto3D.h"
#include "Tablero.h"

class Autopista : public ObjetoCompuesto3D{
private:
public:
	Autopista::Autopista(GLuint* tx, int numTx);
};

#endif