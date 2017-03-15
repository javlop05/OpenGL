#ifndef OBJETOCUADRICO_H
#define OBJETOCUADRICO_H

#include "Objeto3D.h"

class ObjetoCuadrico : public Objeto3D {
public:
	ObjetoCuadrico::ObjetoCuadrico(TAfin* mT, Color* c);
	virtual void ObjetoCuadrico::dibuja() = 0;
};

#endif