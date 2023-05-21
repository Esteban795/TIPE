#ifndef SPRING_H
#define SPRING_H

#include "point.h"

#define NB_SPRINGS 17

#define RIGID_STIFFNESS 50
#define SOFT_STIFFNESS 3
#define RIGID_DAMPING 50
#define SOFT_DAMPING 0.5


spring** create_springs(point** points);

void update_spring(spring* s);


#endif