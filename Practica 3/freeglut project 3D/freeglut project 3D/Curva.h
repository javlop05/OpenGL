#ifndef CURVA_H
#define CURVA_H

#include "ObjetoCompuesto3D.h"
#include "Tablero.h"
#include "Proteccion.h"

class Curva : public ObjetoCompuesto3D{
public:
	Curva::Curva(GLuint* tx, int numTx, int nTablas);
};

#endif