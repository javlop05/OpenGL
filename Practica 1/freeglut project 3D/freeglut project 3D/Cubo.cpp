#include "Cubo.h"

Cubo::Cubo() : Malla(numVertices, vertice, numNormales, normal, numCaras, cara){
	vertice = new PV3D*[8];
	normal = new PV3D*[6];
	cara = new Cara*[6];
	numVertices = 8;
	numNormales = 6;
	numCaras = 6;

	vertice[0] = new PV3D(5.0f, 5.0f, 5.0f, 1); //A
	vertice[1] = new PV3D(5.0f, 5.0f, -5.0f, 1); //B
	vertice[2] = new PV3D(-5.0f, 5.0f, -5.0f, 1); //C
	vertice[3] = new PV3D(-5.0f, 5.0f, 5.0f, 1); //D
	vertice[4] = new PV3D(5.0f, -5.0f, 5.0f, 1); //E
	vertice[5] = new PV3D(5.0f, -5.0f, -5.0f, 1); //F
	vertice[6] = new PV3D(-5.0f, -5.0f, -5.0f, 1); //G
	vertice[7] = new PV3D(-5.0f, -5.0f, 5.0f, 1); //H

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

void Cubo::dibuja(bool armazon){
	GLfloat R = 0.0, G = 1.0, B = 0.0;
	GLfloat temp;
	for (int i = 0; i< this->numCaras; i++) {
		glLineWidth(1.0);
		if (armazon) glBegin(GL_LINE_LOOP);
		else glBegin(GL_POLYGON);
		for (int j = 0; j < cara[i]->getNumVertices(); j++) {
			glColor3f(R, G, B);
			int iN = cara[i]->getIndiceNormalK(j);
			int iV = cara[i]->getIndiceVerticeK(j);
			glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());
			//Si hubiera coordenadas de textura, aquí se suministrarían
			//las coordenadas de textura del vértice j con glTexCoor2f(…);
			glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
			temp = R;
			R = G;
			G = B;
			B = temp;
		}
		glEnd();
	}
}