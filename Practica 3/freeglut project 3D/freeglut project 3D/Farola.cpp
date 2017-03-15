#include "Farola.h"

#define M_PI       3.14159265358979323846

Farola::Farola() : ObjetoCompuesto3D(2, new TAfin(), new Color(0,0,0)) {
	TAfin* mPalo = new TAfin();
	mPalo->rota((GLfloat)(270), new PV3D(1, 0, 0, 0));
	Cilindro* palo = new Cilindro(0.2, 0.2, 10, 10, 10, mPalo, new Color(0.5, 0.5, 0.5));
	introduceObjeto(palo);
	TAfin* mBola = new TAfin();
	mBola->traslada(new PV3D(0, 10, 0, 0));
	Esfera* bola = new Esfera(1, 10, 10, mBola, new Color(1.0, 1.0, 0.0));
	introduceObjeto(bola);
}