#include "raylib.h"
#include "grid.h"
#include "entities.h"
#include <stdlib.h>

double speed = .0667;
double lastUpdateTime = 0;
int lastUpdateDirection;
int lastUpdateLength = 0;

Texture2D score_title, score_value;

/* Passes value for collision detection when update is run */
int updateAll();

void fetchUserInput();

void drawScore();

int main(){

    /* */

    InitWindow(CELL_PXL * GRID_SIZE, (CELL_PXL * GRID_SIZE) + SCORE_MARGIN, "SNAKE");

    // Initialization / setup functions (prepare for entry to game loop)
    initializeGrid();
    initializeSnake();
    initializeFood();

    SetTargetFPS(60);
    lastUpdateTime = GetTime();
    while(updateAll() && !WindowShouldClose()){

        BeginDrawing();
            drawScore();
            fetchUserInput();
            drawGrid();

        EndDrawing();
    }

    /* Application was closed */
    if(WindowShouldClose()){
        exit(0);
    }

    /* Game Over: Kill Snake */
    killSnake();

    while(!WindowShouldClose()){
        BeginDrawing();
        drawGrid();
        EndDrawing();
    }
}

int updateAll(){

    /* Causes jittering-refresh */
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= speed){
        lastUpdateTime = currentTime;

        /* Prevents opposite direction traversal */
        lastUpdateDirection = snake_direction;

        /* Collision detected */
        if(!updateSnake()){
            return 0;
        }
        emptyGrid();
        plotSnake();
        updateFood();
    }
    return 1;
}

void fetchUserInput(){

    if(IsKeyPressed(KEY_UP)){
        if(lastUpdateDirection == SNAKE_DOWN){
            return;
        }
        snake_direction = SNAKE_UP;
    }
    else if(IsKeyPressed(KEY_DOWN)){
        if(lastUpdateDirection == SNAKE_UP){
            return;
        }
        snake_direction = SNAKE_DOWN;
    }
    else if(IsKeyPressed(KEY_RIGHT)){
        if(lastUpdateDirection == SNAKE_LEFT){
            return;
        }
        snake_direction = SNAKE_RIGHT;
    }
    else if(IsKeyPressed(KEY_LEFT)){
        if(lastUpdateDirection == SNAKE_RIGHT){
            return;
        }
        snake_direction = SNAKE_LEFT;
    }
}

void drawScore(){

    DrawRectangleLines(0, 0, GRID_SIZE * CELL_PXL, SCORE_MARGIN, WHITE);
    
}