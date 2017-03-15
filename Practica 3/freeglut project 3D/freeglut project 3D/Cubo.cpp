#include "Cubo.h"

Cubo::Cubo(bool armazon, bool normales, TAfin *mT, Color* c, GLuint* tx, int numTx) 
	: Malla(numVertices, vertice, numNormales, normal, numCaras, cara, normales, armazon, mT, c, tx, numTx){
	this->vertice = new PV3D*[8];
	this->normal = new PV3D*[6];
	this->cara = new Cara*[6];
	this->numVertices = 8;
	this->numNormales = 6;
	this->numCaras = 6;

	vertice[0] = new PV3D(0.5, 0.5, 0.5, 1); //A
	vertice[1] = new PV3D(0.5, 0.5, -0.5, 1); //B
	vertice[2] = new PV3D(-0.5, 0.5, -0.5, 1); //C
	vertice[3] = new PV3D(-0.5, 0.5, 0.5, 1); //D
	vertice[4] = new PV3D(0.5, -0.5, 0.5, 1); //E
	vertice[5] = new PV3D(0.5, -0.5, -0.5, 1); //F
	vertice[6] = new PV3D(-0.5, -0.5, -0.5, 1); //G
	vertice[7] = new PV3D(-0.5, -0.5, 0.5, 1); //H

	/*
	normal[0] = new PV3D(0.0f, 1.0f, 0.0f, 0); //NORMAL CARA ARRIBA
	normal[1] = new PV3D(0.0f, -1.0f, 0.0f, 0); //NORMAL CARA ABAJO
	normal[2] = new PV3D(0.0f, 0.0f, 1.0f, 0); //NORMAL CARA FRONTAL
	normal[3] = new PV3D(0.0f, 0.0f, -1.0f, 0); //NORMAL CARA TRASERA
	normal[4] = new PV3D(1.0f, 0.0f, 0.0f, 0); //NORMAL CARA DERECHA
	normal[5] = new PV3D(-1.0f, 0.0f, 0.0f, 0); //NORMAL CARA IZQUIERDA
	*/

	// El indice de los vertices se da en sentido antihorario

	VerticeNormal** arrayVN_ARRIBA = new VerticeNormal*[4];
	arrayVN_ARRIBA[0] = new VerticeNormal(0, 0);
	arrayVN_ARRIBA[1] = new VerticeNormal(1, 0);
	arrayVN_ARRIBA[2] = new VerticeNormal(2, 0);
	arrayVN_ARRIBA[3] = new VerticeNormal(3, 0);

	VerticeNormal** arrayVN_ABAJO = new VerticeNormal*[4];
	arrayVN_ABAJO[0] = new VerticeNormal(7, 1);
	arrayVN_ABAJO[1] = new VerticeNormal(6, 1);
	arrayVN_ABAJO[2] = new VerticeNormal(5, 1);
	arrayVN_ABAJO[3] = new VerticeNormal(4, 1);

	VerticeNormal** arrayVN_FRONTAL = new VerticeNormal*[4];
	arrayVN_FRONTAL[0] = new VerticeNormal(0, 2);
	arrayVN_FRONTAL[1] = new VerticeNormal(3, 2);
	arrayVN_FRONTAL[2] = new VerticeNormal(7, 2);
	arrayVN_FRONTAL[3] = new VerticeNormal(4, 2);

	VerticeNormal** arrayVN_TRASERA = new VerticeNormal*[4];
	arrayVN_TRASERA[0] = new VerticeNormal(1, 3);
	arrayVN_TRASERA[1] = new VerticeNormal(5, 3);
	arrayVN_TRASERA[2] = new VerticeNormal(6, 3);
	arrayVN_TRASERA[3] = new VerticeNormal(2, 3);

	VerticeNormal** arrayVN_DERECHA = new VerticeNormal*[4];
	arrayVN_DERECHA[0] = new VerticeNormal(0, 4);
	arrayVN_DERECHA[1] = new VerticeNormal(4, 4);
	arrayVN_DERECHA[2] = new VerticeNormal(5, 4);
	arrayVN_DERECHA[3] = new VerticeNormal(1, 4);

	VerticeNormal** arrayVN_IZQUIERDA = new VerticeNormal*[4];
	arrayVN_IZQUIERDA[0] = new VerticeNormal(2, 5);
	arrayVN_IZQUIERDA[1] = new VerticeNormal(6, 5);
	arrayVN_IZQUIERDA[2] = new VerticeNormal(7, 5);
	arrayVN_IZQUIERDA[3] = new VerticeNormal(3, 5);

	cara[0] = new Cara(4, arrayVN_ARRIBA);
	cara[1] = new Cara(4, arrayVN_ABAJO);
	cara[2] = new Cara(4, arrayVN_FRONTAL);
	cara[3] = new Cara(4, arrayVN_TRASERA);
	cara[4] = new Cara(4, arrayVN_DERECHA);
	cara[5] = new Cara(4, arrayVN_IZQUIERDA);

	normal[0] = CalculoVectorNormalPorNewell(cara[0]); //NORMAL CARA ARRIBA
	normal[1] = CalculoVectorNormalPorNewell(cara[1]); //NORMAL CARA ABAJO
	normal[2] = CalculoVectorNormalPorNewell(cara[2]); //NORMAL CARA FRONTAL
	normal[3] = CalculoVectorNormalPorNewell(cara[3]); //NORMAL CARA TRASERA
	normal[4] = CalculoVectorNormalPorNewell(cara[4]); //NORMAL CARA DERECHA
	normal[5] = CalculoVectorNormalPorNewell(cara[5]);//NORMAL CARA IZQUIERDA
}