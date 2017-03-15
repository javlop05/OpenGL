#include "Proteccion.h"

Proteccion::Proteccion() : ObjetoCompuesto3D(5, new TAfin(), new Color(0, 0, 0)) {
	for (int i = 4; i >= 0; i--){
		Color* color;
		Color* granate = new Color(0.7f, 0.0f, 0.0f);
		Color* gris = new Color(0.7f, 0.7f, 0.7f);
		if (i % 2 == 1){
			color = gris;
		}
		else color = granate;

		Cilindro* c1 = new Cilindro(1.5, 1.5, 1, 20, 20, new TAfin(), color);
		c1->rota(90, new PV3D(1, 0, 0, 0));
		c1->translada(new PV3D(0, 0, (GLfloat)i-3, 0)); // Al rotar primero, los ejes ahora son en translada (x, z, y)
		introduceObjeto(c1);
	}
}