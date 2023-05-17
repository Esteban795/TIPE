#ifndef VECT2_H
#define VECT2_H

#include <math.h>


struct Vect2 {
    float x;
    float y;
};

typedef struct Vect2 vect2;

/*
Returns the vect2 that is the difference of both x and y coordinates
*/
vect2 vect2_diff(vect2 v1,vect2 v2);

/*
Divide vector coordinates by a floating point number
*/
vect2 vect2_divide(vect2 v,float n);

/*
Returns length of the vector
*/
float vect2_length(vect2 p);

float dot_product(vect2 v1,vect2 v2);



#endif