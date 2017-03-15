#include "VerticeNormal.h"

VerticeNormal::VerticeNormal(int i, int v) {
	this->indiceVertice = i;
	this->verticeNormal = v;
}

int VerticeNormal::getIndiceVertice() {
	return this->indiceVertice;
}

int VerticeNormal::getVerticeNormal() {
	return this->verticeNormal;
}


