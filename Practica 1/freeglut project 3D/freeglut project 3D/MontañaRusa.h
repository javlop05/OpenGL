#ifndef MONTANIARUSA_H
#define MONTANIARUSA_H
#include "Malla.h"
#define _USE_MATH_DEFINES
#include <cmath>

class MontaņaRusa : public Malla {
private:
	int NP; //numero de lados del poligono
	int NQ; //numero de rodajas que forman la montaņa
	PV3D** perfil;
	int r;

	PV3D* curva(int t);
	PV3D* der1curva(int t);
	PV3D* der2curva(int t);
	PV3D* calculaT(int t);
	PV3D* calculaB(int t);
	PV3D* calculaN(int t);

public:
	MontaņaRusa::MontaņaRusa(int NP, int NQ);
	void MontaņaRusa::dibuja(bool armazon);
};

#endif