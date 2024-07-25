#ifndef GRID_H
    #define GRID_H

    #include "raylib.h"

    /* Grid-element IDs */
    #define GRID_ID_EMPTY ((char) 0)
    #define GRID_ID_BODY ((char) 1)
    #define GRID_ID_FOOD ((char) 2)
    #define GRID_ID_DEAD ((char) 3)

    /* ID Colors */
    #define ID_EMPTY_COLOR CLITERAL(Color){ 0, 0, 0, 255 } //Black
    #define ID_BODY_COLOR CLITERAL(Color){ 0, 228, 48, 255 } //Green
    #define ID_FOOD_COLOR CLITERAL(Color){ 230, 41, 55, 255 } //Red
    #define ID_DEAD_COLOR CLITERAL(Color){ 76, 63, 47, 255 } //Dark Brown
    extern Color Grid_ID_Colors[4];

    /* Grid size / Pixels per cell */
    #define GRID_SIZE 16
    #define CELL_PXL 25
    #define SCORE_MARGIN 100

    /* Element grid */
    extern char Grid[GRID_SIZE][GRID_SIZE];

    // ! MUST BE CALLED BEFORE ANY grid.h FUNC / VAR IS USED
    void initializeGrid();

    /* Draws elements on grid using defined colors */
    void drawGrid();

    /* Sets all elements of the grid to empty */
    void emptyGrid();

    /* Allows for looping. Gives next coordinate if input is out-of-bounds */
    int inGrid(int n);

    /* Returns 1 if coordinate is in bounds, 0 if not */
    int isInGrid(int x, int y);
#endif