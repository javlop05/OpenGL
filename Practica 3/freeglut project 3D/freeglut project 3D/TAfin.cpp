#include "TAfin.h"

TAfin::TAfin(){
	m[0] = 1; m[4] = 0; m[8] = 0;  m[12] = 0;
	m[1] = 0; m[5] = 1; m[9] = 0;  m[13] = 0;
	m[2] = 0; m[6] = 0; m[10] = 1; m[14] = 0;
	m[3] = 0; m[7] = 0; m[11] = 0; m[15] = 1;
}

TAfin::TAfin(GLfloat m[16]) {
	for (int i = 0; i < 16; i++) {
		this->m[i] = m[i];
	}
}

void TAfin::getMatriz(GLfloat m[16]) {
	for (int i = 0; i < 16; i++) {
		m[i] = this->m[i];
	}
}

void TAfin::traslada(PV3D *v) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(v->getX(), v->getY(), v->getZ());
	GLfloat m1[16];
	//Dejar la matriz de modelado-vista en m1
	//Los 16 datos están enumerados por columnas
	glGetFloatv(GL_MODELVIEW_MATRIX, m1);
	glPopMatrix();
	postmultiplica(m1);
}

void TAfin::escala(PV3D *v) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glScalef(v->getX(), v->getY(), v->getZ());
	GLfloat m1[16];
	//Dejar la matriz de modelado-vista en m1
	//Los 16 datos están enumerados por columnas
	glGetFloatv(GL_MODELVIEW_MATRIX, m1);
	glPopMatrix();
	postmultiplica(m1);
}

void TAfin::rota(GLfloat angulo, PV3D *v) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRotatef(angulo, v->getX(), v->getY(), v->getZ());
	GLfloat m1[16];
	//Dejar la matriz de modelado-vista en m1
	//Los 16 datos están enumerados por columnas
	glGetFloatv(GL_MODELVIEW_MATRIX, m1);
	glPopMatrix();
	postmultiplica(m1);
}

void TAfin::postmultiplica(GLfloat *m1) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//Cargar m como matriz actual del modelado-vista
	glLoadMatrixf(this->m);
	//Post-multiplicar por m1
	glMultMatrixf(m1);
	//Dejar el resultado en m
	glGetFloatv(GL_MODELVIEW_MATRIX, this->m);
	glPopMatrix();
}