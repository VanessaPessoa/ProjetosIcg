#pragma once
#pragma once

#include  <GL/glut.h>
#include <functional>
#include "Model.h"

/*
The Car object, renders the car
*/
class Drone
{
public:
	Drone(const std::string fileName);
	GLfloat local[16];	//local coordinate system transformation matrix
	Model *drone;
	GLfloat camHorizontalAngle;
	GLfloat camVerticalAngle;
	GLfloat moveSpeed;
	GLfloat droneRotate;
	std::function<void()> nextMove;
	bool isMoving;


	//Functions
	void keyPressed(const unsigned char key);
	void keyUp(const unsigned char key);
	void init();
	void draw();
	~Drone() = default;
private:
	//update constant animation for tail wiggle and legs movement
	void updateCameraHoriMovement();
	bool isWPressing, isSPressing, isAPressing, isDPressing, isQPressing, isEPressing;
	GLfloat legsAngle;
	bool legsMovementDirectionForward;
};

