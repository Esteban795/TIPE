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
    struct Spring** springs;
    int nb_springs;
    int available_spring_index; 
    vect2 pos;
    vect2 vel;
    vect2 force;
    double mass;
    bool is_fixed;
};

typedef struct Spring spring;
typedef struct Point point;

point** create_points(int WIDTH,int HEIGHT);

void update_point(point* p,double dt);

void apply_force(point* p,vect2 f);

void update_positions(point** points,double dt);

void update_velocities(point** points,double dt);

void clear_forces(point** points);
#endif