#ifndef SPRING_H
#define SPRING_H

#include "point.h"
//old value : 17
#define NB_SPRINGS 5

#define RIGID_STIFFNESS 10
#define SOFT_STIFFNESS 1
#define RIGID_DAMPING 10
#define SOFT_DAMPING 0.5


spring** create_springs(point** points);

void update_spring(spring* s);


#endif