#ifndef ESCENA_H
#define ESCENA_H

#include "ObjetoCompuesto3D.h"
#include "Autopista.h"
#include "Farola.h"
#include "Ficha.h"
#include "Coche.h"
#include "Proteccion.h"
#include "Curva.h"
#include "Tablero.h"
#include "Volante.h"
#include "Boxes.h"

class Escena :public ObjetoCompuesto3D{
private:
public:
	Coche* coche;
	Boxes* boxes;
	Escena::Escena(GLuint* tx);
	void Escena::moverCoche(char direccion, bool alanteUltimoMov);
	void Escena::moverPuerta(char direccion);
};

#endif