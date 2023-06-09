#include "../include/point.h"



point* create_point(double x, double y, bool fixed,double mass){
    point* p = malloc(sizeof(point));
    vect2 pos = {.x = x, .y = y};
    p->pos = pos;
    p->prev_pos = pos;
    p->is_fixed = fixed;
    vect2 zero_vect = {.x = 0.0, .y = 0.0};
    p->force = zero_vect;
    p->mass = mass;
    p->vel = zero_vect;
    return p;
}

/*
Creates points shaped like this


WIDTH/4 to mid.x           BUILDING_WIDTH
<------------------->      <--------------> 

                       3  o             4 o


o                         o               o                         o   7   TMD               
0                          1              2

                        5 o             6 o


Bottom part is essential to maintain the structure. Probably won't be drawn onto the actual screen.
*/
point** create_points(int WIDTH,int HEIGHT){
    point** points = malloc(sizeof(point*) * NB_POINTS);
    vect2 mid = {.x = WIDTH / 2, .y = HEIGHT/2};

    //fixed points
    points[0] = create_point(WIDTH/10,mid.y,true,1);
    points[NB_POINTS - 1] = create_point(9 * WIDTH/10,mid.y,false,TMD_MASS);

    points[1] = create_point(mid.x - BUILDING_HWIDTH,mid.y,false,POINT_MASS);
    points[2] = create_point(mid.x + BUILDING_HWIDTH,mid.y,false,POINT_MASS);
    points[3] = create_point(mid.x - BUILDING_HWIDTH,mid.y - BUILDING_HHEIGHT,false,POINT_MASS);
    points[4] = create_point(mid.x + BUILDING_HWIDTH,mid.y - BUILDING_HHEIGHT,false,POINT_MASS);
    points[5] = create_point(mid.x - BUILDING_HWIDTH,mid.y + BUILDING_HHEIGHT,false,POINT_MASS);
    points[6] = create_point(mid.x + BUILDING_HWIDTH,mid.y + BUILDING_HHEIGHT,false,POINT_MASS);
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

//Verlet integration to update every points position
void update_positions(point** points,double dt){
    for (int i = 0; i < NB_POINTS; i++){
        if (!points[i]->is_fixed) {
            double new_x = 2 * points[i]->pos.x - points[i]->prev_pos.x + (points[i]->force.x * dt * dt / points[i]->mass);
            double new_y = 2 * points[i]->pos.y - points[i]->prev_pos.y + (points[i]->force.y * dt * dt / points[i]->mass); 
            points[i]->prev_pos = points[i]->pos;
            points[i]->pos.x = new_x;
            points[i]->pos.y = new_y;
        }
    }   
}

void update_velocities(point** points,double dt){
    for (int i = 0; i < NB_POINTS; i++){
        if (!points[i]->is_fixed) {
            points[i]->vel.x = (points[i]->pos.x - points[i]->prev_pos.x)/dt;
            points[i]->vel.y = (points[i]->pos.y - points[i]->prev_pos.y)/dt;
        }
    }
}

void delete_points(point** points){
    for (int i = 0; i < NB_POINTS;i++){
        free(points[i]);
    }
    free(points);
}