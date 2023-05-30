#include "../include/spring.h"


spring* create_spring(point* p1,point* p2,double stiffness, double damping){
    spring* s = malloc(sizeof(spring));
    s->p1 = p1;
    s->p2 = p2;
    s->length = vect2_length(vect2_diff(p1->pos,p2->pos));
    s->stiffness = stiffness;
    s->damping = damping;
    return s;
}

/* 
Creates springs like this. (numbers are the spring index in the `springs` array)
Add diagonals but I'm too lazy for that.
                                  2
                           o ------------ o  
                        4  |              |  5
                           |              |
o ------------------------ o ------------ o ----------------------- o                   
            0              |      1       |       8
                        6  |              |  7
                           o ------------ o
                                  3

*/
spring** create_springs(point** points){
    spring** springs = malloc(sizeof(spring*) * NB_SPRINGS);
    
    //actual springs that will have an impact on creating/reducing waves amplitude
    springs[0] = create_spring(points[0],points[1],SOFT_STIFFNESS,SOFT_DAMPING);
    springs[NB_SPRINGS - 1] = create_spring(points[2],points[NB_POINTS - 1],TMD_STIFFNESS,TMD_DAMPING);
    
    //rigid springs : they help maintain the building as a structure
    springs[1] = create_spring(points[1],points[3],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[2] = create_spring(points[3],points[4],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[3] = create_spring(points[4],points[2],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[4] = create_spring(points[2],points[6],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[5] = create_spring(points[6],points[5],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[6] = create_spring(points[1],points[5],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[7] = create_spring(points[1],points[2],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[8] = create_spring(points[1],points[4],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[9] = create_spring(points[3],points[2],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[10] = create_spring(points[1],points[6],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[11] = create_spring(points[5],points[2],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[12] = create_spring(points[3],points[6],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[13] = create_spring(points[5],points[4],RIGID_STIFFNESS,RIGID_DAMPING);
    return springs;
}

void update_spring(spring* s){
    //Force should be F = - stiffness * ((p1_pos - p0_pos) - s->length) + k_damper * (v1 - v0)
    
    vect2 pos_diff = vect2_diff(s->p1->pos,s->p2->pos);
    vect2 vel_diff = vect2_diff(s->p1->vel,s->p2->vel);
    
    float distance = vect2_length(pos_diff);
    double coeff =  - (s->stiffness * (distance - s->length) + s->damping * dot_product(vel_diff,pos_diff) / distance);
    
    vect2 f1 = vect2_multiply(pos_diff,coeff / distance);
    vect2 f2 = vect2_multiply(f1,-1);

    if (!s->p1->is_fixed){ //If a point is pinned, it shouldn't move. So we don't apply anything to it.
        apply_force(s->p1,f1);
    }
    if (!s->p2->is_fixed){
        apply_force(s->p2,f2);
    }
    
}

void delete_springs(spring** springs){
    for (int i = 0; i < NB_SPRINGS; i++){
        free(springs[i]);
    }
    free(springs);
}