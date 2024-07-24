#include "raylib.h"
#include "snake.h"
#include <stdlib.h>
#include <time.h>

int main(){

    /* Set seed for random number generation */
    srand(time(NULL));

    /* Preliminary setup / initialization */
    loadGridColors();
    clearGrid();
    initializeSnake();

    InitWindow(PXL_PER_CELL * GRID_SIZE, PXL_PER_CELL * GRID_SIZE, "SNAKE");

    SetTargetFPS(5);
    while(!WindowShouldClose()){

        if(generate_food){
            placeFood();
        }
        updateGrid();

        printGrid();
        fetchUserInput();
        shiftSnakeBody();
        if(shiftSnakeHead()){

        }
    }
}

void clearGrid(){

    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            grid[i][j] = SNAKE_EMPTY;
        }
    }
}

void printGrid(){

    BeginDrawing();
    ClearBackground(grid_colors[SNAKE_EMPTY]);
    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            if(grid[i][j] != SNAKE_EMPTY){
                DrawRectangle(j * PXL_PER_CELL, i * PXL_PER_CELL, PXL_PER_CELL, PXL_PER_CELL, grid_colors[(int)grid[i][j]]);
            }
        }
    }
    EndDrawing();
}

void loadGridColors(){

    grid_colors[SNAKE_EMPTY] = BLACK;
    grid_colors[SNAKE_BODY] = GREEN;
    grid_colors[SNAKE_FOOD] = RED;
    grid_colors[SNAKE_DEAD] = DARKBROWN;
}

void initializeSnake(){

    snake_length = 0;
    snake_body[0].x = rand() % GRID_SIZE;
    snake_body[0].y = rand() % GRID_SIZE;
    snake_direction = rand() % 4;
}

void updateGrid(){

    clearGrid();
    grid[food.y][food.x] = SNAKE_FOOD;

    for(int i = 0; i < snake_length; i++){
        grid[snake_body[i].y][snake_body[i].x] = SNAKE_BODY;
    }
}

void fetchUserInput(){

    if(IsKeyDown(KEY_UP)){
        if(snake_direction == SNAKE_DOWN){
            return;
        }
        snake_direction = SNAKE_UP;
    }
    else if(IsKeyDown(KEY_DOWN)){
        if(snake_direction == SNAKE_UP){
            return;
        }
        snake_direction = SNAKE_DOWN;
    }
    else if(IsKeyDown(KEY_RIGHT)){
        if(snake_direction == SNAKE_LEFT){
            return;
        }
        snake_direction = SNAKE_RIGHT;
    }
    else if(IsKeyDown(KEY_LEFT)){
        if(snake_direction == SNAKE_RIGHT){
            return;
        }
        snake_direction = SNAKE_LEFT;
    }
}

void shiftSnakeBody(){

    for(int i = snake_length - 1; i > 0; i--){

        /* Placeholder for appending to snake */
        if(i == snake_length - 1){
            tail.x = snake_body[i].x;
            tail.y = snake_body[i].y;
        }

        snake_body[i].x = snake_body[i-1].x;
        snake_body[i].y = snake_body[i-1].y;
    }
}

int shiftSnakeHead(){

    if(snake_direction == SNAKE_DOWN){
        if(grid[ovrF(snake_body[0].y + 1)][snake_body[0].x] != SNAKE_EMPTY){
            if(grid[ovrF(snake_body[0].y + 1)][snake_body[0].x] == SNAKE_FOOD){

                addToSnake();
            }
            return 0;
        }
        snake_body[0].y = ovrF(snake_body[0].y + 1);
    }
    else if (snake_direction == SNAKE_UP){
        if(grid[ovrF(snake_body[0].y - 1)][snake_body[0].x] != SNAKE_EMPTY){
            if(grid[ovrF(snake_body[0].y - 1)][snake_body[0].x] == SNAKE_FOOD){

                addToSnake();
            }
            return 0;
        }
        snake_body[0].y = ovrF(snake_body[0].y - 1);
    }
    else if (snake_direction == SNAKE_RIGHT){
        if(grid[snake_body[0].y][ovrF(snake_body[0].x + 1)] != SNAKE_EMPTY){
            if(grid[snake_body[0].y][ovrF(snake_body[0].x + 1)] == SNAKE_FOOD){

                addToSnake();
                return 1;
            }
            return 0;
        }
        snake_body[0].x = ovrF(snake_body[0].x + 1);
    }
    else if (snake_direction == SNAKE_LEFT){
        if(grid[snake_body[0].y][ovrF(snake_body[0].x - 1)] != SNAKE_EMPTY){
            if(grid[snake_body[0].y][ovrF(snake_body[0].x - 1)] == SNAKE_FOOD){

                addToSnake();
                return 1;
            }
            return 0;
        }
        snake_body[0].x = ovrF(snake_body[0].x - 1);
    }
    return 1;
}

int ovrF(int n){

    if(n < 0){
        return GRID_SIZE - 1;
    }
    return n % GRID_SIZE;
}

void addToSnake(){

    snake_body[snake_length].x = tail.x;
    snake_body[snake_length].y = tail.y;
    snake_length++;
    generate_food = 1;
}

void placeFood(){

    Coord valid_coords[256];
    int quantity = 0;

    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            if(grid[i][j] == SNAKE_EMPTY){
                valid_coords[quantity].y = i; 
                valid_coords[quantity].x = j;
                quantity++;
            }
        }
    }

    int randInt = rand() % quantity;
    food.x = valid_coords[randInt].x;
    food.y = valid_coords[randInt].y;

    generate_food = 0;
}