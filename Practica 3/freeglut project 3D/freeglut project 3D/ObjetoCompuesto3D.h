#ifndef OBJETOCOMPUESTO3D_H
#define OBJETOCOMPUESTO3D_H

#include "Objeto3D.h"

class ObjetoCompuesto3D : public Objeto3D {
protected:
	int numHijos;
	int hijoAct;
	Objeto3D** hijo;
public:
	ObjetoCompuesto3D::ObjetoCompuesto3D(int numHijos, TAfin* mT, Color* c);
	void ObjetoCompuesto3D::introduceObjeto(Objeto3D* objeto);
	void ObjetoCompuesto3D::dibuja();
};

#endif