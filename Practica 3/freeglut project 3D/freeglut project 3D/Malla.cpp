#include "Malla.h"

Malla::Malla(int nV, PV3D** vertice, int nN, PV3D**normal, int nC, Cara** cara, bool normales, bool armazon, TAfin* mT, Color* c, GLuint* tx, int numTx) : Objeto3D(mT, c) {
	this->numVertices = nV;
	this->vertice = vertice;
	this->numNormales = nN;
	this->normal = normal;
	this->numCaras = nC;
	this->cara = cara;
	this->armazon = armazon;
	this->normales = normales;
	this->tx = tx;
	this->numTx = numTx;
}

void Malla::dibuja(){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//Aplicamos su transformacion afin
	GLfloat m[16];
	this->mT->getMatriz(m);
	glMultMatrixf(m);
	//Aplicamos su color
	glColor3f(c->getR(), c->getG(), c->getB());

	for (int i = 0; i< this->numCaras; i++) {
		glLineWidth(1.0);
		if (this->numTx != -1){
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, this->tx[numTx]);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		}
		if (!armazon) glBegin(GL_POLYGON); 
		else glBegin(GL_LINE_LOOP);
		for (int j = 0; j < cara[i]->getNumVertices(); j++) {
			int iN = cara[i]->getIndiceNormalK(j); 
			int iV = cara[i]->getIndiceVerticeK(j);
			glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());
			if (this->numTx != -1 && i == 0)
				switch (j) { // Para orientar las texturas
					case 0: glTexCoord2f(0, 0); break;
					case 1: glTexCoord2f(0, 1); break;
					case 2: glTexCoord2f(1, 1); break;
					case 3: glTexCoord2f(1, 0); break;
				}
			glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
		}
		glEnd();
	}
	
	if (this->normales) dibujarNormales();
	if (this->numTx != 1) glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

PV3D* Malla::CalculoVectorNormalPorNewell(Cara* C) {
	PV3D* n = new PV3D(0, 0, 0, 0);
	PV3D* vertActual;
	PV3D* vertSiguiente;
	GLfloat x = 0, y = 0, z = 0;

	for (int i = 0; i < C->getNumVertices(); i++) {
		vertActual = vertice[C->getIndiceVerticeK(i)];
		vertSiguiente = vertice[C->getIndiceVerticeK((i + 1) % C->getNumVertices())];
		x += (vertActual->getY() - vertSiguiente->getY())*
			(vertActual->getZ() + vertSiguiente->getZ());
		y += (vertActual->getZ() - vertSiguiente->getZ())*
			(vertActual->getX() + vertSiguiente->getX());
		z += (vertActual->getX() - vertSiguiente->getX())*
			(vertActual->getY() + vertSiguiente->getY());
		n->setX(x);
		n->setY(y);
		n->setZ(z);
	}

	return n->normaliza();
}

int Malla::getNumVertices(){
	return this->numVertices;
}

PV3D ** Malla::getVertices(){
	return this->vertice;
}

int Malla::getNumNormales(){
	return this->numNormales;
}

PV3D** Malla::getNormal(){
	return this->normal;
}

int Malla::getNumCaras(){
	return this->numCaras;
}

Cara** Malla::getCara(){
	return this->cara;
}

PV3D* Malla::puntoMedio(Cara* c) {
	GLfloat x = 0, y = 0, z = 0;
	for (int j = 0; j < c->getNumVertices(); j++) {
		int iV = c->getIndiceVerticeK(j);
		x += vertice[iV]->getX();
		y += vertice[iV]->getY();
		z += vertice[iV]->getZ();
	}
	x /= c->getNumVertices();
	y /= c->getNumVertices();
	z /= c->getNumVertices();

	return new PV3D(x, y, z, 1);
}

void Malla::dibujarNormales() {
	PV3D* puntoCentral;
	PV3D* vectorNormal;
	glLineWidth(1.0);
	glBegin(GL_LINES);
	for (int i = 0; i < this->numCaras; i++) {
		puntoCentral = this->puntoMedio(cara[i]);
		vectorNormal = normal[i];
		glVertex3f(puntoCentral->getX(), puntoCentral->getY(), puntoCentral->getZ());
		glVertex3f(puntoCentral->getX() + vectorNormal->getX(),
			puntoCentral->getY() + vectorNormal->getY(),
			puntoCentral->getZ() + vectorNormal->getZ());
	}
	glEnd();
}