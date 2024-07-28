#include "raylib.h"
#include "grid.h"
#include "entities.h"
#include "audio.h"
#include "gui.h"

#define MAX_FRAME_RATE 165
#define WSC (!WindowShouldClose())

double speed = .0667;//Delay between each snake movement
double lastUpdateTime;
int lastUpdateDirection;
int lastUpdateLength;

/* Passes value for collision detection when update is run */
int updateAll();

void fetchUserInput();

void updateScore();

int main(){

    /* Window / initial application config */
    InitWindow(WIN_W, WIN_H, "SNAKE");
    InitAudioDevice();
    SetTargetFPS(MAX_FRAME_RATE);

    //Loads various game-function variables
    loadSounds();
    loadGridColors();
    loadStaticTextures();

    while(WSC){//Application Window Loop

        // Initialization / Reset
        initializeGrid();
        initializeSnake();
        initializeFood();

        // Menu
        while(!IsKeyPressed(KEY_ENTER) && WSC){
            BeginDrawing();
                drawTitleScreen();
            EndDrawing();
        }

        /* Game start: */
        playSoundEffect(SOUND_ID_START);
        lastUpdateTime = GetTime();//Prevents update from occuring right away
        lastUpdateLength = 2;//Allows initial score (0) to be drawn
        lastUpdateDirection = snake_direction;//Prevents first-interval directional glitch

        //Generate initial score Texture (0)
        updateScoreTexture(lastUpdateLength - 2, CELL_PXL * 6/5);

        // Game Loop
        while(updateAll() && WSC){

            BeginDrawing();
                fetchUserInput();
                drawScore();
                drawGrid();
            EndDrawing();
        }

        /* Game Over: */
        updateScoreTexture(lastUpdateLength - 2, CELL_PXL * 4/7);//Final score
        playSoundEffect(SOUND_ID_END);

        // Game Over screen
        while(!IsKeyPressed(KEY_ENTER) && WSC){
            BeginDrawing();
                drawGameoverScreen();
                drawGrid();
            EndDrawing();
        }
    }
    CloseWindow();
    unloadAllTextures();
    unloadAllSounds();
    return 0;
}

int updateAll(){

    /* Causes delay between frames */
    static double currentTime;
    currentTime = GetTime();

    /* Frame-delay interval has passed */
    if(currentTime - lastUpdateTime >= speed){

        lastUpdateTime = currentTime;//Resets for next interval

        /* Direction has changed */
        if(lastUpdateDirection != snake_direction){
            playSoundEffect(SOUND_ID_MOVE);
        } 

        /* Prevents opposite direction traversal */
        lastUpdateDirection = snake_direction;

        /* Update game entities - propogate change to grid */
        if(!updateSnake()){//Move snake
            killSnake();//Changes snake color
            return 0;//Collision detected
        }
        initializeGrid();//Clear grid
        plotSnake();//Redraw snake
        updateFood();//Redraw food, regen if needed

        /* Snake length has changed */
        if(snake_length != lastUpdateLength){
        
            playSoundEffect(SOUND_ID_ATE);
            lastUpdateLength = snake_length;
            updateScoreTexture(lastUpdateLength - 2, CELL_PXL * 6/5);
        }
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