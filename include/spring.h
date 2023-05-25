#ifndef SPRING_H
#define SPRING_H

#include "point.h"
#define NB_SPRINGS 12

#define RIGID_STIFFNESS 10
#define SOFT_STIFFNESS 3
#define RIGID_DAMPING 10
#define SOFT_DAMPING 0.5

#define TMD_STIFFNESS 2
#define TMD_DAMPING 10


spring** create_springs(point** points);

void update_spring(spring* s);

void delete_springs(spring** springs);

#endif