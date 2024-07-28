#ifndef GUI_H
    #define GUI_H

    #include "raylib.h"
    #include "grid.h"

    #define TEXTURE_ID_MENU 0
    #define TEXTURE_ID_MENUSUBTITLE 1
    #define TEXTURE_ID_GAMEOVER 2

    #define SCORE_MARGIN 140
    #define WIN_W (GRID_SIZE * CELL_PXL)
    #define WIN_H ((GRID_SIZE * CELL_PXL) + SCORE_MARGIN)

    /* Game screens and titles. not altered once loaded */
    extern Texture2D static_textures[3];

    /* Dynamic texture, updates with score change */
    extern Texture2D score_texture;

    /* Loads all static texures / screens used in-game */
    void loadStaticTextures();

    /* Draws game title-screen */
    void drawTitleScreen();

    /* Draws game score */
    void drawScore();

    /* Generates an updated score texture and deallocates old texture */
    void updateScoreTexture(int score, int fontSize);

    /* Draws end-of-game screen with final score */
    void drawGameoverScreen();

    /* Unloads all textures from VRAM */
    void unloadAllTextures();

#endif