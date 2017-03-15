#ifndef TAFIN_H
#define TAFIN_H

#include <GL/freeglut.h>

#include "PV3D.h"

class TAfin{
private:
	GLfloat m[16];
public:
	TAfin::TAfin();
	TAfin::TAfin(GLfloat m[16]);
	void TAfin::getMatriz(GLfloat m[16]);
	void TAfin::traslada(PV3D *v);
	void TAfin::escala(PV3D *v);
	void TAfin::rota(GLfloat angulo, PV3D *v);
	void TAfin::postmultiplica(GLfloat *m1);
};

#endif