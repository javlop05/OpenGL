#ifndef TABLERO_H
#define TABLERO_H

#include "ObjetoCompuesto3D.h"
#include "Cubo.h"

class Tablero : public ObjetoCompuesto3D{
private:
	int cAlto;
	int cAncho;
	int cLargo;
public:
	Tablero::Tablero(int cLargo, int cAlto, int cAncho, Color* c, GLuint* tx, int numTx);
};

#endif