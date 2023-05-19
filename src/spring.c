#include "../include/spring.h"


/* 
Creates springs like those. (numbers are the spring index in the `springs` array)

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

spring create_spring(point* p1,point* p2,double stiffness, double damping){
    spring s;
    s.p1 = p1;
    s.p2 = p2;
    p1->springs[p1->available_spring_index] = s;
    p2->springs[p2->available_spring_index] = s;
    s.length = vect2_length(vect2_diff(p1->pos,p2->pos));
    s.stiffness = stiffness;
    s.damping = damping;
    return s;
}


spring* create_springs(point* points){
    spring* springs = malloc(sizeof(spring) * NB_SPRINGS);
    
    //actual springs that will have an impact on reducing waves amplitude
    springs[0] = create_spring(&points[0],&points[1],SOFT_STIFFNESS,SOFT_DAMPING);
    springs[NB_SPRINGS - 1] = create_spring(&points[2],&points[7],SOFT_STIFFNESS,SOFT_DAMPING);

    //rigid springs : they help maintain the building as a whole.
    springs[1] = create_spring(&points[1],&points[2],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[2] = create_spring(&points[3],&points[4],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[3] = create_spring(&points[5],&points[6],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[4] = create_spring(&points[1],&points[3],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[5] = create_spring(&points[4],&points[2],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[6] = create_spring(&points[1],&points[5],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[7] = create_spring(&points[6],&points[2],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[8] = create_spring(&points[3],&points[2],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[9] = create_spring(&points[1],&points[4],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[10] = create_spring(&points[6],&points[1],RIGID_STIFFNESS,RIGID_DAMPING);
    springs[11] = create_spring(&points[5],&points[2],RIGID_STIFFNESS,RIGID_DAMPING);
    return springs;
}

void update_spring(spring* s){
    //Force should be F = stiffness * ((p1_pos - p0_pos) -s->length) + k_damper * (v1 - v0)
    
    vect2 pos_diff = vect2_diff(s->p2->pos, s->p1->pos);
    vect2 vel_diff = vect2_diff(s->p2->vel,s->p1->pos);

    double diff_pos_length = vect2_length(pos_diff) - s->length;
    
}