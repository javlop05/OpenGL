#include "Coche.h"

Coche::Coche(GLuint* tx) : ObjetoCompuesto3D(25, new TAfin(), new Color(0, 0, 0)){
	construirCarroceria(tx);
	construirCasco();
	construirAlerones(tx);
	construirRuedas(tx);
	construirFaros();
	construirVolante(tx);
	this->contadorAngulo = 0;
}

void Coche::construirCarroceria(GLuint* tx){
	// CARROCERÍA
	Cubo* carroceriaUno = new Cubo(false, false, new TAfin(), new Color(0.7f, 0.0f, 0.0f), tx, 0);
	carroceriaUno->translada(new PV3D(-0.5f, 1.0f, 0.0f, 0)); // 1 DE ALTURA POR DEFECTO
	carroceriaUno->escala(new PV3D(15.0f, 0.5f, 1.0f, 0));
	introduceObjeto(carroceriaUno);

	Cubo* carroceriaUnoAlto = new Cubo(false, false, new TAfin(), new Color(0.7f, 0.0f, 0.0f), tx, 0);
	carroceriaUnoAlto->translada(new PV3D(0.0f, 1.5f, 0.0f, 0)); // 1.5 DE ALTURA POR DEFECTO
	carroceriaUnoAlto->escala(new PV3D(11.0f, 0.5f, 1.0f, 0));
	introduceObjeto(carroceriaUnoAlto);

	Cubo* carroceriaDos = new Cubo(false, false, new TAfin(), new Color(0.7f, 0.0f, 0.0f), tx, 0);
	carroceriaDos->translada(new PV3D(2.0f, 1.0f, 0.0f, 0));
	carroceriaDos->escala(new PV3D(6.8f, 1.0f, 3.5f, 0));
	introduceObjeto(carroceriaDos);

	Cubo* carroceriaTres = new Cubo(false, false, new TAfin(), new Color(0.7f, 0.0f, 0.0f), tx, 0);
	carroceriaTres->translada(new PV3D(2.0f, 1.0f, 0.0f, 0));
	carroceriaTres->escala(new PV3D(7.5f, 1.0f, 2.0f, 0));
	introduceObjeto(carroceriaTres);

	Cubo* carroceriaCuatro = new Cubo(false, false, new TAfin(), new Color(0.7f, 0.0f, 0.0f), tx, 0); // Parte de arriba del todo
	carroceriaCuatro->translada(new PV3D(2.5f, 2.0f, 0.0f, 0));
	carroceriaCuatro->escala(new PV3D(3.0f, 1.5f, 1.0f, 0));
	introduceObjeto(carroceriaCuatro);

	Cubo* carroceriaCinco = new Cubo(false, false, new TAfin(), new Color(0.2f, 0.2f, 0.2f), tx, 0); // Bajos
	carroceriaCinco->translada(new PV3D(2.0f, 0.4f, 0.0f, 0));
	carroceriaCinco->escala(new PV3D(6.8f, 0.3f, 3.5f, 0));
	introduceObjeto(carroceriaCinco);

	Cubo* carroceriaSeis = new Cubo(false, false, new TAfin(), new Color(0.7f, 0.0f, 0.0f), tx, 0); // Parte de arriba
	carroceriaSeis->translada(new PV3D(3.0f, 2.0f, 0.0f, 0));
	carroceriaSeis->escala(new PV3D(4.0f, 0.5f, 1.0f, 0));
	introduceObjeto(carroceriaSeis);
}

void Coche::construirCasco(){
	// CASCO
	Esfera* casco = new Esfera(0.4, 100, 100, new TAfin(), new Color(0.0f, 0.5f, 1.0f));
	casco->translada(new PV3D(0.8f, 2.0f, 0.0f, 0));
	introduceObjeto(casco);
}

