#include <Gl/glut.h>
#include <stdlib.h>

void desenha(){

    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);

    glBegin(GL_TRIANGLES);
        glVertex3f(-0.5,-0.5,0.0);
        glVertex3f(0.0,0.5, 0.0);
        glVertex3f(0.5,-0.5, 0.0);
    glEnd();

    glFlush();
}

void teclado(unsigned char key, int x, int y){
    if(key == 27){
        exit(0);
    }
}

void inicializa(){
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0,1.0,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);

}

void main(){
    glutInit();
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindows("Testando");
    glutDisplayFunc(desenha);
    glutKeyboardFunc(teclado);
    inicializa();
    InitGL( 640, 480);
    glutMainLoop();
    return (0);

    return 0;

}
