#include "Drone.h"
#include <GL\glut.h>
#include "Model.h"
#include <glm.hpp>
#include "Drone.h"

Drone::Drone(const std::string fileName) {
	drone = new Model(fileName);
	camHorizontalAngle = 0.f;
	camVerticalAngle = 15.f;
	moveSpeed = 1;
	droneRotate = 90.f;
	isWPressing = isSPressing = isAPressing = isDPressing = isQPressing = isEPressing = false;
	legsAngle = 0.0f;
	legsMovementDirectionForward = true;
	nextMove = nullptr;
	isMoving = false;
}

void Drone::keyPressed(const unsigned char key)
{
	switch (key) {
	case 'W':
	case 'w':
		isWPressing = true;
		break;

	case 'S':
	case 's':
		isSPressing = true;
		break;

	case 'A':
	case 'a':
		isAPressing = true;
		break;

	case 'D':
	case 'd':
		isDPressing = true;
		break;

	case 'Q':
	case 'q':
		isQPressing = true;
		break;

	case 'e':
	case 'E':
		isEPressing = true;
		break;

	default:
		isAPressing = isSPressing = isDPressing = isEPressing = isQPressing = isWPressing = false;
		break;
	}
}

//Funcao que reconhece quando a tecla parou de ser pressionada
void Drone::keyUp(const unsigned char key) {
	switch (key) {

	case 'W':
	case 'w':
		isWPressing = false;
		this->moveSpeed = 2;
		break;

	case 'S':
	case 's':
		isSPressing = false;
		break;

	case 'A':
	case 'a':
		isAPressing = false;
		this->droneRotate = 90;
		break;

	case 'D':
	case 'd':
		isDPressing = false;
		this->droneRotate = 90;
		break;

	case 'Q':
	case 'q':
		isQPressing = false;
		break;

	case 'e':
	case 'E':
		isEPressing = false;
		break;

	default:
		break;
	}

}

void Drone::init() {
	GLfloat viewModelMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, viewModelMatrix);
	glLoadIdentity();

	glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0, 1.2, -5.f);

	glGetFloatv(GL_MODELVIEW_MATRIX, local);
	glLoadMatrixf(viewModelMatrix);
}

void Drone::draw() {
	updateCameraHoriMovement();
	glPushMatrix();

	GLfloat carSpecular[] = { 1.f, 1.f, 1.f };
	GLfloat carShininess = 1.f;

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, carSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, carShininess);
	glMaterialf(GL_FRONT_AND_BACK, GL_EMISSION, 1);

	glColorMaterial(GL_FRONT, GL_SHININESS);
	glEnable(GL_COLOR_MATERIAL);

	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);

	glTranslatef(0, 0, 6.0);
	glScalef(1.f, 1.f, 1.f);
	glRotatef(this->droneRotate, 0.f, 1.f, 0.f);
	drone->renderTheModel(0.09);
	glPopMatrix();
}

void Drone::updateCameraHoriMovement() {
	double dx = 0;
	double dz = 0;
	double dy = 0;

	if (isWPressing) {
		dz += 4;
		(moveSpeed < 2.5f) ? moveSpeed += 0.002f : moveSpeed = 2.5f;
	}
	if (isSPressing)
		dz -= 4;
	if (isAPressing) {
		dx += 4;
		this->droneRotate = 120.f;
	}
	if (isDPressing) {
		dx -= 2;
		this->droneRotate = 120.f;
	}
	if (isQPressing) {
		dy += 2;
	}
	if (isEPressing) {
		dy -= 2;
	}


	if (dz != 0 && dx == 0) {
		nextMove = [dz, dy]() {
			glTranslated(0, dy, dz);
		};
	}
	else if (dz != 0 && dx == 0) {
		nextMove = [dz, dy]() {
			glTranslated(0, dy, dz);
		};
	}
	else if (dz > 0 && dx != 0) {
		nextMove = [dz, dx, dy]() {
			glTranslated(0, dy, dz);
			glRotatef(dx, 0, 1, 0);
		};
	}
	else if (dz > 0 && dx != 0) {
		nextMove = [dz, dx, dy]() {
			glTranslated(0, dy, dz);
			glRotatef(dx, 0, 1, 0);
		};
	}
	else if (dz < 0 && dx != 0) {
		nextMove = [dz, dx, dy]() {
			glTranslated(0, dy, dz);
			glRotatef(-dx, 0, 1, 0);
		};

	}
	else if (dy != 0) {
		nextMove = [dz, dx, dy]() {
			glTranslated(0, dy, 0);
		};
	}
}
