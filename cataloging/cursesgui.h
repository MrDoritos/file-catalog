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

class gui {

public:
gui(cindex& index) {
this->index = &index;
exitting = false;
win = false;
};
gui(cindex* index) {
this->index = index;
exitting = false;
win = false;
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

        height = window->_maxy;
        width = window->_maxx;
        characters = width * height;
        //std::cout << width << height << endl;
        screen = new char[characters];
        memset(screen, ' ', characters);
        win = true;
    }
    string fps;
    auto context = &gui::mainmenu;
    while (!exitting) {
            tp2 = std::chrono::system_clock::now();
            elapsed = tp2 - tp1;
            tp1 = tp2;
            elapsedtime = elapsed.count();
            if (30 < 1.0f / elapsedtime) usleep(33000.0f - (elapsedtime / CLOCKS_PER_SEC));
        (*(void(*)())context)();

        //fps = std::to_string(((elapsedtime * CLOCKS_PER_SEC) / 0.0333f) * 30.0f);
        fps = std::to_string(1.0f / elapsedtime);
        for (int i =0; i <fps.length(); i++)
            screen[i + 1] = fps[i];
            //std::cout << screen;
        draw();
            //std::cout << fps << endl;
            //std::cout << "here";
        //mvwprintw(window, 1, 0, std::to_string(((elapsedtime / CLOCKS_PER_SEC) * 0.0333f) * 30).c_str());
        tp1 = std::chrono::system_clock::now();
    }
    if (exitting) {exit();}
}
void exit() {
    win = false;

    exitting = false;
    //delete screen;
}
void mainmenu() {
return;
}

private:
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
