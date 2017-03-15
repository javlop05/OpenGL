#include "Autopista.h"

Autopista::Autopista(GLuint* tx, int numTx) : ObjetoCompuesto3D(2, new TAfin(), new Color(0, 0, 0)) {
	Tablero* tablero1 = new Tablero(70, 1, 7, new Color(0.2, 0.2, 0.2), tx, numTx);
	tablero1->translada(new PV3D(0, 0.25, 0, 0));
	tablero1->escala(new PV3D(1, 0.5, 1, 0));
	introduceObjeto(tablero1);

	Tablero* tablero2 = new Tablero(70, 1, 7, new Color(0.2, 0.2, 0.2), tx, numTx);
	tablero2->translada(new PV3D(0, 0.25, 10, 0));
	tablero2->escala(new PV3D(1, 0.5, 1, 0));
	introduceObjeto(tablero2);
}