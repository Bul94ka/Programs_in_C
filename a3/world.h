#ifndef _WORLD_H_
#define _WORLD_H_

#include <curses.h>

/**
 * World represented as a rectangular matrix of colorful characters.
 * 
 * Point [0,0] is displayed the upper left corner of the screen.
 * 
 */

enum event_type {
    EVENT_START,
    EVENT_TIMEOUT,
    EVENT_KEY,
    EVENT_MOUSE,
    EVENT_RESIZE,
    EVENT_ESC,
    EVENT_END,
};

struct event {
    /**
     * Last width of the screen.
     */
    int width;
    /**
     * Last height of the screen.
     */
    int height;
    /**
     * Last pressed key or Curses event.
     *
     * Special event  values:
     * ERR if timeout,
     * KEY_RESIZE if screen resize
     * KEY_EVENT, other event,
     * KEY_MOUSE, mouse clicked
     *
     * Key values:
     *
     * ' ' Space
     * KEY_DOWN Arrow down
     * KEY_UP Arrow up
     * KEY_LEFT Arrow left
     * KEY_RIGHT Arrow right
     * KEY_A1 Upper left of keypad
     * KEY_A3 Upper right of keypad
     * KEY_B2 Center of keypad
     * KEY_C1 Lower left of keypad
     * KEY_C3 Lower right of keypad
     *
     * KEY_ENTER
     * KEY_BACKSPACE
     */
    int key;
    int alt_key;
    enum event_type type;
    int mouse_x;
    int mouse_y;
    int mouse_left;
    int mouse_right;
    int mouse_middle;
    long int time_ms;
};

/**
 * Sets cell to a state.
 * @param event 
 * @param x coordinate of cell
 * @param y coordinate of cell
 * @param new state of the cell
 */
void set_cell(int character,int x,int y);

/**
 * COLOR_BLACK   0
 * COLOR_RED     1
 * COLOR_GREEN   2
 * COLOR_YELLOW  3
 * COLOR_BLUE    4
 * COLOR_MAGENTA 5
 * COLOR_CYAN    6
 * COLOR_WHITE   7
 */

#define COLOR_COUNT 8

void set_color_cell(int character,int x,int y,short front_color,short back_color);


/**
 *
 * @param event
 * @param number of commandline arguments
 * @param init_world
 * @param destroy_world
 *
 * void init_world(struct event* w);
 * Initializes user state.
 * Free user state.
 * @param event
 */

int start_world(void* (*init_game)(),int (*world_event)(struct event* event,void* game),void (*destroy_game)(void* game));

void game_speed(int value);

void set_message(const char* message,int x,int y);
void clear_screen();

#endif
