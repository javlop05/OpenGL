#ifndef CAMARA_H
#define CAMARA_H

#include "PV3D.h"
#define _USE_MATH_DEFINES
#include <cmath>

class Camara {
private:
	PV3D *eye;
	PV3D *look;
	PV3D* up;
	PV3D* u;
	PV3D* v;
	PV3D* n;
public:
	Camara::Camara(PV3D *eye, PV3D *look, PV3D*up);
	void Camara::actualizarVectoresCamara();
	void Camara::cambiarCamara(GLfloat x, GLfloat y, GLfloat z);
	void Camara::recorridoEje(int x, int y, int z);
	void Camara::rotaX();
	void Camara::rotaY();
	void Camara::rotaZ();
	void Camara::roll(bool sentido);
	void Camara::yaw(bool sentido);
	void Camara::pitch(bool sentido);
	PV3D* Camara::getEye();
	void Camara::setEye(PV3D* eye);
	PV3D* Camara::getLook();
	void Camara::setLook(PV3D* look);
	PV3D* Camara::getUp();
	void Camara::setUp(PV3D* up);
	PV3D* Camara::getU();
	void Camara::setU(PV3D* u);
	PV3D* Camara::getV();
	void Camara::setV(PV3D* v);
	PV3D* Camara::getN();
	void Camara::setN(PV3D* n);
	void Camara::moverCamara(PV3D* v, GLfloat angulo);
};


#endif 
