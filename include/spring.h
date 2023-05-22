#ifndef SPRING_H
#define SPRING_H

#include "point.h"
#define NB_SPRINGS 13

#define RIGID_STIFFNESS 50
#define SOFT_STIFFNESS 15
#define RIGID_DAMPING 30
#define SOFT_DAMPING 0.5


spring** create_springs(point** points);

void update_spring(spring* s);


#endif