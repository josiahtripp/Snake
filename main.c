#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#ifndef NULL
    #define NULL (void*) 0
#endif

int global_snake_speed = 100;
Texture2D head_texture[4];

void initialize_snake(int* length, Vector2 body[], Vector2* velocity);

Vector2 genRandCoord();

void print_snake(int length, Vector2 body[], Vector2 velocity);

void updateSnakeLocation(Vector2 body[], Vector2 velocity);

void loadTextures();

void update_velocity(Vector2* velocity);

int main(){

    Vector2 snake_body[256], head_velocity;
    int snake_length;

    srand(time(NULL));

    /* add snake head component */
    initialize_snake(&snake_length, snake_body, &head_velocity);

    /* Initialize window */
    InitWindow(800, 800, "snake");

    loadTextures();

    SetTargetFPS(165);
    while(!WindowShouldClose()){
        updateSnakeLocation(snake_body, head_velocity);
        print_snake(snake_length, snake_body, head_velocity);
        update_velocity(&head_velocity);
    }

    return 0;
}

void initialize_snake(int* length, Vector2 body[], Vector2* velocity){

    *length = 1;
    body[0] = genRandCoord();
    
    velocity->x = 0;
    velocity->y = 0;
}

Vector2 genRandCoord(){

    Vector2 randVec2 = {

        (float) 50*(rand() % 16),
        (float) 50*(rand() % 16)
    };
    return randVec2;
}

void print_snake(int length, Vector2 body[], Vector2 velocity){

    BeginDrawing();
    ClearBackground(BLACK);

    /* Draw snake head */
    if(velocity.x > 0){

        DrawTexture(head_texture[1], body[0].x, body[0].y, WHITE);
    }
    else if(velocity.x < 0){

        DrawTexture(head_texture[3], body[0].x, body[0].y, WHITE);
    }
    else if(velocity.y > 0){

        DrawTexture(head_texture[2], body[0].x, body[0].y, WHITE);
    }
    else{

        DrawTexture(head_texture[0], body[0].x, body[0].y, WHITE);
    }
    EndDrawing();
}

void updateSnakeLocation(Vector2 body[], Vector2 velocity){

    body[0].x += velocity.x * global_snake_speed * GetFrameTime();
    body[0].y += velocity.y * global_snake_speed * GetFrameTime();
}

void loadTextures(){

    Image snake_head_image = LoadImage("Snake_head.png");
    head_texture[0] = LoadTextureFromImage(snake_head_image);

    for(int i = 1; i < 4; i++){
        ImageRotateCW(&snake_head_image);
        head_texture[i] = LoadTextureFromImage(snake_head_image);
    }
}

void update_velocity(Vector2* velocity){

    if(IsKeyPressed(KEY_UP)){

        velocity->x = 0;
        velocity->y = -1;
    }
    else if(IsKeyPressed(KEY_DOWN)){

        velocity->x = 0;
        velocity->y = 1;
    }
    else if(IsKeyPressed(KEY_RIGHT)){

        velocity->x = 1;
        velocity->y = 0;
    }
    else if(IsKeyPressed(KEY_LEFT)){

        velocity->x = -1;
        velocity->y = 0;
    }
}