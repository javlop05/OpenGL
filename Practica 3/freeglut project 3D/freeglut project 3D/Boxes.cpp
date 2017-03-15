#include "Boxes.h"

Boxes::Boxes(GLuint* tx, int numTx) : ObjetoCompuesto3D(4, new TAfin(), new Color(0, 0, 0)) {
	Tablero* tablero1 = new Tablero(20, 1, 12, new Color(0.5, 0.0, 0.0), tx, numTx);
	tablero1->translada(new PV3D(-10.0f, 7.0f, -16.0f, 0));
	tablero1->escala(new PV3D(1, 0.5, 1, 0));
	introduceObjeto(tablero1);

	Tablero* tablero2 = new Tablero(20, 7, 1, new Color(0.5, 0.5, 0.5), tx, numTx);
	tablero2->translada(new PV3D(-10.0f, 0.25, -5.0f, 0));
	tablero2->escala(new PV3D(1, 1, 0.5, 0));
	introduceObjeto(tablero2);

	Tablero* tablero3 = new Tablero(20, 7, 1, new Color(0.5, 0.5, 0.5), tx, numTx);
	tablero3->translada(new PV3D(-10.0f, 0.25f, -16.0f, 0));
	tablero3->escala(new PV3D(1, 1, 0.5, 0));
	introduceObjeto(tablero3);

	Tablero* puerta = new Tablero(1, 7, 11, new Color(0.3, 0.1, 0.0), tx, numTx);
	puerta->translada(new PV3D(10.0f, 0.75f, -15.5f, 0));
	puerta->escala(new PV3D(0.5, 1, 1, 0));
	introduceObjeto(puerta);
	this->topeSubir = 0;
}

void Boxes::moverPuerta(char direccion){
	switch (direccion){
	case 'u':
		if (this->topeSubir < 12){
			this->hijo[3]->translada(new PV3D(0.0, 0.5, 0.0, 0));
			this->topeSubir++;
		}
		break;
	case 'd':
		if (this->topeSubir > 0){
			this->hijo[3]->translada(new PV3D(0.0, -0.5, 0.0, 0));
			this->topeSubir--;
		}
		break;
	}
}