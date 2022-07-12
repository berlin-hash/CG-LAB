#include <GL/glut.h>
#include <iostream>
using namespace std;
#include <math.h>
int Aniflag = 1;
GLfloat ya = 0;
bool incr = true;

void idleFunc()
{
    
    if(Aniflag == 1)
    {
        if(ya>-50 && incr == 1)
            ya = ya - 0.2;

        if(ya<=-50 && incr == 1)
            incr = 0;

        if(ya<50 && incr == 0)
            ya = ya + 0.2;

        if(ya>=50 && incr == 0)
            incr = 1;


        
    }
    glutPostRedisplay();
}

void Menu(int i)
{
    if (i == 1)
    {
        Aniflag = 1;
    }
    else if (i == 2)
    {
        Aniflag = 0;
    }
    else
    {
        exit(0);
    }
    glutPostRedisplay();
}

void DisplayFunc()
{
    GLfloat x[4], y1[4], y2[4];
    GLdouble xt[200], y1t[200], y2t[200],t;
    int i, c;
    glClear(GL_COLOR_BUFFER_BIT);

    x[0] = 100;
    x[1] = 200;
    x[2] = 200;
    x[3] = 300;
    y1[0] = 450;
    y1[1] = 450 + ya;
    y1[2] = 450 - ya;
    y1[3] = 450;
    y2[0] = 400;
    y2[1] = 400 + ya;
    y2[2] = 400 - ya;
    y2[3] = 400;
 
    for (i = 0, t = 0, c = 0; t < 1; i++, t = t + 0.01)
    {
        xt[i] = pow(1 - t, 3) * x[0] + 3 * t * pow(1 - t, 2) * x[1] + 3 * pow(t, 2) * (1 - t) * x[2] + pow(t, 3) * x[3];
        y1t[i] = pow(1 - t, 3) * y1[0] + 3 * t * pow(1 - t, 2) * y1[1] + 3 * pow(t, 2) * (1 - t) * y1[2] + pow(t, 3) * y1[3];
        y2t[i] = pow(1 - t, 3) * y2[0] + 3 * t * pow(1 - t, 2) * y2[1] + 3 * pow(t, 2) * (1 - t) * y2[2] + pow(t, 3) * y2[3];

        c++;
    }

    glColor3f(1, 0.25, 0);
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i < c; i++)
    {
        glVertex2d(xt[i], y1t[i]);
        glVertex2d(xt[i], y2t[i]);
    }
    glEnd();

    glFlush();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);

    glutCreateMenu(Menu);
    glutAddMenuEntry("Start", 1);
    glutAddMenuEntry("Stop", 2);
    glutAddMenuEntry("Exit", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Animate flag");
    init();
    glutIdleFunc(idleFunc);
    glutDisplayFunc(DisplayFunc);
    glutMainLoop();
}