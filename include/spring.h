#ifndef SPRING_H
#define SPRING_H

#include "point.h"
#define NB_SPRINGS 13

#define RIGID_STIFFNESS 4
#define SOFT_STIFFNESS 2
#define RIGID_DAMPING 3
#define SOFT_DAMPING 0.5


spring** create_springs(point** points);

void update_spring(spring* s);

void delete_springs(spring** springs);

#endif