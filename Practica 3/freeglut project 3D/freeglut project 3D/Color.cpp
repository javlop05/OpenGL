#include "Color.h"

Color::Color(GLfloat R, GLfloat G, GLfloat B) {
	this->R = R;
	this->G = G;
	this->B = B;
}

GLfloat Color::getR(){
	return this->R;
}

GLfloat Color::getG(){
	return this->G;
}

GLfloat Color::getB(){
	return this->B;
}