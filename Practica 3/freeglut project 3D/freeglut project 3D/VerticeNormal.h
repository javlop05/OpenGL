#ifndef VERTICENORMAL_H
#define VERTICENORMAL_H

class VerticeNormal {
private:
	int indiceVertice;
	int verticeNormal;

public:
	VerticeNormal::VerticeNormal(int i, int v);
	int VerticeNormal::getIndiceVertice();
	int VerticeNormal::getVerticeNormal();
	
};

#endif