#ifndef POINT_H
#define POINT_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "vect2.h"

struct Spring;
struct Point;

struct Spring {
    struct Point* p1;
    struct Point* p2;
    float length;
};

struct Point { 
    struct Stick* s1;
    struct Stick* s2;
    vect2 pos;
    vect2 prev_pos;
    vect2 init_pos;
    vect2 vel;
    bool fixed;
};

typedef struct Spring spring;
typedef struct Point point;


#endif