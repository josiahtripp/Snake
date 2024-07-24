#ifndef SNAKE_H
    #define SNAKE_H

    #include "raylib.h"

    /* Snake head directions */
    #define SNAKE_UP 0
    #define SNAKE_RIGHT 1
    #define SNAKE_DOWN 2
    #define SNAKE_LEFT 3

    /* Display-grid IDs */
    #define SNAKE_EMPTY ((char) 0)
    #define SNAKE_BODY ((char) 1)
    #define SNAKE_FOOD ((char) 2)
    #define SNAKE_DEAD ((char) 3)

    /* Grid / window size */
    #define GRID_SIZE 16
    #define PXL_PER_CELL 25

    typedef struct Coord {

        int x;
        int y;
    } Coord;

    /* Grid used to print to the screen */
    char grid[GRID_SIZE][GRID_SIZE];
    Coord snake_body[256];
    Coord food, tail;
    Texture endText;
    int snake_direction;
    int snake_length;
    int generate_food = 1;

    /* Associated grid ID textures */
    Color grid_colors[5];

    /* Set all grid positions to SNAKE_EMPTY */
    void clearGrid();

    /* Prints all current value of the grid */
    void printGrid();

    /* Loads colors for printing grid */
    void loadGridColors();

    /* Assigns initial value to length var and snake head location */
    void initializeSnake();

    /* Update Grid with snake location */
    void updateGrid();

    /* Changes snake direction */
    void fetchUserInput();

    /* Shifts snake body forward */
    void shiftSnakeBody();

    /* Shifts head forward */
    int shiftSnakeHead();

    /* keeps coords within confines */
    int ovrF(int n);

    /* Adds snake-body to chain*/
    void addToSnake();

    /* Place snake food at a random, valid location */
    void placeFood();

    /* Loads end-game message and associated textures */
    void initializeEnd();
#endif