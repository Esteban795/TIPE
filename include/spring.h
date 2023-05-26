#ifndef SPRING_H
#define SPRING_H

#include "point.h"
#define NB_SPRINGS 15

#define RIGID_STIFFNESS 75.0
#define SOFT_STIFFNESS 20.0
#define RIGID_DAMPING 75.0
#define SOFT_DAMPING 0.0

#define TMD_STIFFNESS 50.0
#define TMD_DAMPING 10.0


spring** create_springs(point** points);

void update_spring(spring* s);

void delete_springs(spring** springs);

#endif