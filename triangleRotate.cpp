#include<iostream>
using namespace std;
#include<GL/glut.h>
#include<math.h>
float p[3][2] = { {20,20},{40,40},{60,20} };
float xp, yp, theta, rtheta;
void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);
	glMatrixMode(GL_MODELVIEW);
}
void drawtraiangle()
{
	glBegin(GL_TRIANGLES);
	glVertex2fv(p[0]);
	glVertex2fv(p[1]);
	glVertex2fv(p[2]);
	glEnd();
}

void display()
{
	float x, y;
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	drawtraiangle();
	rtheta = (theta * 3.142) / 180;
	for (int i = 0; i < 3; i++)
	{
		x = p[i][0];
		y = p[i][1];
		p[i][0] = xp + (x - xp) * cos(rtheta) - (y - yp) * sin(rtheta);
		p[i][1] = yp + (x - xp) * sin(rtheta) + (y - yp) * cos(rtheta);
	}
	
	glColor3f(0, 1, 0);
	drawtraiangle();
	glFlush();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Traingle rotation");
	myinit();
	cout<< "enter xp,yp and theta" << endl;
	cin >> xp >> yp >> theta;
	glutDisplayFunc(display);
	glutMainLoop();
}