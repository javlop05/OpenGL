#include "Ficha.h"

typedef struct Color {
	GLfloat R;
	GLfloat G;
	GLfloat B;
};

Ficha::Ficha(int nDivisiones, float radio, float altura) : Malla(numVertices, vertice, numNormales, normal, numCaras, cara){

	this->numQuesitos = 6;
	int ptsPerfil = 2;
	int ptsPerfilTotales = numQuesitos*ptsPerfil; //ptos de perfil de cada quesito
	PV3D** perfil = new PV3D*[ptsPerfilTotales]; // en total hay 12 puntos
	perfil[0] = new PV3D(radio, 0.0f, 0.0f, 1); //A
	perfil[1] = new PV3D(radio, altura, 0.0f, 1); //B
	int nRotaciones = nDivisiones - 1; //número de rotaciones
	int numVertPartExtQuesito = (nRotaciones*ptsPerfil + 2);
	int numVerticesQuesito = numVertPartExtQuesito + 2;
	int numCarasQuesito = nRotaciones*(ptsPerfil - 1) + 3;

	//Tamaños de los arrays
	int numVerticesParteExterna = numVertPartExtQuesito * numQuesitos;
	this->numVertices = numVerticesQuesito * numQuesitos; //+2 por cada quesito (6 quesitos)
	this->numCaras = numCarasQuesito * numQuesitos;
	this->numNormales = numCaras; //1 normal por cara

	//Creación de los arrays
	this->vertice = new PV3D*[numVertices];
	this->normal = new PV3D*[numNormales];
	this->cara = new Cara*[numCaras];

	for (int k = 0; k < numQuesitos; k++) {

		// Introducimos en vertices el perfil del quesito actual
		for (int j = 0; j < ptsPerfil; j++)
			vertice[j + k * numVerticesQuesito] = perfil[j + 2 * k]->clona();

		//Vertices de la malla
		for (int i = 1; i < nDivisiones; i++){ //generar el perfil i-ésimo
			double theta = M_PI / 180 * (i * 55 / (double)nRotaciones);
			double c = cos(theta);
			double s = sin(theta);
			//R_y es la matriz de rotación sobre el eje Y
			for (int j = 0; j < ptsPerfil; j++) {
				int indice = i*ptsPerfil + j + k*numVerticesQuesito;
				int indicePerfil = j + 2 * k; //Indice perfil del quesito a construir
				//Transformar el punto j-ésimo del perfil original
				double x = c*perfil[indicePerfil]->getX() + s*perfil[indicePerfil]->getZ();
				double z = -s*perfil[indicePerfil]->getX() + c*perfil[indicePerfil]->getZ();
				PV3D* p = new PV3D(x, perfil[indicePerfil]->getY(), z, 1);
				vertice[indice] = p;
			} //for
		} //for

		//Construimos la punta del quesito
		vertice[numVertPartExtQuesito + k*numVerticesQuesito] = new PV3D(0.0f, 0.0f, 0.0f, 1);
		vertice[numVertPartExtQuesito + 1 + k*numVerticesQuesito] = new PV3D(0.0f, altura, 0.0f, 1);

		//Construcción de las caras externas
		int indiceCara = k * numCarasQuesito;
		for (int i = 0; i < nRotaciones; i++){ //unir el perfil i-ésimo con el (i+1)%n-ésimo
			for (int j = 0; j < ptsPerfil - 1; j++) { //esquina inferior-izquierda de una cara
				//indiceCara = i*(m-1) + j;
				//indice del punto de la esquina inferior izquierda
				int indice = i*ptsPerfil + j + k*numVerticesQuesito;
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
		vn1[0] = new VerticeNormal(k*numVerticesQuesito, indiceCara);
		vn1[1] = new VerticeNormal(1 + k*numVerticesQuesito, indiceCara);
		vn1[2] = new VerticeNormal(numVertPartExtQuesito + 1 + k*numVerticesQuesito, indiceCara);
		vn1[3] = new VerticeNormal(numVertPartExtQuesito + k*numVerticesQuesito, indiceCara);
		cara[indiceCara] = new Cara(4, vn1);

		PV3D* v1 = CalculoVectorNormalPorNewell(cara[indiceCara]); //Newell
		normal[indiceCara] = v1;

		indiceCara++;

		// Contruccion de cara lateral trasera
		VerticeNormal** vn2 = new VerticeNormal*[4];
		vn2[0] = new VerticeNormal(numVertPartExtQuesito + k*numVerticesQuesito - 2, indiceCara);
		vn2[1] = new VerticeNormal(numVertPartExtQuesito + k*numVerticesQuesito, indiceCara);
		vn2[2] = new VerticeNormal(numVertPartExtQuesito + 1 + k*numVerticesQuesito, indiceCara);
		vn2[3] = new VerticeNormal(numVertPartExtQuesito + k*numVerticesQuesito - 1, indiceCara);
		cara[indiceCara] = new Cara(4, vn2);

		PV3D* v2 = CalculoVectorNormalPorNewell(cara[indiceCara]); //Newell
		normal[indiceCara] = v2;

		indiceCara++;

		// Contruccion de cara lateral superior
		VerticeNormal** vn3 = new VerticeNormal*[nDivisiones + 1]; // nDivisiones = nRotaciones + 1
		// Vertice superior de la punta del quesito
		vn3[0] = new VerticeNormal(numVertPartExtQuesito + 1 + k*numVerticesQuesito, indiceCara);

		//Vamos cogiendo los vertices superiores externos del quesito
		int indiceVertParteSuperior = 1 + k * numVerticesQuesito;
		for (int cont = 1; cont < nDivisiones + 1; cont++) {
			vn3[cont] = new VerticeNormal(indiceVertParteSuperior, indiceCara);
			indiceVertParteSuperior += 2;
		}

		cara[indiceCara] = new Cara(nDivisiones + 1, vn3);

		PV3D* v3 = CalculoVectorNormalPorNewell(cara[indiceCara]); //Newell
		normal[indiceCara] = v3;

		// Rotamos el perfil
		if (k < 5) {
			double theta = M_PI / 180 * ((k + 1) * 60);
			double c = cos(theta);
			double s = sin(theta);
			//R_y es la matriz de rotación sobre el eje Y
			for (int j = 0; j < ptsPerfil; j++) {
				//Transformar el punto j-ésimo del perfil original
				double x = c*perfil[j]->getX() + s*perfil[j]->getZ();
				double z = -s*perfil[j]->getX() + c*perfil[j]->getZ();
				PV3D* p = new PV3D(x, perfil[j]->getY(), z, 1);
				perfil[j + 2 * (k+1)] = p;
			}
		}
	}
}

void Ficha::dibuja(bool armazon){
	Color marron = { 0.5, 0.25, 0 };
	Color verde = { 0, 0.5, 0 };
	Color rosa = { 1.0, 0.5, 1.0 };
	Color amarillo = { 1.0, 1.0, 0 };
	Color naranja = { 1.0, 0.5, 0 };
	Color azul = { 0, 0.5, 1.0 };
	
	Color c[6] = { marron, verde, rosa, amarillo, naranja, azul };
	Color color;

	for (int i = 0; i< this->numCaras; i++) {
		glLineWidth(1.0);
		if (armazon) glBegin(GL_LINE_LOOP);
		else glBegin(GL_POLYGON);
		/*Cuando ya acaba de pintar un quesito, es decir, numCarasQuesito = (numCaras / 6)
		hay que cambiar el color para pintar el nuevo quesito de otro color */
		color = c[i / (numCaras / this->numQuesitos)]; //6 = numQuesitos
		glColor3f(color.R, color.G, color.B);
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