#include "grid.h"
#include "raylib.h"

Color Grid_ID_Colors[4];

char Grid[GRID_SIZE][GRID_SIZE];

void initializeGrid(){

    /* Load ID Colors */
    Grid_ID_Colors[0] = ID_EMPTY_COLOR;
    Grid_ID_Colors[1] = ID_BODY_COLOR;
    Grid_ID_Colors[2] = ID_FOOD_COLOR;
    Grid_ID_Colors[3] = ID_DEAD_COLOR;

    /* Set grid to empty */
    emptyGrid();
}

void drawGrid(){

    /* Runs through all cells. Prints color at position corresponding to cell */
    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            
            DrawRectangle(j*CELL_PXL, (i*CELL_PXL) + SCORE_MARGIN, CELL_PXL, CELL_PXL,
             Grid_ID_Colors[(int)Grid[i][j]]);
        }
    }
}

void emptyGrid(){

    /* Sets every valid cell to empty */
    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            Grid[i][j] = GRID_ID_EMPTY;
        }
    }
}

int inGrid(int n){

    if(n < 0){
        return GRID_SIZE - 1;
    }
    return n % GRID_SIZE;
}

int isInGrid(int x, int y){

    if((-1 < x) && (x < GRID_SIZE) && (-1 < y) && (y < GRID_SIZE)){
        return 1;
    }
    return 0;
}