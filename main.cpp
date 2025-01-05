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
    bool isCellOutside(ll row, ll column) {
        if( row >= 0 && row < numRows && column >= 0 && column < numCols) {
            return false;
        }
        return true;
    }
};
/// Position Class
class Position
{
public:
    ll row, col;
    Position( ll row, ll col )
    {
        this -> row = row;
        this -> col = col;
    }
};
/// Block Class
class Block
{
private:
    ll cellsize, rotationState;
    vector<Color>colors;
    ll rowOffset, colOffset; /// to move the blocks
public:
    ll id; // to identify each block uniquely
    map<ll, vector<Position>>cells; /// key -> rotation state(0,1,2,3), then respective position in the grid
    Block()
    {
        cellsize = 30;
        rotationState = 0;
        colors = getCellColors();
        rowOffset = 0;
        colOffset = 0;
    }
    void draw() {
        vector<Position> tiles = getCellPositions();
        for( Position item : tiles ) {
            plotRectangle( item.col * cellsize + 11, item.row * cellsize + 11, cellsize -1 , cellsize - 1 , colors[id] );
        }
    }
    void move(ll rows, ll cols ) {
        rowOffset += rows;
        colOffset +=  cols;
    }
    vector<Position> getCellPositions() {
        vector<Position> tiles = cells[rotationState];
        vector<Position> movedTiles;
        for( Position item : tiles ) {
            Position newPos = Position(item.row+rowOffset,item.col+colOffset);
            movedTiles.push_back(newPos);
        }
        return movedTiles;
    }
    void rotate() {
        rotationState = (rotationState + 1) % cells.size();
    }
    void undoRotation() {
        rotationState -= 1;
        if( rotationState <= 0 ) {
            rotationState =  cells.size() - 1;
        }
    }
};
/// Creating L Block
class LBlock:public Block
{
public:
    LBlock() {
        id = 1;
        /**
            ..#
            ###
            ...
        **/
        cells[0] = { Position(0,2), Position(1,0), Position(1,1), Position(1,2)};
        /**
            .#.
            .#.
            .##
        **/
        cells[1] = { Position(0,1), Position(1,1), Position(2,1), Position(2,2)};
        /**
            ...
            ###
            #..
        **/
        cells[2] = { Position(1,0), Position(1,1), Position(1,2), Position(2,0)};
        /**
            ##.
            .#.
            .#.
        **/
        cells[3] = { Position(0,0), Position(0,1), Position(1,1), Position(2,1)};
        move(0,3);
    }
};
/// Creating the J Block
class JBlock : public Block
{
public:
    JBlock()
    {
        id = 2;
        /**
            #..
            ###
            ...
        **/
        cells[0] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2)};
        /**
            .##
            .#.
            .#.
        **/
        cells[1] = {Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 1)};
        /**
            ...
            ###
            ..#
        **/
        cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 2)};
        /**
            .#.
            .#.
            ##.
        **/
        cells[3] = {Position(0, 1), Position(1, 1), Position(2, 0), Position(2, 1)};
        move(0,3);
    }
};

class IBlock : public Block
{
public:
    IBlock()
    {
        id = 3;
        /**
            ....
            ####
            ....
            ....
        **/
        cells[0] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3)};
        /**
            ..#.
            ..#.
            ..#.
            ..#.
        **/
        cells[1] = {Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2)};
        /**
            ....
            ....
            ####
            ....
        **/
        cells[2] = {Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3)};
        /**
            .#..
            .#..
            .#..
            .#..
        **/
        cells[3] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1)};
        move(-1,3);
    }
};

class OBlock : public Block
{
public:
    OBlock()
    {
        /**
            ##
            ##
        **/
        id = 4;
        cells[0] = {Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1)};
        move(0,4);
    }
};

class SBlock : public Block
{
public:
    SBlock()
    {
        id = 5;
        /**
            .##
            ##.
            ...
        **/
        cells[0] = {Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1)};
        /**
            .#.
            .##
            ..#
        **/
        cells[1] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 2)};
        /**
            ...
            .##
            ##.
        **/
        cells[2] = {Position(1, 1), Position(1, 2), Position(2, 0), Position(2, 1)};
        /**
            #..
            ##.
            .#.
        **/
        cells[3] = {Position(0, 0), Position(1, 0), Position(1, 1), Position(2, 1)};
        move(0,3);
    }
};

