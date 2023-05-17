#include "../include/vect2.h"

/*
Returns the vect2 that is the difference of both x and y coordinates
*/
vect2 vect2_diff(vect2 v1,vect2 v2){
    vect2 temp = {.x = v1.x - v2.x,.y = v1.y - v2.y};
    return temp;
}

/*
Divide vector coordinates by a floating point number
*/
vect2 vect2_divide(vect2 v,double n) {
    vect2 temp = {.x = v.x / n,.y = v.y / n};
    return temp;
}

double vect2_length(vect2 v){
    return sqrtf(v.x * v.x + v.y * v.y);
}

double dot_product(vect2 v1,vect2 v2){
    return v1.x * v2.x + v1.y * v2.y;
}
