#include "world.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int TIMEOUT;

void abort_game(const char* message){
    endwin();
    puts(message);
    exit(1);
}

void check_bounds(const char* source,int x, int y){
    char msg[200];
    if (x < 0 || x >= COLS){
        sprintf(msg,"%s:: width %d is out of bounds (0,%d)",source,x,COLS);
        abort_game(msg);
    }
    if (y < 0 || y >= LINES){
        sprintf(msg,"%s:: height %d is out of bounds (0,%d)",source,y,LINES);
        abort_game(msg);
    }
}

void clear_screen(){
    // Clear screen
    mvaddch(0,0,' ');
    int screenchars = LINES*COLS;
    for (int j = 1; j < screenchars;j++ ){
        addch(' ');
    }
}

void game_speed(int value){
    if (value < 0){
        abort_game("world_seed:: cannot be negative\n");
    }
    TIMEOUT =value;
}

void set_message(const char* message,int x,int y) {
    int l = strlen(message);
    for (int i = 0; i < l; i++){
        check_bounds("set_message",x+i,y);
        set_cell(message[i],x+i,y);
    }
}

void assert_message(int event,const char* message){
    if (event == 0){
        abort_game(message);
    }
}


void set_cell(int character,int x,int y) {
    check_bounds("set_cell",x,y);
    set_color_cell(character,x,y,COLOR_WHITE,COLOR_BLACK);
}

void set_color_cell(int character,int x,int y,short front_color,short back_color){
    check_bounds("set_color_cell",x,y);
    if (has_colors()){
        int pair = COLOR_COUNT * front_color + back_color; 
        attron(COLOR_PAIR(pair));
        mvaddch(y,x,character);
        attroff(COLOR_PAIR(pair));
    }
    else{
        mvaddch(y,x,character);
    }
}

int start_world(void* (*init_game)(),int (*world_event)(struct event* event,void* game),void (*destroy_game)(void*)){
    srand(time(NULL));
    int r = 1;
    // Speed global variable
    TIMEOUT = 100;
    if (initscr() == NULL){
        // TODO Which Error?
        puts("Curses Error.");
        return -1;
    }
    noecho(); // Nevypisuj vstup na obrazovku
    cbreak(); // Zabudni starý vstup
    nodelay(stdscr,TRUE); // Nečakaj na stlačenie
    keypad(stdscr,TRUE); // Aktivuje šípky
    curs_set(FALSE); // Neviditeľný kurzor
    /* Get all the mouse events */
    mousemask(ALL_MOUSE_EVENTS, NULL);
    MEVENT mouse_event;
    if (has_colors()){ // Zistenie či terminál podporuje farby
        start_color();
        for (int i = 0; i < COLOR_COUNT;i++){
            for (int j = 0; j < COLOR_COUNT;j++){
                init_pair(i * COLOR_COUNT + j, i,j);
            }
        }
    }
    else {
        puts("No colors!\n");
    }
    void* game = NULL;
    if (init_game != NULL){
         game = init_game();
         assert_message(game != NULL,"init_game:: should return non null pointer");
    }
    timeout(TIMEOUT);
    // Initial step
    struct event event;
    memset(&event,0,sizeof(struct event));
    event.height = LINES;
    event.width = COLS;
    event.type = EVENT_START;
    clock_t start_time = clock();
    clock_t last_timeout = start_time;
    clock_t next_timeout = last_timeout + TIMEOUT;
    event.time_ms = start_time;
    // Start event
    r = world_event(&event,game);
    refresh();
    while (!r) {
        memset(&event,0,sizeof(struct event));
        event.height = LINES;
        event.width = COLS;
        event.key = getch();
        // No key was pressed
        if (event.key == ERR){
            event.type = EVENT_TIMEOUT;
            last_timeout = clock();
            next_timeout = last_timeout + TIMEOUT;
        }
        // Mouse event
        else if (event.key == KEY_MOUSE ){
            event.type = EVENT_MOUSE;
            if(getmouse(&mouse_event) == OK){
                event.mouse_x = mouse_event.x;
                event.mouse_y = mouse_event.y;
                if(mouse_event.bstate & BUTTON1_PRESSED){
                    event.mouse_left = 1;
                }
                if(mouse_event.bstate & BUTTON2_PRESSED){
                    event.mouse_middle = 1;
                }
                if(mouse_event.bstate & BUTTON3_PRESSED){
                    event.mouse_right = 1;
                }
            }
        }
        else if (event.key == KEY_RESIZE) {
            event.type = EVENT_RESIZE;
        }
        else{
            event.type = EVENT_KEY;
            if (event.key == 27){
                int k = getch();
                if (k == -1){
                    // Esc Was pressed
                    event.type = EVENT_ESC;
                }
                else {
                    // Alt was pressed
                    event.key = k;
                    event.alt_key = 1;
                }
            }
        }
        // Draw new world
        event.time_ms = clock();
        r = world_event(&event,game);
        refresh();
        event.time_ms = clock();
        // set new timeout
        int nt = next_timeout - event.time_ms;
        //printf("%d\n",nt);
        if (nt > 0){
            timeout(nt);
        }
        else {
            timeout(TIMEOUT);
            next_timeout = event.time_ms + TIMEOUT;
        }
    }
    memset(&event,0,sizeof(struct event));
    event.height = LINES;
    event.width = COLS;
    event.type = EVENT_END;
    event.time_ms = clock();
    world_event(&event,game);
    if (destroy_game != NULL){
        destroy_game(game);
    }
    endwin();
    return r;
};
