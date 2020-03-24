#include "lib.h"
#include <vector>
#include "Drone.h"
#include <cstdio>
#include "Box.h"
#include "PointLigth.h"

using namespace std;

#define DRONE "obj/drone.obj"
#define COLISEU "obj/coliseu.obj"
#define PESSOAS "obj/a.obj"
#define HOMEM "obj/f.obj"
#define MULHER "obj/g.obj"
#define GRUPO "obj/grupo.obj"
//#define ARVORE  "obj/arvore.obj"

float angle = 0.0f, angleM = 0.f;
float lx = 0.0f, lz = -1.0f;
float x = 0.0f, y = 1.f, z = 5.0f;
int mainWindow;
int w, h;

//Lights
PointLight pointlight(100, 800, -500);
GLfloat globalAmbient = 0.5f;

//ID das texturas
GLuint texture[6];

//Models
std::vector<Drone*> drones;
std::vector<Model*> models;
std::vector<Model*> pessoas;
std::vector<Model*> persona;
std::vector<Model*> mulher;
std::vector<Model*> grupo;
std::vector<Model*> familia;
std::vector<Model*> arvore;


void initTexture() {
	glEnable(GL_DEPTH_TEST);
	glGenTextures(6, texture);

	loadTex(0, "img/posy.bmp", texture);
	loadTex(1, "img/negy.bmp", texture);
	loadTex(2, "img/posx.bmp", texture);
	loadTex(3, "img/negx.bmp", texture);
	loadTex(4, "img/posz.bmp", texture);
	loadTex(5, "img/negz.bmp", texture);
}

void changeSize(int width, int heigth) {
	w = width;
	h = heigth;
	if (h == 0)
		h = 1;

	float ratio = (float)w * 1.0 / h;
	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.f, ratio, 1.f, 1000.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void initModels() {
	Model *coliseu = new Model(COLISEU);
	Model *pessoa = new Model(PESSOAS);
	Model *person = new Model(HOMEM);
	Model *woman = new Model(MULHER);
	Model *grup = new Model(GRUPO);
 	Drone *drone = new Drone(DRONE);
		
	if (!drone->drone->importModel())
		std::cout << "Import model error!" << std::endl;

	if (!coliseu->importModel())
		std::cout << "Import model error!" << std::endl;

	if (!woman->importModel())
		std::cout << "Import model error!" << std::endl;

	if (!pessoa->importModel())
		std::cout << "Import model error!" << std::endl;

	if (!person->importModel())
		std::cout << "Import model error!" << std::endl;

	if (!grup->importModel())
		std::cout << "Import model error!" << std::endl;


	persona.push_back(person);
	pessoas.push_back(pessoa);
	models.push_back(coliseu);
	drones.push_back(drone);
	mulher.push_back(woman);
	grupo.push_back(grup);
}

void deleteModels() {
	delete drones[0];
	delete models[0];
	delete pessoas[0];
	delete persona[0];
	delete grupo[0];
}


void drawScene() {
	glPushMatrix();
	glTranslatef(pointlight.position[0], pointlight.position[1], pointlight.position[2]);
	pointlight.addLight();
	glPopMatrix();
	pointlight.draw();

	glStencilMask(0x00);
	drawSkybox(texture);

	// Draw ground
	glPushMatrix();
	glScalef(40, 40, 34);
	glRotatef(180.f, 0, 1, 0);
	glTranslatef(1, -2.5, 1);
	models[0]->renderTheModel(0.3);
	glPopMatrix();
	
	//personagens
	glPushMatrix();
	glRotatef(180.f, 0, 1, 0);
	glTranslatef(10, -97.2, 1);
	pessoas[0]->renderTheModel(0.3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(45.f, 0, 1, 0);
	glTranslatef(35, -97.2, -50);
	pessoas[0]->renderTheModel(0.3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(45.f, 0, 1, 0);
	glTranslatef(-2, -97.2, -100);
	pessoas[0]->renderTheModel(0.3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.f, 0, 1, 0);
	glTranslatef(10, -93.5, 190);
	persona[0]->renderTheModel(0.35);
	glPopMatrix();

	glPushMatrix();
	glRotatef(40.f, 0, 1, 0);
	glTranslatef(-50, -93.5, 130);
	persona[0]->renderTheModel(0.35);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.f, 0, 1, 0);
	glTranslatef(40, -93.5, 80);
	persona[0]->renderTheModel(0.35);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180.f, 0, 1, 0);
	glTranslatef(50, -94, 200);
	mulher[0]->renderTheModel(0.3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.f, 0, 1, 0);
	glTranslatef(85, -94, 100);
	mulher[0]->renderTheModel(0.3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180.f, 0, 1, 0);
	glTranslatef(-10, -97, 20);
	grupo[0]->renderTheModel(0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-50, -97, 20);
	grupo[0]->renderTheModel(0.3);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.f, 0, 1, 0);
	glTranslatef(50, -97, 20);
	grupo[0]->renderTheModel(0.3);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(15.f, 0, 1, 0);
	glTranslatef(-70, -97, -40);
	grupo[0]->renderTheModel(0.3);
	glPopMatrix();

	//paisagem


	//Draw drone Model
	glPushMatrix();
	glMultMatrixf(drones[0]->local);
	drones[0]->draw();
	glPopMatrix();
}

