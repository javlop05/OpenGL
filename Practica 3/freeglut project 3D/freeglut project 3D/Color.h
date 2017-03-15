#ifndef COLOR_H
#define COLOR_H

#include <GL/freeglut.h>

class Color{
private:
	GLfloat R;
	GLfloat G;
	GLfloat B;
public:
	Color::Color(GLfloat R, GLfloat G, GLfloat B);
	GLfloat Color::getR();
	GLfloat Color::getG();
	GLfloat Color::getB();
};

#endif