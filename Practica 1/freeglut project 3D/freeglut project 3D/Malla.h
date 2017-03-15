#ifndef MALLA_H
#define MALLA_H
#include "PV3D.h"
#include "Cara.h"

class Malla {
protected:
	int numVertices;
	PV3D** vertice;
	int numNormales; //=numCaras, frecuentemente
	PV3D** normal;
	int numCaras;
	Cara** cara;

public:
	Malla::Malla(int nV, PV3D** vertice, int nN, PV3D**normal, int nC, Cara** cara);
	void Malla::dibuja();
	PV3D* Malla::CalculoVectorNormalPorNewell(Cara* c);
	int Malla::getNumVertices();
	PV3D** Malla::getVertices();
	int Malla::getNumNormales();
	PV3D** Malla::getNormal();
	int Malla::getNumCaras();
	Cara** Malla::getCara();
	PV3D* Malla::puntoMedio(Cara* c);
	void Malla::dibujarNormales();
};

#endif