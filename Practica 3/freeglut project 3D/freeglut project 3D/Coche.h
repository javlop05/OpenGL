#ifndef COCHE_H
#define COCHE_H

#include "ObjetoCompuesto3D.h"
#include "Ficha.h"
#include "Cubo.h"
#include "Cilindro.h"
#include "Esfera.h"
#include "Volante.h"
#include "Faro.h"

class Coche : public ObjetoCompuesto3D{
private:
	void Coche::construirCarroceria(GLuint* tx);
	void Coche::construirCasco();
	void Coche::construirAlerones(GLuint* tx);
	void Coche::construirRuedas(GLuint* tx);
	void Coche::construirVolante(GLuint* tx);
	void Coche::construirFaros();
	int contadorAngulo; // Oscila entre -30 y 30
	void Coche::rotarRuedas(bool alanteUltimoMov);
public:
	Coche::Coche(GLuint* tx);
	void Coche::moverCoche(char direccion, bool alanteUltimoMov);
};

#endif