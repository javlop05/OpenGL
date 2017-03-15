#include "Curva.h"

Curva::Curva(GLuint* tx, int numTx, int nTablas) : ObjetoCompuesto3D(nTablas + nTablas/2, new TAfin(), new Color(0, 0, 0)) {
	for (int i = 0; i < nTablas; i++){
		Tablero* curva = new Tablero(3, 1, 7, new Color(0.2, 0.2, 0.2), tx, numTx);
		curva->escala(new PV3D(1, 0.5, 1, 0));
		curva->rota((GLfloat)8.7 * i, new PV3D(0, 1, 0, 0));
		curva->translada(new PV3D(-1, 0, 2, 0));
		
		if (i % 2 == 0){
			Proteccion* proteccion = new Proteccion();
			proteccion->rota((GLfloat)-8*i, new PV3D(0, -1, 0, 0));
			proteccion->translada(new PV3D(2, 2, 12, 0));
			introduceObjeto(proteccion);
		}
		introduceObjeto(curva);
	}
}