#include <GL/gl.h>
#include <GL/glut.h>

void display(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glClear (GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   glBegin(GL_TRIANGLES);
    glColor3f (1.0, 0.0, 0.0);
    glVertex3f(-0.5,-0.5,0);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(0.5,-0.5,0);
    glColor3f(0.0,0.0,1.0);
    glVertex3f(0.0,0.5,0);
   glEnd();
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.5, 1.5, -1.5, 1.5, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}



int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (350, 350);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}
