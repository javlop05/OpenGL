#ifndef BOXES_H
#define BOXES_H

#include "ObjetoCompuesto3D.h"
#include "Tablero.h"

class Boxes : public ObjetoCompuesto3D{
private:
	int topeSubir;
public:
	Boxes::Boxes(GLuint* tx, int numTx);
	void Boxes::moverPuerta(char direccion);
};

#endif