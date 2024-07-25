#include "raylib.h"
#include "grid.h"
#include "entities.h"
#include <stdlib.h>
#include <stdio.h>

double speed = .0667;
double lastUpdateTime;
int lastUpdateDirection;
int lastUpdateLength;

Texture2D score, game_over, menu, menu_subtitle;

/* Passes value for collision detection when update is run */
int updateAll();

void fetchUserInput();

void drawScore();

void clearMargin();

void drawMenu();

int main(){

    InitWindow(CELL_PXL * GRID_SIZE, (CELL_PXL * GRID_SIZE) + SCORE_MARGIN, "SNAKE");
    SetTargetFPS(60);

    /* Load initial textures */
    game_over = LoadTextureFromImage(ImageText("Game Over", 30, WHITE));
    menu = LoadTextureFromImage(ImageText("SNAKE", 50, WHITE));
    menu_subtitle = LoadTextureFromImage(ImageText("Press enter to start...", 20, WHITE));

    while(!WindowShouldClose()){

        // Initialization / setup functions (prepare for entry to game loop)
        initializeGrid();
        initializeSnake();
        initializeFood();

        lastUpdateTime = 0;
        lastUpdateLength = 0;

        /* Wait for key press to start game */
        while(!IsKeyPressed(KEY_ENTER) && !WindowShouldClose()){
            BeginDrawing();
                drawMenu();
            EndDrawing();
        }

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

        /* Regen smaller final-score texture */
            char score_str[256];
            sprintf(score_str, "Score: %d", snake_length - 2);
            score = LoadTextureFromImage(ImageText(score_str, 20, WHITE));

        while(!WindowShouldClose() && !IsKeyPressed(KEY_ENTER)){
            BeginDrawing();
                clearMargin();
                DrawTexture(game_over, ((GRID_SIZE * CELL_PXL)-game_over.width)/2, (SCORE_MARGIN-game_over.height)/2, WHITE);
                DrawTexture(score, ((GRID_SIZE * CELL_PXL)-score.width)/2, ((SCORE_MARGIN-score.height)/2)+game_over.height, WHITE);
                drawGrid();
            EndDrawing();
        }
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

    /* Regenerate score texture if score has changed */
    if(snake_length != lastUpdateLength){

        char score_str[256];
        sprintf(score_str, "Score: %d", snake_length - 2);
        score = LoadTextureFromImage(ImageText(score_str, 30, WHITE));

        /* Redraw */
        clearMargin();
        DrawTexture(score, ((GRID_SIZE * CELL_PXL)-score.width)/2, (SCORE_MARGIN-score.height)/2, WHITE);
    }
}

void clearMargin(){

    DrawRectangle(0, 0, GRID_SIZE * CELL_PXL, SCORE_MARGIN, BLACK);
    DrawRectangleLines(0, 0, GRID_SIZE * CELL_PXL, SCORE_MARGIN, WHITE);
}

void drawMenu(){

    ClearBackground(BLACK);
    DrawTexture(menu, ((GRID_SIZE * CELL_PXL)-menu.width)/2, ((GRID_SIZE * CELL_PXL) + SCORE_MARGIN - menu.height)/3, WHITE);
    DrawTexture(menu_subtitle, ((GRID_SIZE * CELL_PXL)-menu_subtitle.width)/2, ((GRID_SIZE * CELL_PXL) + SCORE_MARGIN - menu.height)/2, WHITE);
    DrawRectangleLines(0, 0, GRID_SIZE * CELL_PXL, (GRID_SIZE * CELL_PXL) + SCORE_MARGIN, WHITE);
}