#include "../include/point.h"



point create_point(double x, double y, bool fixed){
    point p;
    vect2 pos = {.x = x, .y = y};
    p.pos = pos;
    p.init_pos = pos;
    p.prev_pos = pos;
    p.fixed = fixed;
    p.s1 = NULL;
    p.s2 = NULL;
    return p;
}

/*
Creates points shaped like this


WIDTH/4 to mid.x           BUILDING_WIDTH
<------------------->      <--------------> 

                       3  o             4 o


o                         o               o                         o   7                  
0                          1              2

                        5 o             6 o

*/
point* create_points(int WIDTH,int HEIGHT){
    point* points = malloc(sizeof(point) * NB_POINTS);
    vect2 mid = {.x = WIDTH / 2, .y = HEIGHT/2};
    points[0] = create_point(WIDTH/4,mid.y,true);
    points[NB_POINTS - 1] = create_point(3 * WIDTH/4,mid.y,true);
    points[1] = create_point(mid.x - BUILDING_HWIDTH,mid.y,false);
    points[2] = create_point(mid.x + BUILDING_HWIDTH,mid.y,false);
    points[3] = create_point(mid.x - BUILDING_HWIDTH,mid.y - BUILDING_HHEIGHT,false);
    points[4] = create_point(mid.x + BUILDING_HWIDTH,mid.y - BUILDING_HHEIGHT,false);
    points[5] = create_point(mid.x - BUILDING_HWIDTH,mid.y + BUILDING_HHEIGHT,false);
    points[6] = create_point(mid.x + BUILDING_HWIDTH,mid.y + BUILDING_HHEIGHT,false);
    return points;
}


void print_point(point p){
    printf("Pos : (%f;%f), fixed : %d",p.pos.x,p.pos.y,p.fixed);
}