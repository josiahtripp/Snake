#ifndef ENTITIES_H
    #define ENTITIES_H

    /* Snake directions */
    #define SNAKE_UP 0
    #define SNAKE_RIGHT 1
    #define SNAKE_DOWN 2
    #define SNAKE_LEFT 3

    /* Holds coordinates corresponding to grid */
    typedef struct Coord {
        int x;
        int y;
    } Coord;

    /* Snake-entity variables */
    extern Coord snake_coords[256];
    extern int snake_direction;
    extern int snake_length;

    /* Food-entity variables */
    extern Coord food_coords;
    extern int need_food;

    //MUST BE RUN BEFORE ANY SNAKE-ENTITY FUNC / VAR IS USED
    void initializeSnake();

    /* Places every snake-elemnt onto the grid */
    void plotSnake();

    /* Moves snake using snake_direction. Does nothing and returns 0 if collision is detected */
    int updateSnake();

    /* Replaces snake-ID with dead-snake-ID */
    void killSnake();

    //MUST BE RUN BEFORE ANY FOOD-ENTITY FUNC / VAR IS USED
    void initializeFood();

    /* Places food at a random valid coordinate and plots it on grid */
    void updateFood();

#endif