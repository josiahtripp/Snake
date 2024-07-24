#include "raylib.h"
#include "snake.h"
#include <stdlib.h>
#include <time.h>

int main(){

    /* Set seed for random number generation */
    srand(time(NULL));

    InitWindow(PXL_PER_CELL * GRID_SIZE, PXL_PER_CELL * GRID_SIZE, "SNAKE");

    /* Preliminary setup / initialization */
    loadGridColors();
    clearGrid();
    initializeSnake();
    initializeEnd();

    SetTargetFPS(60);
    float invspeed = .1;
    float cont = invspeed;
    int contDir;

    updateGrid();
    if(generate_food){
        placeFood();
    }

    while(!WindowShouldClose()){

        BeginDrawing();
        updateGrid();
        printGrid();

        if(contDir == snake_direction){
            fetchUserInput();
        }

        if(cont >= invspeed){
            cont = 0;
            shiftSnakeBody();
            updateGrid();
            if(!shiftSnakeHead()){

                break;
            }
            addToSnake();
            if(generate_food){
                placeFood();
            }
            contDir = snake_direction;
        }
        cont += GetFrameTime();
        EndDrawing();
    }
    for(int i = 0; i < GRID_SIZE * GRID_SIZE; i++){

        if(grid[0][i] == SNAKE_BODY){
            grid[0][i] = SNAKE_DEAD;
        }
    }

    while(!WindowShouldClose()){

        BeginDrawing();
        printGrid();
        EndDrawing();
    }
}

void clearGrid(){

    for(int i = 0; i < GRID_SIZE * GRID_SIZE; i++){
        grid[0][i] = SNAKE_EMPTY;
    }
}

void printGrid(){

    ClearBackground(grid_colors[SNAKE_EMPTY]);
    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            if(grid[i][j] != SNAKE_EMPTY){
                DrawRectangle(j * PXL_PER_CELL, i * PXL_PER_CELL, PXL_PER_CELL, PXL_PER_CELL, grid_colors[(int)grid[i][j]]);
            }
        }
    }
}

void loadGridColors(){

    grid_colors[SNAKE_EMPTY] = BLACK;
    grid_colors[SNAKE_BODY] = GREEN;
    grid_colors[SNAKE_FOOD] = RED;
    grid_colors[SNAKE_DEAD] = DARKBROWN;
}

void initializeSnake(){

    snake_length = 1;
    snake_body[0].x = rand() % GRID_SIZE;
    snake_body[0].y = rand() % GRID_SIZE;
    snake_direction = rand() % 4;
    food.x = 0;
    food.y = 0;
}

void updateGrid(){

    clearGrid();
    grid[food.y][food.x] = SNAKE_FOOD;

    for(int i = 0; i < snake_length; i++){
        grid[snake_body[i].y][snake_body[i].x] = SNAKE_BODY;
    }
}

void fetchUserInput(){

    if(IsKeyPressed(KEY_UP)){
        if(snake_direction == SNAKE_DOWN){
            return;
        }
        snake_direction = SNAKE_UP;
    }
    else if(IsKeyPressed(KEY_DOWN)){
        if(snake_direction == SNAKE_UP){
            return;
        }
        snake_direction = SNAKE_DOWN;
    }
    else if(IsKeyPressed(KEY_RIGHT)){
        if(snake_direction == SNAKE_LEFT){
            return;
        }
        snake_direction = SNAKE_RIGHT;
    }
    else if(IsKeyPressed(KEY_LEFT)){
        if(snake_direction == SNAKE_RIGHT){
            return;
        }
        snake_direction = SNAKE_LEFT;
    }
}

void shiftSnakeBody(){

    tail.x = snake_body[snake_length - 1].x;
    tail.y = snake_body[snake_length - 1].y;

    for(int i = snake_length - 1; i > 0; i--){

        snake_body[i].x = snake_body[i-1].x;
        snake_body[i].y = snake_body[i-1].y;
    }
}

int shiftSnakeHead(){

    if(snake_direction == SNAKE_DOWN){
        if(grid[ovrF(snake_body[0].y + 1)][snake_body[0].x] != SNAKE_BODY){
            
            snake_body[0].y = ovrF(snake_body[0].y + 1);
            return 1;   
        }
        return 0;
    }
    else if (snake_direction == SNAKE_UP){
        if(grid[ovrF(snake_body[0].y - 1)][snake_body[0].x] != SNAKE_BODY){
            
            snake_body[0].y = ovrF(snake_body[0].y - 1);
            return 1;
        }
        return 0;
    }
    else if (snake_direction == SNAKE_RIGHT){
        if(grid[snake_body[0].y][ovrF(snake_body[0].x + 1)] != SNAKE_BODY){
           
            snake_body[0].x = ovrF(snake_body[0].x + 1);
            return 1;   
        }
        return 0;
    }
    else{
        if(grid[snake_body[0].y][ovrF(snake_body[0].x - 1)] != SNAKE_BODY){
            
            snake_body[0].x = ovrF(snake_body[0].x - 1);
            return 1;
        }
        return 0;
    }
}

int ovrF(int n){

    if(n < 0){
        return GRID_SIZE - 1;
    }
    return n % GRID_SIZE;
}

void addToSnake(){

    if(grid[food.y][food.x] == SNAKE_BODY){

        snake_body[snake_length].x = tail.x;
        snake_body[snake_length].y = tail.y;
        snake_length++;
        generate_food = 1;
    }
}

void placeFood(){

    Coord valid_coords[256];
    int quantity = 0;

    for(int i = 0; i < GRID_SIZE * GRID_SIZE; i++){
        if(grid[0][i] == SNAKE_EMPTY){
            valid_coords[quantity].y = i; 
            valid_coords[quantity].x = i;
            quantity++;
        }
    }

    int randInt = rand() % quantity;
    food.y = (int) valid_coords[randInt].y / GRID_SIZE;
    food.x = valid_coords[randInt].x % GRID_SIZE;

    generate_food = 0;
}

void initializeEnd(){

    endText = LoadTextureFromImage(ImageText("GAME OVER", 30, ORANGE));
}