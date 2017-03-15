#ifndef RECTANGULOAUREO_H
#define RECTANGULOAUREO_H

#include "PV2D.h"
#include "Lapiz.h"

class RectanguloAureo {
private:
	PV2D* init;
	GLdouble dir;
	GLdouble anchura;
	GLdouble altura;
public:
	RectanguloAureo::RectanguloAureo(PV2D* init, GLdouble dir, GLdouble anchura, GLdouble altura);
	void RectanguloAureo::dibuja(Lapiz *lapiz);
};

#endif