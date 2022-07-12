#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
// float v1[8][3] = { {-1,-1,1},{-1,1,1},{1,1,1},{1,-1,1},{-1,-1,-1},{-1,1,-1},{1,1,-1},{1,-1,-1} };
float p[8][3] = { {0,0,1},{0,1,1},{1,1,1},{1,0,1},{0,0,0},{0,1,0},{1,1,0},{1,0,0} };
float v[8][3] = { {0,0,2},{0,2,2},{2,2,2},{2,0,2},{0,0,0},{0,2,0},{2,2,0},{2,0,0} };


float theta[3] = { 0,0,0 };
int flag = 2;
#include<GL/glu.h>
#include<GL/glut.h>

GLfloat d = 0;
int a=0;

void MyInit()
{
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
}

void Spin()
{
    d = d + 0.25;
    if(d > 360)
        d = 0;
    glutPostRedisplay();
}

void Face(GLfloat A[],GLfloat B[],GLfloat C[],GLfloat D[])
{
    glBegin(GL_POLYGON);
        glVertex3fv(A);
        glVertex3fv(B);
        glVertex3fv(C);
        glVertex3fv(D);
    glEnd();
}

void Cube(GLfloat V0[],GLfloat V1[],GLfloat V2[],GLfloat V3[],GLfloat V4[],GLfloat V5[],GLfloat V6[],GLfloat V7[])
{
    glColor3f(1,0,0);
    Face(V0,V1,V2,V3); //Front
    glColor3f(0,1,0);
    Face(V4,V5,V6,V7); //Back
    glColor3f(0,0,1);
    Face(V0,V4,V7,V3); //Left
    glColor3f(1,1,0);
    Face(V1,V5,V6,V2); //Right
    glColor3f(1,0,1);
    Face(V2,V3,V7,V6); //Bot
    glColor3f(0,1,1);
    Face(V0,V1,V5,V4); //Top
}

void Draw()
{
    GLfloat V[8][3] =   {
                            {-0.5, 0.5, 0.5},
                            { 0.5, 0.5, 0.5},
                            { 0.5,-0.5, 0.5},
                            {-0.5,-0.5, 0.5},
                            {-0.5, 0.5,-0.5},
                            { 0.5, 0.5,-0.5},
                            { 0.5,-0.5,-0.5},
                            {-0.5,-0.5,-0.5},
                        };
    GLfloat rV[8][3],r;
    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    r = d*3.14/180;

    if(a == 1)
    {
        for(i=0;i<8;i++)
        {
            rV[i][0] = V[i][0];
            rV[i][1] = V[i][1]*cos(r)-V[i][2]*sin(r);
            rV[i][2] = V[i][1]*sin(r)+V[i][2]*cos(r);
        }
    }

    if(a == 2)
    {
        for(i=0;i<8;i++)
        {
            rV[i][0] = V[i][2]*sin(r)+V[i][0]*cos(r);
            rV[i][1] = V[i][1];
            rV[i][2] = V[i][2]*cos(r)-V[i][0]*sin(r);
        }
    }

    if(a == 3)
    {
        for(i=0;i<8;i++)
        {
            rV[i][0] = V[i][0]*cos(r)-V[i][1]*sin(r);
            rV[i][1] = V[i][0]*sin(r)+V[i][1]*cos(r);
            rV[i][2] = V[i][2];
        }
    }

    Cube(rV[0],rV[1],rV[2],rV[3],rV[4],rV[5],rV[6],rV[7]);

    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    printf("Enter the Axis of Rotation [ 1->Xaxis | 2->Yaxis | 3->Zaxis ]: ");
    scanf("%d",&a);
    glutInit(&argc,argv);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(50,150);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Cube Spin with Matrices");
    MyInit();
    glutDisplayFunc(Draw);
    glutIdleFunc(Spin);
    glutMainLoop();
    return 0;
}

void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4, 4, -4, 4, -4, 4);
    glMatrixMode(GL_MODELVIEW);
}
void idlefunc()
{
    theta[flag]++;
    if (theta[flag] > 360)theta[flag] = 0;
    glutPostRedisplay();
}
void mousefunc(int button, int status, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && status == GLUT_DOWN)
        flag = 2;
    if (button == GLUT_MIDDLE_BUTTON && status == GLUT_DOWN)
        flag = 1;
    if (button == GLUT_RIGHT_BUTTON && status == GLUT_DOWN)
        flag = 0;
}
void drawpoly(int a, int b, int c, int d)
{
    glBegin(GL_POLYGON);
    glColor3fv(p[a]);
    glVertex3fv(v[a]);
    glColor3fv(p[b]);
    glVertex3fv(v[b]);
    glColor3fv(p[c]);
    glVertex3fv(v[c]);
    glColor3fv(p[d]);
    glVertex3fv(v[d]);
    glEnd();
}
void colorcube()
{
    drawpoly(0, 1, 2, 3);
    drawpoly(0, 1, 5, 4);
    drawpoly(1, 5, 6, 2);
    drawpoly(4, 5, 6, 7);
    drawpoly(3, 2, 6, 7);
    drawpoly(0, 4, 7, 3);
}
void display()
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glColor3f(1, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glRotatef(theta[0], 1, 0, 0);//x
    glRotatef(theta[1], 0, 1, 0);//y
    glRotatef(theta[2], 0, 0, 1);//z
    colorcube();
    glFlush();
    glutSwapBuffers();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("cube rotation");
    myinit();
    glutDisplayFunc(display);
    glutMouseFunc(mousefunc);
    glutIdleFunc(idlefunc);
    glutMainLoop();
}
