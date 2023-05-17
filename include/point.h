#ifndef POINT_H
#define POINT_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "vect2.h"


#define NB_POINTS 8
#define BUILDING_HWIDTH 50
#define BUILDING_HHEIGHT 50

struct Spring;
struct Point;

struct Spring {
    struct Point* p1;
    struct Point* p2;
    double length;
    double stiffness;
    double damping;
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

point* create_points(int WIDTH,int HEIGHT);

void print_point(point p);

#endif