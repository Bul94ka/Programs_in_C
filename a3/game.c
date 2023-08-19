#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"
#include "game.h"

// Start is called one in the beginning
void* init_game(){
    // Allocate memory for the state
    struct game* st = calloc(1,(sizeof(struct game)));
    // Initialize state
    st->mousex = 5;
    st->mousey = 5;
    st->catx = 0;
    st->caty = 0;
    st->catx_position = 15;
    st->caty_position = 15;
    // Store pointer to the state to the world variable
    return st;
}

// Step is called in a loop once in interval.
// It should modify the state and draw it.
int game_event(struct event* event,void* game){
    // Get state pointer
    struct game* state = game;
    char msg[200];
    sprintf(msg,"%d",event->type);
    set_message(msg,10,0);
    if ( event->type == EVENT_ESC){
        // Non zero means finish the loop and stop the game.
        return 1;
    }
    // Read game variable and update the  eventstate

    // Is mouse caught ?
    if ((state->caty_position == state->mousey) && (state->catx_position == state->mousex)){
        clear_screen();
        set_message("HAM",12,13);
        return 0;
    }
    else if(event->type == EVENT_TIMEOUT) {
        // Move cat
        state->catx_position += state->catx;
        state->caty_position += state->caty;
        int cx = state->catx_position + state->catx;
        int cy = state->caty_position + state->caty;
        if (cx < 0 || cy < 0 || cx > event->width || cy > event->height){

        }
        else {
            state->catx_position = cx;
            state->caty_position = cy;
        }

        state->catx_position += state->catx;
        state->caty_position += state->caty;
        state->caty_position += state->caty;
        // random mouse movement
        int m = rand() % 6;
        if (m == 0){
            state->mousey -= 1;
        }
        else if (m == 1){
            state->mousey += 1;
        }
        else if (m == 2){
            state->mousex -= 1;
        }
        else if (m == 3){
            state->mousex += 1;
        }
        // Je myska mimo plochy
    }
    else if (event->type == EVENT_KEY){
        // Move cat according to keyboard
        if ( event->key == KEY_UP){
            state->catx = 0;
            state->caty = -1;
        }
        else if ( event->key == KEY_DOWN){
            state->catx = 0;
            state->caty = 1;
        }
        else if ( event->key == KEY_LEFT){
            state->catx = -1;
            state->caty = 0;
        }
        else if ( event->key == KEY_RIGHT){
            state->catx = +1;
            state->caty = 0;
        }
    }
	// Draw world state 
    //
    // Draw cat
    clear_screen();
    set_color_cell('c',state->catx_position,state->caty_position,COLOR_YELLOW,COLOR_RED);
    set_color_cell('-',state->catx_position-1,state->caty_position,COLOR_YELLOW,COLOR_GREEN);
    //set_cell('c',state->catx_position,state->caty_position);
    // Draw mouse
    set_cell('m',state->mousex,state->mousey);
    set_message( state->message,1,0);
    return 0;
}

