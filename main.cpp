#include <bits/stdc++.h>
using namespace std;
#include <GL/gl.h>
#include <GL/glut.h>
#define ll long long int
#define ld long double
/// Grid Setup
class Grid
{
private:
    ll numRows, numCols, cellSize;
public:
    vector<vector<int>> grid;
    Grid()
    {
        numRows = 20;
        numCols = 10;
        cellSize = 30;
        initialize();
    }
    void initialize() {
        grid.resize(numRows);
        for( ll row = 0; row < numRows; row += 1 ) {
            grid[row].resize(numCols,0);
        }
    }
    void print() {
        for( ll row = 0; row < numRows; row += 1 ) {
            for( ll col = 0; col < numCols; col += 1 ) {
                cout << grid[row][col] << " ";
            }
            cout << endl;
        }
    }
};

void display(void)
{
    /// Setting up Background color
    glClear(GL_COLOR_BUFFER_BIT );
    glClearColor(0.172, 0.172, 0.498, 1.0);
    glutSwapBuffers();
    Grid grid = Grid();
    grid.print();

    return ;
}

void myInit (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.172f, 0.172f, 0.498f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
	return ;
}
int main(int argc, char ** argv)
{
	glutInit( & argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tetris Game by Ruhul Amin Sharif");
	myInit ();
	glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
