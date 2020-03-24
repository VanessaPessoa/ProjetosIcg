#include "Box.h"
#include <SOIL2.h>


GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, BoxSize / 2.f, 0.f, 1.0f };
GLfloat LightPosition2[] = { -BoxSize / 2.f, -BoxSize / 2.f, BoxSize / 2.f, 1.0f };
GLfloat LightPosition3[] = { BoxSize / 2.f, -BoxSize / 2.f, BoxSize / 2.f, 1.0f };
GLfloat LightPosition4[] = { 0.0f, -BoxSize / 2.f, -BoxSize / 2.f, 1.0f };


void loadTex(int i, const char *filename, GLuint* texture) {
	unsigned char* image;
	int width, height;
	image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, texture[i]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void drawRect(GLuint texture) {
	glEnable(GL_TEXTURE_2D);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glBindTexture(GL_TEXTURE_2D, texture);
	const GLfloat x1 = -0.5, x2 = 0.5;
	const GLfloat y1 = -0.5, y2 = 0.5;
	const GLfloat point[4][2] = { { x1,y1 },{ x1,y2 },{ x2,y2 },{ x2,y1 } };
	int dir[4][2] = { { 1,0 },{ 1,1 },{ 0,1 },{ 0,0 } };
	glBegin(GL_QUADS);

	for (int i = 0; i < 4; i++) {
		glTexCoord2iv(dir[i]);
		glVertex2fv(point[i]);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
}

void drawSkybox(GLuint* texture) {
	//Cima
	glPushMatrix();
	glTranslatef(0.0f, (BoxSize / 2.0f) - 400, 0.0f);
	glRotatef(270, 1, 0, 0);
	glScalef(BoxSize, BoxSize, 1);
	drawRect(texture[0]);
	glPopMatrix();

	//Baixo  
	glPushMatrix();
	glTranslatef(0.0f, (-BoxSize / 2.0f) + 400, 0.0f);
	glRotatef(90, 1, 0, 0);

	glScalef(BoxSize, BoxSize, 1);
	drawRect(texture[1]);
	glPopMatrix();

	//Esquerda
	glPushMatrix();
	glTranslatef(BoxSize / 2.0f, 0.0f, 0.0f);
	glRotatef(90, 0, 1, 0);
	glRotatef(180, 0, 0, 1);

	glScalef(BoxSize, BoxSize - 800, 1);
	drawRect(texture[2]);
	glPopMatrix();


	//Direita
	glPushMatrix();
	glTranslatef(-BoxSize / 2.0f, 0.0f, 0.0f);
	glRotatef(270, 0, 1, 0);
	glRotatef(180, 0, 0, 1);

	glScalef(BoxSize, BoxSize - 800, 1);
	drawRect(texture[3]);
	glPopMatrix();


	//Frente
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, BoxSize / 2.0f);
	glRotatef(180, 0, 0, 1);

	glScalef(BoxSize, BoxSize - 800, 1);
	drawRect(texture[4]);
	glPopMatrix();

	//Costas
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -BoxSize / 2.0);
	glRotatef(180, 1, 0, 0);

	glScalef(BoxSize, BoxSize - 800, 1);
	drawRect(texture[5]);
	glPopMatrix();

}

void setupLights() {
	glClearDepth(1.0f);				
	glEnable(GL_DEPTH_TEST);		
	glDepthFunc(GL_LEQUAL);			
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);

	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, LightPosition2);

	glEnable(GL_LIGHT3);
	glLightfv(GL_LIGHT3, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT3, GL_POSITION, LightPosition3);

	glEnable(GL_LIGHT4);
	glLightfv(GL_LIGHT4, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT4, GL_POSITION, LightPosition4);
}