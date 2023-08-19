#ifndef _GAME_H_INCLUDE_
#define _GAME_H_INCLUDE_
#include "world.h"

// Set of variables that expresses state of the game.
// 
struct game {
    // X speed of the cat
    int catx;
    // Y speed  of the cat
    int caty;
    // X position of the cat
    int catx_position;
    // Y opsition of the cat
    int caty_position;;
    // X position of the mouse
    int mousex;
    // Y position of the mouse
    int mousey;
    // Funky message
    char message[100];
};

// Returns pointer to  newly allocated state
void* init_game();

// Changes world according to the game state (pressed key, screen size or other event)
int game_event(struct event* event,void* game);

#endif
