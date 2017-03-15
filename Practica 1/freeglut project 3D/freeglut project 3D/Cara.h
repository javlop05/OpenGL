#ifndef CARA_H
#define CARA_H

#include "VerticeNormal.h"

class Cara {
private:
	int numVertices;
	VerticeNormal** arrayVN;

public:
	Cara::Cara(int numV, VerticeNormal** VN);
	int Cara::getNumVertices();
	VerticeNormal** Cara::getVerticeNormal();
	int Cara::getIndiceNormalK(int j);
	int Cara::getIndiceVerticeK(int j);
};

#endif