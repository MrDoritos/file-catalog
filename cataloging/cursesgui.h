#include "console.h"
#include "cindex.h"
#include "disc.h"
#include "file.h"
#include "tag.h"

#include "ncurses.h"

#pragma once

class gui {

public:
gui(cindex& index) {
this->index = &index;
};
gui(cindex* index) {
this->index = index;
};
void begin() {
    if (!win)
        window = initscr();
}

private:
    bool win;
    WINDOW* window;
    cindex* index;

};
