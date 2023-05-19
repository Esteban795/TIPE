#ifndef SPRING_H
#define SPRING_H

#include "point.h"

#define NB_SPRINGS 19

#define RIGID_STIFFNESS 10
#define SOFT_STIFFNESS 2
#define RIGID_DAMPING 10
#define SOFT_DAMPING 5


spring** create_springs(point** points);

void update_spring(spring* s);


#endif