class TBlock : public Block
{
public:
    TBlock()
    {
        id = 6;
        /**
            .#.
            ###
            ...
        **/
        cells[0] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2)};
        /**
            .#.
            .##
            .#.
        **/
        cells[1] = {Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 1)};
        /**
            ...
            ###
            .#.
        **/
        cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1)};
        /**
            .#.
            ##.
            .#.
        **/
        cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1)};
        move(0,3);
    }
};

class ZBlock : public Block
{
public:
    ZBlock()
    {
        id = 7;
        /**
            ##.
            .##
            ...
        **/
        cells[0] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2)};
        /**
            ..#
            .##
            .#.
        **/
        cells[1] = {Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 1)};
        /**
            ...
            ##.
            .##
        **/
        cells[2] = {Position(1, 0), Position(1, 1), Position(2, 1), Position(2, 2)};
        /**
            .#.
            ##.
            #..
        **/
        cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0)};
        move(0,3);
    }
};
class Game
{
private:
    vector<Block> blocks;
    Block currBlock, nextBlock;
public:
    Grid grid;
    Game()
    {
        grid = Grid();
        blocks = getAllBlocks();
        currBlock = getRandomBlock();
        nextBlock = getRandomBlock();
    }
    Block getRandomBlock() {
        if( blocks.empty() ) {
            blocks = getAllBlocks();
        }
        ll randomIndex = rand() % blocks.size();
        Block block = blocks[randomIndex];
        blocks.erase(blocks.begin() + randomIndex);
        return block;
    }
    vector<Block> getAllBlocks() {
        return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
    }
    void draw() {
        grid.draw();
        currBlock.draw();
    }
    void handleInput(unsigned char key, ll x, ll y) {
        switch (key) {
            case 'l': // 'a' for left
                moveBlockLeft();
                break;
            case 'r': // 'd' for right
                moveBlockRight();
                break;
            case 'd': // 's' for down
                moveBlockDown();
                break;
            case 'w': // 'w' for rotate
                rotateBlock();
                break;
            default:
                break;
        }
    }
    void handleSpecialInput(int key, int x, int y) {
        switch (key) {
            case GLUT_KEY_LEFT:
                moveBlockLeft();
                break;
            case GLUT_KEY_RIGHT:
                moveBlockRight();
                break;
            case GLUT_KEY_DOWN:
                moveBlockDown();
                break;
            case GLUT_KEY_UP:
                rotateBlock();
                break;
            default:
                break;
        }
    }
    bool isBlockOutside() {
        vector<Position> tiles = currBlock.getCellPositions();
        for (Position item : tiles) {
            if ( grid.isCellOutside( item.row, item.col ) ) {
                return true;
            }
        }
        return false;
    }
    void moveBlockLeft()
    {
        currBlock.move(0,-1);
        if( isBlockOutside() ) {
            currBlock.move(0, 1);
        }
    }
    void moveBlockRight() {
        currBlock.move(0, 1);
        if( isBlockOutside() ) {
            currBlock.move(0, -1);
        }
    }

    void moveBlockDown() {
        currBlock.move(1, 0);
        if( isBlockOutside() ) {
            currBlock.move(-1, 0);
        }
    }
    void rotateBlock() {
        currBlock.rotate();
        if( isBlockOutside() ) {
           // currBlock.undoRotation();
        }
    }
};
Game myGame = Game();
void display(void)
{
    /// Setting up Background color
    glClear(GL_COLOR_BUFFER_BIT );
    glClearColor(0.172, 0.172, 0.498, 1.0);


    myGame.draw();

    glutSwapBuffers();
    return ;
}
void handleInput(unsigned char key, int x, int y) {
    myGame.handleInput(key, x, y);
    glutPostRedisplay(); // Request display update
}
void handleSpecialInput(int key, int x, int y) {
    myGame.handleSpecialInput(key, x, y);
    glutPostRedisplay();
}
void myInit (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.172f, 0.172f, 0.498f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 620.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	return ;
}
int main(int argc, char ** argv)
{
	glutInit( & argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
	glutInitWindowSize(500, 620);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("Tetris Game by Ruhul Amin Sharif");
	myInit ();
	glutDisplayFunc(display);
	glutKeyboardFunc(handleInput);
	glutSpecialFunc(handleSpecialInput);
    glutMainLoop();
    return 0;
}
