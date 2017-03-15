#include "Quesito.h"

Quesito::Quesito(int nDivisiones, float radio, float altura) : Malla(numVertices, vertice, numNormales, normal, numCaras, cara){
	this->nDivisiones = nDivisiones;
	this->altura = altura;
	this->radio = radio;

	this->ptsPerfil = 2; //número de puntos en el perfil original
	this->perfil = new PV3D*[ptsPerfil]; //perfil original en el plano XY

	perfil[0] = new PV3D(radio, 0.0f, 0.0f, 1); //A
	perfil[1] = new PV3D(radio, altura, 0.0f, 1); //B

	this->nRotaciones = this->nDivisiones-1; //número de rotaciones
	//Tamaños de los arrays
	this->numVertices = nRotaciones*ptsPerfil + 4; //nDivisiones*ptsPerfil + 2
	this->numCaras = nRotaciones*(ptsPerfil - 1) + 3; 
	this->numNormales = numCaras; //1 normal por cara

	//Creación de los arrays
	this->vertice = new PV3D*[numVertices];
	this->normal = new PV3D*[numNormales];
	this->cara = new Cara*[numCaras];

	for (int j = 0; j < this->ptsPerfil; j++)
		vertice[j] = perfil[j]->clona();

	//Vertices de la malla
	for (int i = 1; i < this->nDivisiones; i++){ //generar el perfil i-ésimo
		double theta = M_PI/180 *(i * 60 / (double)nRotaciones);
		double c = cos(theta);
		double s = sin(theta);
		//R_y es la matriz de rotación sobre el eje Y
		for (int j = 0; j< this->ptsPerfil; j++) {
			int indice = i*this->ptsPerfil + j;
			//Transformar el punto j-ésimo del perfil original
			double x = c*perfil[j]->getX() + s*perfil[j]->getZ();
			double z = -s*perfil[j]->getX() + c*perfil[j]->getZ();
			PV3D* p = new PV3D(x, perfil[j]->getY(), z, 1);
			vertice[indice] = p;
		} //for
	} //for

	vertice[nRotaciones*ptsPerfil] = new PV3D(0.0f, 0.0f, 0.0f, 1);
	vertice[nRotaciones*ptsPerfil + 1] = new PV3D(0.0f, altura, 0.0f, 1);

	//Construcción de las caras
	int indiceCara = 0;
	for (int i = 0; i < this->nRotaciones; i++){ //unir el perfil i-ésimo con el (i+1)%n-ésimo
		for (int j = 0; j<ptsPerfil - 1; j++) { //esquina inferior-izquierda de una cara
			//indiceCara = i*(m-1) + j;
			int indice = i*ptsPerfil + j;
			VerticeNormal** vn = new VerticeNormal*[4];
			vn[0] = new VerticeNormal(indice, indiceCara);
			vn[1] = new VerticeNormal((indice + ptsPerfil) % (numVertices), indiceCara);
			vn[2] = new VerticeNormal((indice + 1 + ptsPerfil) % (numVertices), indiceCara);
			vn[3] = new VerticeNormal(indice + 1, indiceCara);
			cara[indiceCara] = new Cara(4, vn);

			PV3D* v = CalculoVectorNormalPorNewell(cara[indiceCara]); //Newell
			normal[indiceCara] = v;

			indiceCara++;
		} //for
	} //for

	// Contruccion de cara lateral frontal
	VerticeNormal** vn1 = new VerticeNormal*[4];
	vn1[0] = new VerticeNormal(0, indiceCara);
	vn1[1] = new VerticeNormal(1, indiceCara);
	vn1[2] = new VerticeNormal(nRotaciones*ptsPerfil + 1, indiceCara);
	vn1[3] = new VerticeNormal(nRotaciones*ptsPerfil, indiceCara);
	cara[indiceCara] = new Cara(4, vn1);

	PV3D* v1 = CalculoVectorNormalPorNewell(cara[indiceCara]); //Newell
	normal[indiceCara] = v1;

	indiceCara++;

	// Contruccion de cara lateral trasera
	VerticeNormal** vn2 = new VerticeNormal*[4];
	vn2[0] = new VerticeNormal(nRotaciones*ptsPerfil - 2, indiceCara);
	vn2[1] = new VerticeNormal(nRotaciones*ptsPerfil, indiceCara);
	vn2[2] = new VerticeNormal(nRotaciones*ptsPerfil + 1, indiceCara);
	vn2[3] = new VerticeNormal(nRotaciones*ptsPerfil - 1, indiceCara);
	cara[indiceCara] = new Cara(4, vn2);

	PV3D* v2 = CalculoVectorNormalPorNewell(cara[indiceCara]); //Newell
	normal[indiceCara] = v2;

	indiceCara++;

	// Contruccion de cara lateral superior
	VerticeNormal** vn3 = new VerticeNormal*[nDivisiones + 1]; // nDivisiones = nRotaciones + 1
	vn3[0] = new VerticeNormal(nRotaciones*ptsPerfil + 1, indiceCara);

	int i = 1;
	for (int cont = 1; cont < nDivisiones + 1; cont++) {
		vn3[cont] = new VerticeNormal(i, indiceCara);
		i += 2;
	}

	cara[indiceCara] = new Cara(nDivisiones + 1, vn3);

	PV3D* v3 = CalculoVectorNormalPorNewell(cara[indiceCara]); //Newell
	normal[indiceCara] = v3;
}

void Quesito::dibuja(bool armazon){
	for (int i = 0; i< this->numCaras; i++) {
		glLineWidth(1.0);
		if (armazon) glBegin(GL_LINE_LOOP);
		else glBegin(GL_POLYGON);
		for (int j = 0; j < cara[i]->getNumVertices(); j++) {
			int iN = cara[i]->getIndiceNormalK(j);
			int iV = cara[i]->getIndiceVerticeK(j);
			glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());
			//Si hubiera coordenadas de textura, aquí se suministrarían
			//las coordenadas de textura del vértice j con glTexCoor2f(…);
			glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
		}
		glEnd();
	}
}