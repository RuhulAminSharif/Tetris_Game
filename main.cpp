#include <bits/stdc++.h>
using namespace std;
#include <GL/gl.h>
#include <GL/glut.h>
#define ll long long int
#define ld long double
#define PI acos(-1)
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

    return {darkGrey, green, red, orange, yellow, purple, cyan, blue, cyan, darkBlue, purple, green, red };
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
// Function to draw a filled circle segment (quarter-circle)
void DrawCircleSegment(float cx, float cy, float radius, int startAngle, int endAngle, int numSegments, const Color& colorObj ) {
    glColor4f(colorObj.r, colorObj.g, colorObj.b, colorObj.a);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // Center of the circle
    for (int i = startAngle; i <= endAngle; ++i) {
        float angle = i * PI / 180.0f;
        glVertex2f(cx + cos(angle) * radius, cy + sin(angle) * radius);
    }
    glEnd();
}

// Function to draw a rounded rectangle
void DrawRectangleRounded(float x, float y, float width, float height, float roundness, int segments, const Color& colorObj) {
    float radius = roundness * fmin(width, height) / 2.0f;

    // Draw the main rectangle body (without the corners)
    glColor4f(colorObj.r, colorObj.g, colorObj.b, colorObj.a);
    glBegin(GL_QUADS);
    glVertex2f(x + radius, y); // Bottom-left
    glVertex2f(x + width - radius, y); // Bottom-right
    glVertex2f(x + width - radius, y + height); // Top-right
    glVertex2f(x + radius, y + height); // Top-left
    glEnd();

    // Draw the left and right side rectangles
    glBegin(GL_QUADS);
    // Left side
    glVertex2f(x, y + radius);
    glVertex2f(x + radius, y + radius);
    glVertex2f(x + radius, y + height - radius);
    glVertex2f(x, y + height - radius);
    // Right side
    glVertex2f(x + width - radius, y + radius);
    glVertex2f(x + width, y + radius);
    glVertex2f(x + width, y + height - radius);
    glVertex2f(x + width - radius, y + height - radius);
    glEnd();

    // Draw the corner circles (quarter-circle segments)
    DrawCircleSegment(x + radius, y + radius, radius, 180, 270, segments, colorObj); // Bottom-left
    DrawCircleSegment(x + width - radius, y + radius, radius, 270, 360, segments, colorObj); // Bottom-right
    DrawCircleSegment(x + width - radius, y + height - radius, radius, 0, 90, segments, colorObj); // Top-right
    DrawCircleSegment(x + radius, y + height - radius, radius, 90, 180, segments, colorObj); // Top-left
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
    bool isCellEmpty(ll row, ll column) {
        return grid[row][column] == 0;
    }
    ll clearFullRows( ) {
        ll tot = 0;
        for( ll row = numRows - 1; row >= 0; row -= 1 ) {
            if( isRowFull( row) ) {
                tot += 1;
            }
            else if( tot > 0 ) {
                moveRowDown( row, tot );
            }
        }
        return tot;
    }
    bool isRowFull( ll row ) {
        for( ll col = 0; col < numCols; col += 1 ) {
            if( grid[row][col] == 0 ) {
                return false;
            }
        }
        return true;
    }
    void clearRow( ll row ) {
        for( ll col = 0; col < numCols; col += 1 ) {
            grid[row][col] = 0;
        }
    }
    void moveRowDown( ll whichRow, ll howManyRows ) {
        for( ll col = 0; col < numCols; col += 1 ) {
            grid[whichRow+howManyRows][col] = grid[whichRow][col];
            grid[whichRow][col] = 0;
        }
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
    void draw(ll offSetX, ll offSetY ) {
        vector<Position> tiles = getCellPositions();
        for( Position item : tiles ) {
            plotRectangle( item.col * cellsize + offSetX, item.row * cellsize + offSetY, cellsize -1 , cellsize - 1 , colors[id] );
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
        rotationState = (rotationState - 1 + cells.size()) % cells.size();
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
class ComplexBlock1 : public Block {
public:
    ComplexBlock1() {
        id = 8; // unique ID for ComplexBlock1
        /**
            .#.
            ###
            .#.
        **/
        cells[0] = cells[1] = cells[2] = cells[3] = {Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1)};
        move(0, 3);
    }
};
class ComplexBlock2 : public Block {
public:
    ComplexBlock2() {
        id = 9; // unique ID for ComplexBlock2
        /**
            .##.
            .##.
            ####
            ....
        **/
        cells[0] = {Position(0, 1), Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3)};
        /**
            ...#
            .###
            .###
            ...#
        **/
        cells[1] = {Position(0, 3),Position(1, 1),Position(1, 2), Position(1, 3),Position(2, 1),Position(2, 2), Position(2, 3), Position(3,3)};
        /**
            ####
            .##.
            .##.
            ....
        **/
        cells[2] = {Position(0, 0),Position(0, 1),Position(0, 2), Position(0, 3),Position(1, 1),Position(1, 2), Position(2, 1), Position(2,2)};
        /**
            #...
            ###.
            ###.
            #...
        **/
        cells[3] = {Position(0, 0),Position(1, 0),Position(1, 1), Position(1, 2),Position(2, 0),Position(2, 1), Position(2, 2), Position(3,0)};

        move(0, 3);
    }
};
class ComplexBlock3 : public Block {
public:
    ComplexBlock3() {
        id = 10; // unique ID for ComplexBlock3
        /**
            ..##.
            #####
            ..##.
            .....
        **/
        cells[0] = {Position(0, 2), Position(0, 3), Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3), Position(1, 4), Position(2, 2), Position(2, 3)};
        /**
            ..#.
            .###.
            .###.
            ..#..
            ..#..
        **/
        cells[1] = {Position(0, 2), Position(1,1), Position(1, 2), Position(1, 3), Position(2, 1), Position(2, 2), Position(2, 3), Position(3, 3), Position(4, 3)};
        /**
            .##..
            #####
            .##..
            .....
        **/
        cells[2] = {Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3), Position(1, 4), Position(2, 1), Position(2, 2)};
        /**
            ..#.
            ..#.
            .###.
            .###.
            ..#..
        **/
        cells[3] = {Position(0, 2), Position(1, 2), Position(2,1), Position(2, 2), Position(2, 3), Position(3, 1), Position(3, 2), Position(3, 3), Position(4, 3)};
        move(0, 3);
    }
};
class Game
{
private:
    vector<Block> blocks;
    vector<Block> complexBlocks;
    Block currBlock, nextBlock;
public:
    Grid grid;
    bool gameOver;
    ll score;
    ll level;
    ll scoreForNextLevel;
    ll timerInterval;
    ll windowID;
    bool levelUpMsg;
    ll nextComplexBlockIndex;
    Game()
    {
        grid = Grid();
        blocks = getAllBlocks();
        currBlock = getRandomBlock();
        nextBlock = getRandomBlock();
        gameOver = false;
        score = 0;
        level = 1;
        scoreForNextLevel = 500;
        timerInterval = 500;
        levelUpMsg = false;
        complexBlocks = {ComplexBlock1(), ComplexBlock2(), ComplexBlock3()};
        nextComplexBlockIndex = 0;
    }
    void increaseLevel() {
        level += 1;
        scoreForNextLevel += 500;
        timerInterval = max( 100LL, timerInterval - 100 );
        grid = Grid();
        if( nextComplexBlockIndex < complexBlocks.size()) {
            nextComplexBlockIndex++;
            blocks.push_back(complexBlocks[nextComplexBlockIndex-1]);
        }
        currBlock = getRandomBlock();
        nextBlock = getRandomBlock();
        gameOver = false;
        levelUpMsg = true;
    }
    void reset() {
        grid = Grid(); /// need to change later ---
        blocks = getAllBlocks();
        currBlock = getRandomBlock();
        nextBlock = getRandomBlock();
        gameOver = false;
        score = 0;
        level = 1;
        scoreForNextLevel = 1000;
        timerInterval = 500;
        levelUpMsg = false;
        nextComplexBlockIndex = 0;
    }
    void updateScore( ll lines, ll moveDownPoints ) {
        if( lines == 1 ) {
            score += 100;
        }
        else if( lines == 2 ) {
            score += 300;
        }
        else if( lines == 3 ) {
            score += 600;
        }
        else if( lines >= 4 ) {
            score += ( lines * 250 );
        }
        score += moveDownPoints;
        if (score >= scoreForNextLevel) {
            increaseLevel();
        }
    }
    Block getRandomBlock() {
        if( blocks.empty() ) {
            for( ll i = 1; i <= nextComplexBlockIndex; i += 1 ) {
                blocks.push_back(complexBlocks[i-1]);
            }
            vector<Block> temp = getAllBlocks();
            for( auto blk : temp ) {
                blocks.push_back(blk);
            }
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
        currBlock.draw(11, 11);
        if( nextBlock.id == 3 ) {
            nextBlock.draw(255, 290);
        }
        else if( nextBlock.id == 4 ) {
            nextBlock.draw(255, 280);
        }
        else {
            nextBlock.draw(270, 270);
        }

    }
    void handleInput(unsigned char key, ll x, ll y) {
        if ( gameOver ) {
            if (key == 'n') { // 'n' for new game
                reset(); // Call the reset method
            }
        }
        else {
            switch (key) {
                case 'l': // 'l' for left
                    moveBlockLeft();
                    break;
                case 'r': // 'r' for right
                    moveBlockRight();
                    break;
                case 'd': // 'd' for down
                    moveBlockDown();
                    updateScore(0,1);
                    break;
                case 'w': // 'w' for rotate
                    rotateBlock();
                    break;
                default:
                    break;
            }
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
                updateScore(0,1);
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
        if( gameOver == false ) {
            currBlock.move(0,-1);
            if( isBlockOutside() || isBlockFits() == false ) {
                currBlock.move(0, 1);
            }
        }
    }
    void moveBlockRight() {
        if( gameOver == false ) {
            currBlock.move(0, 1);
            if( isBlockOutside() || isBlockFits() == false ) {
                currBlock.move(0, -1);
            }
        }
    }
    void moveBlockDown() {
        if( gameOver == false ) {
            currBlock.move(1, 0);
            if( isBlockOutside() || isBlockFits() == false ) {
                currBlock.move(-1, 0);
                lockBlock();
            }
        }
    }
    void lockBlock() {
        vector<Position> tiles = currBlock.getCellPositions();
        for (Position item : tiles) {
            grid.grid[item.row][item.col] = currBlock.id;
        }
        currBlock = nextBlock;
        if( isBlockFits() == false ) {
            gameOver = true;
        }
        nextBlock = getRandomBlock();
        ll lines = grid.clearFullRows();
        updateScore( lines, 0 );
    }
    void rotateBlock() {
        if( gameOver == false ) {
            currBlock.rotate();
            if( isBlockOutside() || isBlockFits() == false ) {
                currBlock.undoRotation();
            }
        }
    }
    bool isBlockFits() {
        vector<Position> tiles = currBlock.getCellPositions();
        for (Position item : tiles) {
            if( grid.isCellEmpty(item.row, item.col) == false ) {
                return false;
            }
        }
        return true;
    }
};
Game myGame = Game();
// Function to render text
void renderBitmapString(float x, float y, void* font, const string& text) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(font, c);
    }
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
// Function to draw text
void drawText(const std::string& text, float x, float y, void* font, float color[3]) {
    glColor3f(color[0], color[1], color[2]); // Set text color

    glRasterPos2f(x, y); // Position text
    for (char c : text) {
        glutBitmapCharacter(font, c);
    }
}
void update(int value) {

    myGame.moveBlockDown(); // Move the current block down
    glutPostRedisplay(); // Redraw the scene
    glutTimerFunc(myGame.timerInterval, update, 0); // Call update again after 500 milliseconds (0.5 seconds)
}

void handleInput(unsigned char key, int x, int y) {
    myGame.handleInput(key, x, y);
    glutPostRedisplay(); // Request display update
}
void handleSpecialInput(int key, int x, int y) {
    myGame.handleSpecialInput(key, x, y);
    glutPostRedisplay();
}
void clearLevelUpMessage(int value) {
    myGame.levelUpMsg = false;
    glutPostRedisplay();
}
void display(void)
{
    /// Setting up Background color
    glClear(GL_COLOR_BUFFER_BIT );
    glClearColor(0.172, 0.172, 0.498, 1.0);

    // Set text color to white
    glColor3f(1.0, 1.0, 1.0);

    // Render text at specific locations
    renderBitmapString(365.0f, 25.0f, GLUT_BITMAP_HELVETICA_18, "Score");
    renderBitmapString(370.0f, 175.0f, GLUT_BITMAP_HELVETICA_18, "Next");
    if( myGame.gameOver) {
        renderBitmapString(320.0f, 450.0f, GLUT_BITMAP_HELVETICA_18, "GAME OVER");
    }

    // Display current level
    string levelText = "Level: " + to_string(myGame.level);
    renderBitmapString(365.0f, 450.0f, GLUT_BITMAP_HELVETICA_18, levelText);

    // Display LEVEL UP message if level increased
    if (myGame.levelUpMsg) {
        renderBitmapString(365.0f, 500.0f, GLUT_BITMAP_HELVETICA_18, "LEVEL UP!");
        glutTimerFunc(5000,clearLevelUpMessage,0);
    }

    Color lightBlue(59.0f / 255.0f, 85.0f / 255.0f, 162.0f / 255.0f, 1.0f);
    DrawRectangleRounded(320.0f, 55.0f, 170.0f, 60.0f, 0.3f, 6, lightBlue ); // lightBlue color

    // Convert score to string
    string scoreText = to_string( myGame.score );
    ll width = 0;
    for (char c : scoreText) {
        width += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, c);
    }

    // Calculate the position for centering
    float x = 320 + (170 - width) / 2.0f;
    float y = 90;

    // Draw text
    float textColor[3] = {1.0f, 1.0f, 1.0f}; // White color
    drawText(scoreText, x, y, GLUT_BITMAP_HELVETICA_18, textColor);

    DrawRectangleRounded(320.0f, 215.0f, 170.0f, 180.0f, 0.3f, 6, lightBlue ); // lightBlue color
    myGame.draw();

    glutSwapBuffers();
    return ;
}
int main(int argc, char ** argv)
{
	glutInit( & argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
	glutInitWindowSize(500, 620);
	glutInitWindowPosition(500, 100);
    glutCreateWindow("Tetris Game");
	myInit ();
	glutDisplayFunc(display);
	glutKeyboardFunc(handleInput);
	glutSpecialFunc(handleSpecialInput);
    glutTimerFunc(myGame.timerInterval, update, 0);
    glutMainLoop();
    return 0;
}
