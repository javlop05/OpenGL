#include "Ficha.h"

Ficha::Ficha(int nDivisiones, GLfloat radio, GLfloat altura, GLuint* tx, int numTx) : ObjetoCompuesto3D(6, new TAfin(), new Color(0, 0, 0)) {
	for (int i = 0; i < 6; i++) {
		this->introduceObjeto(new Quesito(nDivisiones, radio, altura, new TAfin(), new Color(1, 1, 1), tx, numTx));
	}
	GLfloat inc = 3.14f / 0.33f;
	for (int i = 0; i < 6; i++) {
		hijo[i]->translada(new PV3D(0.05f*cos(i*inc), 0, 0.05f*sin(i*inc), 1));
		hijo[i]->rota((GLfloat)i * 60, new PV3D(0, 1, 0, 0));
	}
}