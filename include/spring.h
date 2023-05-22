#ifndef SPRING_H
#define SPRING_H

#include "point.h"
#define NB_SPRINGS 13

#define RIGID_STIFFNESS 9
#define SOFT_STIFFNESS 1.5
#define RIGID_DAMPING 0.5
#define SOFT_DAMPING 0.2


spring** create_springs(point** points);

void update_spring(spring* s);


#endif