#ifndef SPRING_H
#define SPRING_H

#include "point.h"

#define NB_SPRINGS 13

#define RIGID_STIFFNESS 1.0
#define SOFT_STIFFNESS 0.8 
#define RIGID_DAMPING 1.0
#define SOFT_DAMPING 0.8


spring* create_springs(point* points);



#endif