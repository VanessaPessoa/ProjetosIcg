#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm.hpp>

#define BoxSize 1000.f

void loadTex(int i, const char *filename, GLuint* texture);
void drawRect(GLuint texture);
void drawSkybox(GLuint *texture);
void setupLights();




