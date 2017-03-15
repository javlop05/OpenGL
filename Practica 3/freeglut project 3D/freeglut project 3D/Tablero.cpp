#include "Tablero.h"

Tablero::Tablero(int cLargo, int cAlto, int cAncho, Color* c, GLuint* tx, int numTx) : ObjetoCompuesto3D(cAlto*cAncho*cLargo, new TAfin(), c) {
	this->cAlto = cAlto;
	this->cAncho = cAncho;
	this->cLargo = cLargo;

	for (int i = 0; i < cLargo; i++) {
		for (int j = 0; j < cAncho; j++) {
			for (int k = 0; k < cAlto; k++) {
				TAfin *t = new TAfin();
				t->traslada(new PV3D((GLfloat)i, (GLfloat)k, (GLfloat)j, 0));
				Cubo* cubo = new Cubo(false, false, t, c, tx, numTx); //armazon = true y normales = false
				introduceObjeto(cubo);
			}
		}
	}
}