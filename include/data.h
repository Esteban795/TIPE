#ifndef DATA_H
#define DATA_H

#include "point.h"

int write_to_arr(int* data_sol,int* data_top,int len,bool started, int* index,int nb_dt,point** points);

void save_to_file(char* filename,int* data_sol, int* data_top,int len,double stiffness,double damping,double B_H,double TMD_stiff);


#endif