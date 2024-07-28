#ifndef AUDIO_H
    #define AUDIO_H

    #include "raylib.h"

    #define SOUND_ID_START 0
    #define SOUND_ID_MOVE 1
    #define SOUND_ID_ATE 2
    #define SOUND_ID_END 3

    #define ID_START_FILE "game_start.ogg"
    #define ID_MOVE_FILE "change_direction.ogg"
    #define ID_ATE_FILE "ate_food.ogg"
    #define ID_END_FILE "game_end.ogg"

    #define AUDIO_PATH "resources/audio/"
    #define WHOLE_PATH_SIZE 50

    /* Sound effects used in-game */
    extern Sound game_sounds[4];

    /* Loads sounds effects from audio files */
    void loadSounds();

    /* Plays sounds - prevents overlapping */
    void playSoundEffect(int sound_ID);

    /* Unloads all sounds from RAM */
    void unloadAllSounds();
#endif