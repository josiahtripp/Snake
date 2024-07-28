#include "entities.h"
#include "raylib.h"
#include "grid.h"

Coord snake_coords[256];
int snake_direction;
int snake_length;

Coord food_coords;
int need_food;

void initializeSnake(){

    /* Set initial length and randomize initial direction */
    snake_length = 2;
    snake_direction = GetRandomValue(0, 3);

    /* Randomize snake-head position */
    snake_coords[0].x = GetRandomValue(0, GRID_SIZE - 1);
    snake_coords[0].y = GetRandomValue(0, GRID_SIZE - 1);

    /* Randomize snake-body location */
    int xOffset, yOffset, randIndex[2] = {-1, 1};

    /* Ensures that random location doesn't cut across grid */
    do
    {
        /* Generate random connecting coordinate */
        xOffset = GetRandomValue(-1, 1);
        if(xOffset == 0){
            yOffset = randIndex[GetRandomValue(0, 1)];
        }
        else{
            yOffset = 0;
        }
    } while(!isInGrid(snake_coords[0].x + xOffset, snake_coords[0].y + yOffset));

    /* Assign location */
    snake_coords[1].x = snake_coords[0].x + xOffset;
    snake_coords[1].y = snake_coords[0].y + yOffset;

    /* Plot Snake */
    for(int i = 0; i < snake_length; i++){
        Grid[snake_coords[i].y][snake_coords[i].x] = GRID_ID_BODY;
    }
}

void plotSnake(){

    /* Plot snake */
    for(int i = 0; i < snake_length; i++){
        Grid[snake_coords[i].y][snake_coords[i].x] = GRID_ID_BODY;
    }
}

int updateSnake(){

    /* Holds for transfer to 2nd body-component & appending */
    Coord head_coords, tail_coords;
    head_coords.x = snake_coords[0].x;
    head_coords.y = snake_coords[0].y;

    /* Remove tail for collision detection */
    tail_coords.y = snake_coords[snake_length-1].y;
    tail_coords.x = snake_coords[snake_length-1].x;

    /* Update snake head position with direction */
    if(snake_direction == SNAKE_DOWN){
        if(Grid[inGrid(head_coords.y + 1)][head_coords.x] == GRID_ID_BODY &&//Grid-space contain snake-body
        (inGrid(head_coords.y + 1) != tail_coords.y || head_coords.x != tail_coords.x)){//Grid-space is not tail

            return 0;   
        }
        snake_coords[0].y = inGrid(snake_coords[0].y + 1);//Move snake-head down
    }
    else if (snake_direction == SNAKE_UP){
        if(Grid[inGrid(snake_coords[0].y - 1)][snake_coords[0].x] == GRID_ID_BODY &&
        (inGrid(head_coords.y - 1) != tail_coords.y || head_coords.x != tail_coords.x)){
            
            return 0;
        }
        snake_coords[0].y = inGrid(snake_coords[0].y - 1);//Move snake-head up
    }
    else if (snake_direction == SNAKE_RIGHT){
        if(Grid[snake_coords[0].y][inGrid(snake_coords[0].x + 1)] == GRID_ID_BODY &&
        (head_coords.y != tail_coords.y || inGrid(head_coords.x + 1) != tail_coords.x)){
           
            return 0;   
        }
        snake_coords[0].x = inGrid(snake_coords[0].x + 1);//Move snake-head right
    }
    else{//SNAKE_LEFT
        if(Grid[snake_coords[0].y][inGrid(snake_coords[0].x - 1)] == GRID_ID_BODY &&
        (head_coords.y != tail_coords.y || inGrid(head_coords.x - 1) != tail_coords.x)){
            
            return 0;
        }
        snake_coords[0].x = inGrid(snake_coords[0].x - 1);//Move snake-left up
    }

    /* Shift the rest of the snake components towards head */
    tail_coords.x = snake_coords[snake_length-1].x;//Store to append snake
    tail_coords.y = snake_coords[snake_length-1].y;

    for(int i = snake_length - 1; i > 1; i--){//Remaining body

        snake_coords[i].x = snake_coords[i-1].x;
        snake_coords[i].y = snake_coords[i-1].y;
    }

    snake_coords[1].x = head_coords.x;//1st body component
    snake_coords[1].y = head_coords.y;

    /* Snake ate food */
    if(Grid[snake_coords[0].y][snake_coords[0].x] == GRID_ID_FOOD){

        need_food = 1;
        snake_coords[snake_length].x = tail_coords.x;
        snake_coords[snake_length].y = tail_coords.y;
        snake_length++;
    }
    return 1;
}

void killSnake(){

    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            if(Grid[i][j] == GRID_ID_BODY){
                Grid[i][j] = GRID_ID_DEAD;
            }
        }
    }
}

void initializeFood(){
    
    need_food = 1;
    updateFood();
}

void updateFood(){

    /* Generate a new food location */
    if (need_food){

        int x, y;
        do
        {
            x = GetRandomValue(0, GRID_SIZE - 1);
            y = GetRandomValue(0, GRID_SIZE - 1);
        } while (Grid[y][x] != GRID_ID_EMPTY);
        food_coords.x = x;
        food_coords.y = y;
        need_food = 0;
    }

    /* Plot food location */
    Grid[food_coords.y][food_coords.x] = GRID_ID_FOOD;
}