void display(void) {
	// Clear Color and Depth Buffers
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Update car transformation matrix
	if (drones[0]->nextMove) {
		drones[0]->isMoving = true;
		GLfloat viewModelMatrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, viewModelMatrix);
		glLoadMatrixf(drones[0]->local);
		drones[0]->nextMove();
		drones[0]->nextMove = nullptr;
		glGetFloatv(GL_MODELVIEW_MATRIX, drones[0]->local);
		glLoadMatrixf(viewModelMatrix);
	}

	/*Camera do drone*/
	GLfloat viewModelMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, viewModelMatrix);
	glLoadMatrixf(drones[0]->local);

	glRotatef(drones[0]->camVerticalAngle, 1, 0, 0);
	glRotatef(drones[0]->camHorizontalAngle, 0, 1, 0);
	glTranslated(0, 1.5, 0.9);

	GLfloat cameraPoseInCarView[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, cameraPoseInCarView);
	glLoadMatrixf(viewModelMatrix);

	GLfloat zAngle = atan2(-cameraPoseInCarView[2], cameraPoseInCarView[0]);
	GLfloat yAngle = atan2(-cameraPoseInCarView[9], cameraPoseInCarView[5]);

	gluLookAt(cameraPoseInCarView[12], cameraPoseInCarView[13], cameraPoseInCarView[14],
		sin(zAngle) + cameraPoseInCarView[12],
		-yAngle + cameraPoseInCarView[13],
		cos(zAngle) + cameraPoseInCarView[14],
		0, 1, 0);

	GLfloat globalAmbientVec[4] = { globalAmbient, globalAmbient, globalAmbient, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientVec);

	drawScene();

	glColorMask(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST); 

	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); 

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void normalKeyPress(unsigned char key, int xx, int yy) {
	drones[0]->keyPressed(key);
}

void normalKeyUp(unsigned char key, int x, int y) {
	drones[0]->keyUp(key);
}

void processNormalKeys(unsigned char key, int xx, int yy){
	if (key == 27)
		exit(0);
}

void init() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// register callbacks
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	initModels();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE | GLUT_STENCIL);
	glutInitWindowPosition(150, 0);
	glutInitWindowSize(700, 1000);
	mainWindow = glutCreateWindow("Coliseu");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(changeSize);
	init();

	glutKeyboardFunc(normalKeyPress);
	glutKeyboardUpFunc(normalKeyUp);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	pointlight.enable();	
	drones[0]->init();
	initTexture();
	glutMainLoop();
	deleteModels();
	return 0;
}
