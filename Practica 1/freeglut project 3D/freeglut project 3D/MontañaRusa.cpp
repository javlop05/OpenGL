#include "MontañaRusa.h"

PV3D* transformaVertice(PV3D* v, GLfloat t);

MontañaRusa::MontañaRusa(int NP, int NQ) : Malla(numVertices, vertice, numNormales, normal, numCaras, cara) {
	this->NP = NP;
	this->NQ = NQ;
	this->perfil = new PV3D*[NP];
	this->r = 1;

	this->numVertices = NQ*NP;
	this->numCaras = NQ*NP;
	this->numNormales = numCaras;

	// Creación de los arrays
	this->vertice = new PV3D*[numVertices];
	this->normal = new PV3D*[numNormales];
	this->cara = new Cara*[numCaras];

	// Construccion del perfil original
	double inc = 2 * M_PI / NP;
	for (int i = 0; i < NP; i++) {
		perfil[i] = new PV3D((GLfloat)(r*cos(2 * M_PI - i*inc)), (GLfloat)(r*sin(2 * M_PI - i*inc)), 0.0f, 1);
	}

	// Construccion de los vertices

	GLfloat incr = (GLfloat)(2 * M_PI / NQ);

	for (int i = 0; i < NQ; i++) {
		for (int j = 0; j < NP; j++) {
			GLfloat t = incr * i;
			vertice[j + i * NP] = transformaVertice(perfil[j], t);
		}
	}

	//construimos las caras
	int indiceCara = 0;
	for (int i = 0; i < NQ; i++) {
		for (int j = 0; j < NP; j++) {
			int indice = j + i * NP;
			VerticeNormal** vn = new VerticeNormal*[4];
			vn[0] = new VerticeNormal(indice, indiceCara);
			vn[1] = new VerticeNormal((indice + NP) % (numVertices), indiceCara);
			vn[2] = new VerticeNormal((indice + 1 + NP) % (numVertices), indiceCara);
			vn[3] = new VerticeNormal((indice + 1) % numVertices, indiceCara);
			cara[indiceCara] = new Cara(4, vn);

			PV3D* v = CalculoVectorNormalPorNewell(cara[indiceCara]); //Newell
			normal[indiceCara] = v;

			indiceCara++;
		}
	}
}

void MontañaRusa::dibuja(bool armazon){
	for (int i = 0; i< this->numCaras; i++) {
		glLineWidth(1.0);
		if (armazon) glBegin(GL_LINE_LOOP);
		else glBegin(GL_POLYGON);
		for (int j = 0; j < cara[i]->getNumVertices(); j++) {
			int iN = cara[i]->getIndiceNormalK(j);
			int iV = cara[i]->getIndiceVerticeK(j);
			glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());
			//Si hubiera coordenadas de textura, aquí se suministrarían
			//las coordenadas de textura del vértice j con glTexCoor2f(…);
			glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
		}
		glEnd();
	}
}

//curva dada
PV3D* curva(GLfloat t) {
	return new PV3D(3 * cos(t), 3 * sin(2 * t), 3 * sin(t), 0);
}

PV3D* der1curva(GLfloat t) {
	return new PV3D(-3 * sin(t), 6 * cos(2 * t), 3 * cos(t), 0);
}

PV3D* der2curva(GLfloat t) {
	return new PV3D(-3 * cos(t), -12 * sin(2 * t), -3 * sin(t), 0);
}

PV3D* calculaT(GLfloat t) {
	//C'(t)
	return der1curva(t)->normaliza();
}

PV3D* calculaB(GLfloat t) {
	//C'(t) x C''(t)
	return (der1curva(t)->productoVectorial(der2curva(t)))->normaliza();
}

PV3D* calculaN(GLfloat t) {
	//B(t) x T(t) , que ya esta normalizado
	return calculaB(t)->productoVectorial(calculaT(t));
}


//Calcula la matriz con un valor t
PV3D* transformaVertice(PV3D* v, GLfloat t) {

	GLfloat m[16];

	PV3D* N = calculaN(t);
	m[0] = N->getX();
	m[1] = N->getY();
	m[2] = N->getZ();
	m[3] = 0;

	PV3D* B = calculaB(t);
	m[4] = B->getX();
	m[5] = B->getY();
	m[6] = B->getZ();
	m[7] = 0;

	PV3D* T = calculaT(t);
	m[8] = T->getX();
	m[9] = T->getY();
	m[10] = T->getZ();
	m[11] = 0;

	PV3D* C = curva(t);
	m[12] = C->getX();
	m[13] = C->getY();
	m[14] = C->getZ();
	m[15] = 1;

	GLfloat x = v->getX();
	GLfloat y = v->getY();
	GLfloat z = v->getY();

	//aplicamos la matriz de transformacion al perfil
	GLfloat newx = m[0] * x + m[4] * y + m[8] * z + m[12] * 1;
	GLfloat newy = m[1] * x + m[5] * y + m[9] * z + m[13] * 1;
	GLfloat newz = m[2] * x + m[6] * y + m[10] * z + m[14] * 1;

	return new PV3D(newx, newy, newz, 1);
}