#include <bits/stdc++.h>
using namespace std;
#include <GL/gl.h>
#include <GL/glut.h>
#define ll long long int
#define ld long double
// Define the Color structure
struct Color {
    float r, g, b, a;

    Color() : r(0), g(0), b(0), a(1) {} // Default constructor
    Color(float red, float green, float blue, float alpha = 1.0f)
        : r(red), g(green), b(blue), a(alpha) {}
};
/// Grid Setup
class Grid
{
private:
    ll numRows, numCols, cellSize;
    vector<Color>colors;

public:
    vector<vector<int>> grid;

    Grid()
    {
        numRows = 20;
        numCols = 10;
        cellSize = 30;
        initialize();
        colors = getCellColors();
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
    vector<Color> getCellColors() {
        // Define the color constants
        const Color darkGrey = {26.0f / 255.0f, 31.0f / 255.0f, 40.0f / 255.0f, 1.0f};
        const Color green = {47.0f / 255.0f, 230.0f / 255.0f, 23.0f / 255.0f, 1.0f};
        const Color red = {232.0f / 255.0f, 18.0f / 255.0f, 18.0f / 255.0f, 1.0f};
        const Color orange = {226.0f / 255.0f, 116.0f / 255.0f, 17.0f / 255.0f, 1.0f};
        const Color yellow = {237.0f / 255.0f, 234.0f / 255.0f, 4.0f / 255.0f, 1.0f};
        const Color purple = {166.0f / 255.0f, 0.0f / 255.0f, 247.0f / 255.0f, 1.0f};
        const Color cyan = {21.0f / 255.0f, 204.0f / 255.0f, 209.0f / 255.0f, 1.0f};
        const Color blue = {13.0f / 255.0f, 64.0f / 255.0f, 216.0f / 255.0f, 1.0f};
        const Color lightBlue = {59.0f / 255.0f, 85.0f / 255.0f, 162.0f / 255.0f, 1.0f};
        const Color darkBlue = {44.0f / 255.0f, 44.0f / 255.0f, 127.0f / 255.0f, 1.0f};

        return {darkGrey, green, red, orange, yellow, purple, cyan, blue, lightBlue, darkBlue};
    }
    void draw() {
        // plotting the grid
        for( ll row = 0; row < numRows; row += 1 ) {
            for( ll col = 0; col < numCols; col += 1 ) {
                ll val = grid[row][col];
                if (val < 0 || val >= colors.size()) val = 0;
                plotRectangle(  col * cellSize+11, row * cellSize+11, cellSize-1, cellSize-1, colors[val] );
            }
        }

    }
    void plotRectangle( ll posX, ll posY, ll width, ll height, const Color& colorObj  ) {
        glColor4f(colorObj.r, colorObj.g, colorObj.b, colorObj.a);
        glBegin(GL_QUADS);
        glVertex2f(posX, posY);
        glVertex2f(posX + width, posY);
        glVertex2f(posX + width, posY + height);
        glVertex2f(posX, posY + height);
        glEnd();
        return ;
    }

};
void display(void)
{
    /// Setting up Background color
    glClear(GL_COLOR_BUFFER_BIT );
    glClearColor(0.172, 0.172, 0.498, 1.0);

    Grid grid = Grid();
    grid.grid[0][0] = 1;
    grid.grid[3][5] = 4;
    grid.grid[17][8] = 7;
    grid.print();
    grid.draw();
    glutSwapBuffers();
    return ;
}

void myInit (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.172f, 0.172f, 0.498f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 800.0, 0.0, 600.0);
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
