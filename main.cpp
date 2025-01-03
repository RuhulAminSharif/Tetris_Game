#include <bits/stdc++.h>
using namespace std;
#include <GL/gl.h>
#include <GL/glut.h>
#define ll long long int
#define ld long double
ll x[2],y[2];
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    glPointSize(2.0);

    glFlush();
    return ;
}
void myInit (void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500, 500, 500, -500);
	return ;
}
int main(int argc, char ** argv)
{
	glutInit( & argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(100, 100);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tetris Game by Ruhul Amin Sharif");
	myInit ();
	glutDisplayFunc(display);
	glutMainLoop();
    return 0;
}
