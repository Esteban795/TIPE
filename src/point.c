#include "../include/point.h"



point create_point(double x, double y, bool fixed){
    point p;
    vect2 pos = {.x = x, .y = y};
    p.pos = pos;
    p.init_pos = pos;
    p.prev_pos = pos;
    p.is_fixed = fixed;
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
    printf("Pos : (%f;%f), fixed : %d\n",p.pos.x,p.pos.y,p.is_fixed);
}

//Verlet integration
void update_point(point* p,double dt, double drag, vect2 acceleration){
    if (p->is_fixed) return; //points that are not affected by any force.
    float new_x = p->pos.x + (p->pos.x - p->prev_pos.x) * (1.0f - drag) + acceleration.x * (1.0f - drag) * dt * dt;
    float new_y = p->pos.y + (p->pos.y - p->prev_pos.y) * (1.0f - drag) + acceleration.y * (1.0f - drag) * dt * dt;
    p->prev_pos = p->pos;
    p->pos.x = new_x;
    p->pos.y = new_y;
    vect2 temp_vel = vect2_diff(p->pos,p->prev_pos);
    p->vel = vect2_divide(temp_vel,1/dt);
}