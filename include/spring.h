#ifndef SPRING_H
#define SPRING_H

#include "point.h"
#define NB_SPRINGS 13

#define RIGID_STIFFNESS 10
#define SOFT_STIFFNESS1 0.5
#define SOFT_STIFFNESS2 1
#define RIGID_DAMPING 10
#define SOFT_DAMPING 0.5


spring** create_springs(point** points);

void update_spring(spring* s);


#endif