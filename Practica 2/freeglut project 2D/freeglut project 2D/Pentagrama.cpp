#include "Pentagrama.h"

#include <cmath>

const GLdouble NUMAUREO = ((1 + sqrt(5)) / 2);
const GLdouble PI = 3.14159265358979323846;

Pentagrama::Pentagrama(GLdouble dir, GLdouble lado) {
	this->dir = dir;
	this->lado = lado;
}

void Pentagrama::dibuja(Lapiz *lapiz) {
	lapiz->turnTo(dir);

	GLdouble tamDiagonal = this->lado*NUMAUREO;
	GLdouble angulo = 144 * PI / 180;

	for (int i = 0; i < 5; i++) {
		lapiz->forward(tamDiagonal, true);
		lapiz->turn(angulo);
	}

}