void Coche::construirAlerones(GLuint* tx){

	// ALERON DELANTERO
	Cubo* aleronD = new Cubo(false, false, new TAfin(), new Color(1.0f, 1.0f, 1.0f), tx, -1);
	aleronD->translada(new PV3D(-8.0f, 0.6f, 0.0f, 0));
	aleronD->escala(new PV3D(1.25f, 0.3f, 5.2f, 0));
	introduceObjeto(aleronD);

	Cubo* aleronDLD = new Cubo(false, false, new TAfin(), new Color(0.7f, 0.0f, 0.0f), tx, 0);
	aleronDLD->translada(new PV3D(-8.0f, 0.8f, -2.6f, 0));
	aleronDLD->escala(new PV3D(1.25f, 0.7f, 0.2f, 0));
	introduceObjeto(aleronDLD);

	Cubo* aleronDLI = new Cubo(false, false, new TAfin(), new Color(0.7f, 0.0f, 0.0f), tx, 0);
	aleronDLI->translada(new PV3D(-8.0f, 0.8f, 2.6f, 0));
	aleronDLI->escala(new PV3D(1.25f, 0.7f, 0.2f, 0));
	introduceObjeto(aleronDLI);
	// ALERON TRASERO
	Cubo* aleronI = new Cubo(false, false, new TAfin(), new Color(0.7f, 0.7f, 0.7f), tx, -1);
	aleronI->translada(new PV3D(6.5f, 2.5f, 0.0f, 0));
	aleronI->escala(new PV3D(1.0f, 0.2f, 4.0f, 0));
	introduceObjeto(aleronI);

	Cubo* aleronIBajo = new Cubo(false, false, new TAfin(), new Color(0.1f, 0.1f, 0.1f), tx, -1);
	aleronIBajo->translada(new PV3D(6.5f, 1.2f, 0.0f, 0));
	aleronIBajo->escala(new PV3D(1.0f, 0.2f, 4.0f, 0));
	introduceObjeto(aleronIBajo);

	Cubo* aleronILD = new Cubo(false, false, new TAfin(), new Color(0.7f, 0.0f, 0.0f), tx, 0);
	aleronILD->translada(new PV3D(6.5f, 2.0f, 2.0f, 0));
	aleronILD->escala(new PV3D(1.0f, 1.8f, 0.2f, 0));
	introduceObjeto(aleronILD);

	Cubo* aleronILI = new Cubo(false, false, new TAfin(), new Color(0.7f, 0.0f, 0.0f), tx, 0);
	aleronILI->translada(new PV3D(6.5f, 2.0f, -2.0f, 0));
	aleronILI->escala(new PV3D(1.0f, 1.8f, 0.2f, 0));
	introduceObjeto(aleronILI);
}

void Coche::construirRuedas(GLuint* tx){
	// RUEDAS
	Ficha* rueda1 = new Ficha(10, 5.0f, 1.5f, tx, 0);
	rueda1->translada(new PV3D(-6.0f, 1.0f, -2.0f, 0));
	rueda1->rota(270, new PV3D(1.0f, 0.0f, 0.0f, 0));
	rueda1->escala(new PV3D(0.2f, 0.5f, 0.2f, 0));
	introduceObjeto(rueda1);

	Ficha* rueda2 = new Ficha(10, 5.0f, 1.5f, tx, 0);
	rueda2->translada(new PV3D(-6.0f, 1.0f, 2.0f, 0));
	rueda2->rota(90, new PV3D(1.0f, 0.0f, 0.0f, 0));
	rueda2->escala(new PV3D(0.2f, 0.5f, 0.2f, 0));
	introduceObjeto(rueda2);

	Ficha* rueda3 = new Ficha(10, 5.0f, 1.5f, tx, 0);
	rueda3->translada(new PV3D(4.5f, 1.0f, 2.0f, 0));
	rueda3->rota(90, new PV3D(1.0f, 0.0f, 0.0f, 0));
	rueda3->escala(new PV3D(0.2f, 0.5f, 0.2f, 0));
	introduceObjeto(rueda3);

	Ficha* rueda4 = new Ficha(10, 5.0f, 1.5f, tx, 0);
	rueda4->translada(new PV3D(4.5f, 1.0f, -2.0f, 0));
	rueda4->rota(270, new PV3D(1.0f, 0.0f, 0.0f, 0));
	rueda4->escala(new PV3D(0.2f, 0.5f, 0.2f, 0));
	introduceObjeto(rueda4);

	// EJES DE LAS RUEDAS
	Cubo* ejeUno = new Cubo(false, false, new TAfin(), new Color(0.1f, 0.1f, 0.1f), tx, -1);
	ejeUno->translada(new PV3D(-6.0f, 1.0f, 0.0f, 0));
	ejeUno->escala(new PV3D(0.2f, 0.2f, 4.5f, 0));
	introduceObjeto(ejeUno);

	Cubo* ejeDos = new Cubo(false, false, new TAfin(), new Color(0.1f, 0.1f, 0.1f), tx, -1);
	ejeDos->translada(new PV3D(4.5f, 1.0f, 0.0f, 0));
	ejeDos->escala(new PV3D(0.2f, 0.2f, 4.5f, 0));
	introduceObjeto(ejeDos);
}

