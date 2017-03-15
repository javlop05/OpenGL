#ifndef VOLANTE_H
#define VOLANTE_H

#include "ObjetoCompuesto3D.h"
#include "Cubo.h"
#include "Toro.h"

class Volante : public ObjetoCompuesto3D{
public:
	Volante::Volante(GLuint* tx, int numTx);
};

#endif