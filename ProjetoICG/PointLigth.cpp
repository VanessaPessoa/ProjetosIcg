#include "PointLigth.h"

PointLight::PointLight(float lpX, float lpY, float lpZ) :
	color{ 1.f, 1.f,  1.f ,  1.f },
	difLight0{ 0.5f, 0.5f, 0.5f, 1.0f },
	position{ lpX, lpY, lpZ, 1.0f } {}

void PointLight::addLight() {
	if (!glIsEnabled(GL_LIGHT0))
		return;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, color);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180.0f);
}

void PointLight::draw()
{
	if (!glIsEnabled(GL_LIGHT0))
		return;
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor4fv(color);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

void PointLight::disable()
{
	glDisable(GL_LIGHT0);
}

void PointLight::enable()
{
	glEnable(GL_LIGHT0);
}