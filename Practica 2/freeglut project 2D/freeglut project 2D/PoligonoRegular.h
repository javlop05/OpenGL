#ifndef POLIGONOREGULAR_H
#define POLIGONOREGULAR_H

#include "PV2D.h"
#include "Lapiz.h"

class PoligonoRegular {
private:
	PV2D* init;
	GLdouble dir;
	GLdouble lado; //medida del lado del pentagono en el que esta inscrito
	int numLados;

public:
	PoligonoRegular::PoligonoRegular(PV2D* init, GLdouble dir, GLdouble lado, int numLados);
	void PoligonoRegular::dibuja(Lapiz *lapiz);
};

#endif