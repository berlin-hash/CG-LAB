#include<GL/glut.h>
#include<iostream>
using namespace std;
int le[500],re[500];

void myinit(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
    glMatrixMode(GL_MODELVIEW);
}
void Intersection(GLint x1,GLint y1,GLint x2,GLint y2)
{
    float x,M;
    int t,y;
    if(y1>y2)
    {
        t = x1;
        x1 = x2;
        x2 = t;

        t = y1;
        y1 = y2;
        y2 = t;
    }

    if((y2-y1)==0)
        M = (x2-x1);
    else
        M = (x2-x1)/(y2-y1);

    x = x1;
    for(y=y1;y<=y2;y++)
    {
        if(x<le[y])
            le[y]=x;
        if(x>re[y])
            re[y]=x;

        x = x + M;
    }
}
void draw(){
    int x,y;
    
    GLint P1[2] = {125,250},P2[2] = {250,125},P3[2] = {375,250},P4[2] = {250,375};
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i=0;i<500;i++){
        le[i]=500;
        re[i]=0;
    }
    glBegin(GL_LINE_LOOP);
        glVertex2iv(P1);
        glVertex2iv(P2);
        glVertex2iv(P3);
        glVertex2iv(P4);
    
    glEnd();
    Intersection(P1[0],P1[1],P2[0],P2[1]);
    Intersection(P2[0],P2[1],P3[0],P3[1]);
    Intersection(P3[0],P3[1],P4[0],P4[1]);
    Intersection(P4[0],P4[1],P1[0],P1[1]);  
    
    for(y=0;y<500;y++){
        for(x=le[y];x<re[y];x++){
            glBegin(GL_POINTS);
                glVertex2i(x,y);
            glEnd();
            glFlush();
        }
    }
    glFlush();
    
}
int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutCreateWindow("scanline");
    myinit(); 
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}