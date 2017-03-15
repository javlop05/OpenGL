#include "Cara.h"

Cara::Cara(int numV, VerticeNormal** VN) {
	this->numVertices = numV;
	this->arrayVN = VN;
}

int Cara::getNumVertices() {
	return this->numVertices;
}

VerticeNormal** Cara::getVerticeNormal() {
	return this->arrayVN;
}

int Cara::getIndiceNormalK(int j) {
	return this->arrayVN[j]->getVerticeNormal();
}

int Cara::getIndiceVerticeK(int j) {
	return this->arrayVN[j]->getIndiceVertice();
}
