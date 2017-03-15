#include "Escena.h"

Escena::Escena(GLuint* tx) : ObjetoCompuesto3D(17, new TAfin(), new Color(0, 0, 0)) { //6

	Cubo* tablero = new Cubo(false, false, new TAfin(), new Color(0, 0.5, 0), tx, 0);
	tablero->translada(new PV3D(0.0f, 0.0f, 6.5f, 0));
	tablero->escala(new PV3D(100, 0.5, 100, 0));
	introduceObjeto(tablero);

	Autopista* autopista = new Autopista(tx, -1);
	autopista->translada(new PV3D(-34.5f, 0.0f, -3.0f, 0));
	introduceObjeto(autopista);

	GLfloat x = 35.0f;
	int contFarolas = 8;
	while (contFarolas > 0) {
		Farola* farola = new Farola();
		farola->translada(new PV3D(x, 0, 5.0f, 0));
		introduceObjeto(farola);
		contFarolas--;
		x -= 10.0f;
	}

	this->coche = new Coche(tx);
	coche->translada(new PV3D(0.0f, 0.5f, 0.0f, 0));
	introduceObjeto(coche);

	Curva* curva1 = new Curva(tx, -1, 23);
	curva1->translada(new PV3D(36.5, 0.25f, 5.0, 0));
	introduceObjeto(curva1);

	Curva* curva2 = new Curva(tx, -1, 23);
	curva2->translada(new PV3D(-36.5f, 0.25f, 5.0f, 0));
	curva2->rota(180, new PV3D(0, 1, 0, 0));
	introduceObjeto(curva2);

	Curva* curvaBoxes1 = new Curva(tx, -1, 12);
	curvaBoxes1->translada(new PV3D(13.0f, 0.25f, -5.0f, 0));
	curvaBoxes1->rota(90, new PV3D(0, 1, 0, 0));
	introduceObjeto(curvaBoxes1);

	Curva* curvaBoxes2 = new Curva(tx, -1, 12);
	curvaBoxes2->translada(new PV3D(-16.0f, 0.25f, -5.0f, 0));
	curvaBoxes2->rota(180, new PV3D(0, 1, 0, 0));
	introduceObjeto(curvaBoxes2);

	Tablero* rectaBoxes = new Tablero(30, 1, 7, new Color(0.2, 0.2, 0.2), tx, -1);
	rectaBoxes->translada(new PV3D(-18.0f, 0.25, -13.0f, 0));
	rectaBoxes->escala(new PV3D(1, 0.5, 1, 0));
	introduceObjeto(rectaBoxes);

	this->boxes = new Boxes(tx, 0);
	introduceObjeto(boxes);
}

void Escena::moverCoche(char direccion, bool alanteUltimoMov) {
	this->coche->moverCoche(direccion, alanteUltimoMov);
}

void Escena::moverPuerta(char direccion){
	this->boxes->moverPuerta(direccion);
}