#include "console.h"
#include "cindex.h"
#include "disc.h"
#include "file.h"
#include "tag.h"
#include <chrono>
#include <unistd.h>
#include <string>
#include <iostream>

#include "ncurses.h"

#pragma once

#define MAINMENU_OPTIONS 4
#define MAINMENU_OPTIONS_OFFSET 3
#define MAINMENU_ADD "ADD"
#define MAINMENU_REMOVE "REMOVE"
#define MAINMENU_TAG "TAG"
#define MAINMENU_LIST "LIST"
#define MAINMENU_EXIT "EXIT"
    /*
     [0] OPTION 1: ADD
     [1] OPTION 2: REMOVE
     [2] OPTION 3: TAG
     [3] OPTION 4: LIST
     [4] OPTION 5: EXIT
     */

class gui {

public:
gui(cindex& index) {
this->index = &index;
exitting = false;
win = false;
width = 0;
height = 0;
characters = 0;
};
gui(cindex* index) {
this->index = index;
exitting = false;
win = false;
width = 0;
height = 0;
characters = 0;
};
void begin() {
    auto tp1 = chrono::system_clock::now();
    auto tp2 = chrono::system_clock::now();
    float elapsedtime;
    std::chrono::duration<float> elapsed;
    if (!win) {
        window = initscr();
        noecho();
        nodelay(stdscr, true);
        curs_set(false);
        console::bindioctl();
        height = console::getconsoleheight();
        width = console::getconsolewidth();
        characters = width * height;
        //std::cout << width << height << endl;
        screen = new char[characters];
        memset(screen, ' ', characters);
        win = true;
    }
    string fps;
    control.context = (void*)&gui::mainmenu;
    while (!exitting) {
            tp2 = std::chrono::system_clock::now();
            elapsed = tp2 - tp1;
            tp1 = tp2;
            elapsedtime = elapsed.count();
            if (30 < 1.0f / elapsedtime) usleep(33000.0f - (elapsedtime / CLOCKS_PER_SEC));
        (*(void(*)())control.context)();

        fps = std::to_string(1.0f / elapsedtime);
        for (int i =0; i <fps.length(); i++)
            screen[i + 1] = fps[i];
            //std::cout << screen;
        draw();
        control.key = wgetch(window);
        if (control.key == '\x1B') exitting = true;

        tp1 = std::chrono::system_clock::now();
    }
    if (exitting) {exit();}
}
void exit() {
    win = false;

    exitting = false;

    endwin();

    //delete screen;
}
void mainmenu() {
    /*
     [0] OPTION 1: ADD
     [1] OPTION 2: REMOVE
     [2] OPTION 3: TAG
     [3] OPTION 4: LIST
     [4] OPTION 5: EXIT
     */

    if (control.key != ERR) {
        switch (control.key) {
    case KEY_UP:
        if (control.mainmenu.selected < MAINMENU_OPTIONS) control.mainmenu.selected++;
        else
            control.mainmenu.selected = 0;
        break;
    case KEY_DOWN:
        if (control.mainmenu.selected > 0) control.mainmenu.selected--;
        else
            control.mainmenu.selected = MAINMENU_OPTIONS;
        break;
    case KEY_ENTER:
        switch (control.mainmenu.selected) {
    case 4:
        exitting = true;
        return;
        }
        break;
        default:
            break;
        }
    }

    //Draw elements
    if (width > 20 && height > 20) {
        strcpy((char*)&screen[(1 * width) + MAINMENU_OPTIONS_OFFSET], (const char*)MAINMENU_ADD);
        strcpy((char*)&screen[(2 * width) + MAINMENU_OPTIONS_OFFSET], (const char*)MAINMENU_REMOVE);
        strcpy((char*)&screen[(3 * width) + MAINMENU_OPTIONS_OFFSET], (const char*)MAINMENU_TAG);
        strcpy((char*)&screen[(4 * width) + MAINMENU_OPTIONS_OFFSET], (const char*)MAINMENU_LIST);
        strcpy((char*)&screen[(5 * width) + MAINMENU_OPTIONS_OFFSET], (const char*)MAINMENU_EXIT);
        screen[((control.mainmenu.selected + 1) * width) + MAINMENU_OPTIONS_OFFSET - 1] = '>';
    }
return;
}

private:
    struct controls
    {
    size_t context = (void*)&gui::mainmenu;
        struct mainmenus {
            int selected = 0;
        } mainmenu;
    int key;
    } control;
void draw() {
    screen[characters - 1] = '\0';
    //mvwprintw(window, 0,0,(const char*)screen);
    console::setcursory(0);
    console::setcursorx(0);
    std::cout << screen;
    memset(screen, ' ', characters);
}
    bool exitting;
    int characters;
    int height;
    int width;
    char* screen;
    bool win;
    WINDOW* window;
    cindex* index;

};
