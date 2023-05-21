#ifndef STICK_H
#define STICK_H

#include "point.h"

#define NB_STICKS 11


struct Stick {
    point* p1;  
    point* p2;
    int x_offset;
    int y_offset;
    bool active;
};

typedef struct Stick stick;

stick* create_sticks(point** points);

void update_stick(stick s);


#endif