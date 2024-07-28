#include "raylib.h"
#include "audio.h"
#include <string.h>

/* Holds loaded sounds */
Sound game_sounds[4];

/* Clears and resets file-path string (used for init) */
static void resetPathString(char* str);

/* Stops all sounds currently playing */
static void stopAllSounds();

void loadSounds(){

    /* Load sounds from files */
    char file_name[WHOLE_PATH_SIZE];

    resetPathString(file_name);
    game_sounds[SOUND_ID_START] = LoadSound(strcat(file_name, ID_START_FILE));
    resetPathString(file_name);
    game_sounds[SOUND_ID_MOVE] = LoadSound(strcat(file_name, ID_MOVE_FILE));
    resetPathString(file_name);
    game_sounds[SOUND_ID_ATE] = LoadSound(strcat(file_name, ID_ATE_FILE));
    resetPathString(file_name);
    game_sounds[SOUND_ID_END] = LoadSound(strcat(file_name, ID_END_FILE));

    /* Set sound volume */
    SetSoundVolume(game_sounds[SOUND_ID_MOVE], 0.5);
}

void playSoundEffect(int sound_ID){

    switch (sound_ID){

        case SOUND_ID_START:
            /* Start-sound has highest precedence */
            stopAllSounds();
            PlaySound(game_sounds[sound_ID]);
        break;

        case SOUND_ID_MOVE:
            /* If either other possible sound is playing. Move sound has lowest precedence */
            if(IsSoundPlaying(game_sounds[SOUND_ID_START]) || IsSoundPlaying(game_sounds[SOUND_ID_ATE])){
                break;
            }
            PlaySound(game_sounds[sound_ID]);
        break;

        case SOUND_ID_ATE:
            /* Eat-sound has lower precedence than start sound */
            if(IsSoundPlaying(game_sounds[SOUND_ID_START])){
                break;
            }
            StopSound(game_sounds[SOUND_ID_MOVE]);
            PlaySound(game_sounds[sound_ID]);
        break;

        case SOUND_ID_END:
            stopAllSounds();
            PlaySound(game_sounds[sound_ID]);
        break;
    }
}

void unloadAllSounds(){

    for(int i = 0; i < 4; i++){
        UnloadSound(game_sounds[i]);
    }
}

static void stopAllSounds(){

    for(int i = 0; i < 4; i++){
        StopSound(game_sounds[i]);
    }
}

static void resetPathString(char* str){

    memset(str, 0, WHOLE_PATH_SIZE);
    strcpy(str, AUDIO_PATH);
}