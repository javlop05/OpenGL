#include "Volante.h"

Volante::Volante(GLuint* tx, int numTx) : ObjetoCompuesto3D(3, new TAfin(), new Color(0, 0, 0)) {
	// Compuesto por dos toros y un cubo
	Cubo* c = new Cubo(false, false, new TAfin(), new Color(0.2f, 0.2f, 0.2f), tx, numTx);
	c->translada(new PV3D(0, 0, 0, 0));
	c->escala(new PV3D(1, 4, 5, 0));
	introduceObjeto(c);
	
	Toro* t1 = new Toro(0.3, 1, 20, 20, new TAfin(), new Color(0.2f, 0.2f, 0.2f));
	t1->translada(new PV3D(0, 0, 2, 0));
	t1->rota(90, new PV3D(0, 1, 0, 0));
	t1->escala(new PV3D(1.5, 1.5, 1.5, 0));
	introduceObjeto(t1);
	Toro* t2 = new Toro(0.3, 1, 20, 20, new TAfin(), new Color(0.2f, 0.2f, 0.2f));
	t2->translada(new PV3D(0, 0, -2, 0));
	t2->rota(90, new PV3D(0, 1, 0, 0));
	t2->escala(new PV3D(1.5, 1.5, 1.5, 0));
	introduceObjeto(t2);
}
