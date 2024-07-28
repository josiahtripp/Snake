#include "raylib.h"
#include "gui.h"
#include "grid.h"
#include <stdio.h>

Texture2D static_textures[3];
Texture2D score_texture;

/* Draws score margin segment and outline */
static void drawScoreMargin();

void updateScoreTexture(int score, int fontSize);

void loadStaticTextures(){

    static_textures[TEXTURE_ID_MENU] = 
        LoadTextureFromImage(ImageText("SNAKE", CELL_PXL * 2, WHITE));
    static_textures[TEXTURE_ID_MENUSUBTITLE] = 
        LoadTextureFromImage(ImageText("Press enter to start...", CELL_PXL * 4/5, WHITE));
    static_textures[TEXTURE_ID_GAMEOVER] = 
        LoadTextureFromImage(ImageText("Game Over", CELL_PXL * 6/5, WHITE));
}

void drawTitleScreen(){

    //const int win_H = (GRID_SIZE * CELL_PXL) + SCORE_MARGIN;
    //const int win_W = GRID_SIZE * CELL_PXL;

    ClearBackground(BLACK);
    DrawTexture(static_textures[TEXTURE_ID_MENU], 
        (WIN_W - static_textures[TEXTURE_ID_MENU].width)/2, 
        (WIN_H - static_textures[TEXTURE_ID_MENU].height)/3, WHITE);
    DrawTexture(static_textures[TEXTURE_ID_MENUSUBTITLE], 
        (WIN_W - static_textures[TEXTURE_ID_MENUSUBTITLE].width)/2,
        (WIN_H - static_textures[TEXTURE_ID_MENUSUBTITLE].height)/2, WHITE);
    DrawRectangleLines(0, 0, WIN_W, WIN_H, WHITE);
}

void drawScore(){

    /* Draw score */
    drawScoreMargin();
    DrawTexture(score_texture, (WIN_W-score_texture.width)/2, 
        (SCORE_MARGIN-score_texture.height)/2, WHITE);
}

void drawGameoverScreen(){

    drawScoreMargin();
    DrawTexture(static_textures[TEXTURE_ID_GAMEOVER],
        (WIN_W - static_textures[TEXTURE_ID_GAMEOVER].width)/2,
        (SCORE_MARGIN-static_textures[TEXTURE_ID_GAMEOVER].height)/2, WHITE);
    DrawTexture(score_texture, (WIN_W - score_texture.width)/2, 
        ((SCORE_MARGIN-score_texture.height)/2) 
        + static_textures[TEXTURE_ID_GAMEOVER].height, WHITE);
}

static void drawScoreMargin(){

    DrawRectangle(0, 0, WIN_W, SCORE_MARGIN, BLACK);
    DrawRectangleLines(0, 0, WIN_W, SCORE_MARGIN, WHITE);
}

void updateScoreTexture(int score, int fontSize){
    
    /* Unload old texture */
    UnloadTexture(score_texture);

    /* Generate string */
    static char score_str[16];
    sprintf(score_str, "Score: %d", score);
    
    /* Generate image */
    static Image tmp_img;
    tmp_img = ImageText(score_str, fontSize, WHITE);

    /* Free image and old texture */
    score_texture = LoadTextureFromImage(tmp_img);
    UnloadImage(tmp_img);
}

void unloadAllTextures(){

    for(int i = 0; i < 3; i++){
        UnloadTexture(static_textures[i]);
    }
    UnloadTexture(score_texture);
}