void Coche::construirFaros(){
	Faro* faroD = new Faro(0.8, 1, 3, 20, 20, true);
	faroD->translada(new PV3D(-8.3f, 0.6f, -2.1f, 0));
	faroD->rota(270, new PV3D(0, 1, 0, 0));
	faroD->escala(new PV3D(0.5f, 0.25f, 0.20f, 0));
	introduceObjeto(faroD);

	Faro* faroI = new Faro(0.8, 1, 3, 20, 20, false);
	faroI->translada(new PV3D(-8.3f, 0.6f, 2.1f, 0));
	faroI->rota(270, new PV3D(0, 1, 0, 0));
	faroI->escala(new PV3D(0.5f, 0.25f, 0.20f, 0));
	introduceObjeto(faroI);
}

void Coche::construirVolante(GLuint* tx){
	// VOLANTE
	Volante* volante = new Volante(tx, -1);
	volante->translada(new PV3D(-0.5f, 1.9f, 0.0f, 0));
	volante->escala(new PV3D(0.1f, 0.1f, 0.1f, 0));
	introduceObjeto(volante);

	Cubo* soporteVolante = new Cubo(false, false, new TAfin(), new Color(0.1f, 0.1f, 0.1f), tx, -1);
	soporteVolante->translada(new PV3D(-0.7f, 1.7f, 0.0f, 0));
	soporteVolante->escala(new PV3D(0.3f, 0.5f, 0.4f, 0));
	introduceObjeto(soporteVolante);
}

void Coche::moverCoche(char direccion, bool alanteUltimoMov) {
	switch (direccion) {
	case 'f':
		//TRANSLADAR COCHE (AVANZAR)
		this->translada(new PV3D(-1, 0, 0, 0));

		//GIRAR RUEDAS
		rotarRuedas(alanteUltimoMov);

		// Por cada vez que pulses la tecla se intenta enderezar hasta que llegue a 0
		if (this->contadorAngulo > 0){ // Si el volante estaba girado a la derecha
			this->hijo[23]->rota(5, new PV3D(1, 0, 0, 0));
			this->contadorAngulo -= 5;
		} 
		else if (this->contadorAngulo < 0){ // Si el volante estaba girado a la izquierda
			this->hijo[23]->rota(5, new PV3D(-1, 0, 0, 0));
			this->contadorAngulo += 5;
		}

		break;
	case 'r':
		//GIRAR COCHE HACIA LA DERECHA
		this->rota(345, new PV3D(0, 1, 0, 0));

		//TRANSLADAR COCHE
		if (alanteUltimoMov) this->translada(new PV3D(-1, 0, 0, 0));
		else this->translada(new PV3D(1, 0, 0, 0));

		//GIRAR RUEDAS
		rotarRuedas(alanteUltimoMov);

		if (this->contadorAngulo < 30){ // Va girar da igual su ángulo hasta que llegue al tope de la derecha
			this->hijo[23]->rota(5, new PV3D(-1, 0, 0, 0));
			this->contadorAngulo += 5;
		}
			break;
	case 'l':
		//GIRAR COCHE HACIA LA IZQUIERDA
		this->rota(15, new PV3D(0, 1, 0, 0));

		//TRANSLADAR COCHE
		if (alanteUltimoMov) this->translada(new PV3D(-1, 0, 0, 0));
		else this->translada(new PV3D(1, 0, 0, 0));

		//GIRAR RUEDAS
		rotarRuedas(alanteUltimoMov);

		if (this->contadorAngulo > -30){ // Va girar da igual su ángulo hasta que llegue al tope de la izquierda
			this->hijo[23]->rota(5, new PV3D(1, 0, 0, 0));
			this->contadorAngulo -= 5;
		}
		
		break;
	case 'b':
		//TRANSLADAR COCHE (MARCHA ATRÁS)
		this->translada(new PV3D(1, 0, 0, 0));
		//GIRAR RUEDAS
		rotarRuedas(alanteUltimoMov);
		break;
	default:
		break;
	}
}

void Coche::rotarRuedas(bool alanteUltimoMov) {
	if (alanteUltimoMov) {
		this->hijo[15]->rota(45, new PV3D(0, 1, 0, 0));
		this->hijo[16]->rota(-45, new PV3D(0, 1, 0, 0));
		this->hijo[17]->rota(-45, new PV3D(0, 1, 0, 0));
		this->hijo[18]->rota(45, new PV3D(0, 1, 0, 0));
	}
	else {
		this->hijo[15]->rota(-45, new PV3D(0, 1, 0, 0));
		this->hijo[16]->rota(45, new PV3D(0, 1, 0, 0));
		this->hijo[17]->rota(45, new PV3D(0, 1, 0, 0));
		this->hijo[18]->rota(-45, new PV3D(0, 1, 0, 0));
	}
}