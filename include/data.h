#ifndef DATA_H
#define DATA_H

#include "point.h"

int write_to_arr(int* arr,int len,bool started, int* index,int nb_dt,point** points);

void save_to_file(char* filename,int* arr,int len);


#endif