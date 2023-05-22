#include "../include/point.h"



point* create_point(double x, double y, bool fixed,int nb_springs){
    point* p = malloc(sizeof(point));
    vect2 pos = {.x = x, .y = y};
    p->pos = pos;
    p->is_fixed = fixed;
    p->nb_springs = nb_springs;
    p->springs = malloc(sizeof(spring) * nb_springs);
    p->available_spring_index = 0;
    vect2 zero_vect = {.x = 0.0, .y = 0.0};
    p->force = zero_vect;
    p->mass = 1;
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
point** create_points(int WIDTH,int HEIGHT){
    point** points = malloc(sizeof(point*) * NB_POINTS);
    vect2 mid = {.x = WIDTH / 2, .y = HEIGHT/2};

    points[0] = create_point(WIDTH/4,mid.y,true,2);
    points[NB_POINTS - 1] = create_point(3 * WIDTH/4,mid.y,true,2);

    points[1] = create_point(mid.x - BUILDING_HWIDTH,mid.y,false,2);
    points[2] = create_point(mid.x + BUILDING_HWIDTH,mid.y,false,2);
    /*
    points[3] = create_point(mid.x - BUILDING_HWIDTH,mid.y - BUILDING_HHEIGHT,false,5);
    points[4] = create_point(mid.x + BUILDING_HWIDTH,mid.y - BUILDING_HHEIGHT,false,5);
    points[5] = create_point(mid.x - BUILDING_HWIDTH,mid.y + BUILDING_HHEIGHT,false,5);
    points[6] = create_point(mid.x + BUILDING_HWIDTH,mid.y + BUILDING_HHEIGHT,false,5);
    */
    return points;
}


void apply_force(point* p,vect2 f){
    p->force = vect2_add(p->force,f);
}

void clear_forces(point** points){
    for (int i = 0; i < NB_POINTS; i++){
        points[i]->force.x = 0.0;
        points[i]->force.y = 0.0;
    }
}

//Euler integration to update every points position
void update_positions(point** points,double dt){
    for (int i = 0; i < NB_POINTS; i++){
        if (!points[i]->is_fixed) {
            vect2 temp = vect2_multiply(points[i]->vel,dt);
            points[i]->pos = vect2_add(points[i]->pos,temp);
        }
    }
    
}

void update_velocities(point** points,double dt){
    for (int i = 0; i < NB_POINTS; i++){
        if (!points[i]->is_fixed) {
            vect2 accel = vect2_multiply(points[i]->force,1.0/points[i]->mass);
            vect2 temp = vect2_multiply(accel,dt);
            points[i]->vel = vect2_add(points[i]->vel,temp);
        }
    }
}