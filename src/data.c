#include "../include/data.h"

int write_to_arr(int* arr,int len,bool started, int* index,int nb_dt,point** points){
    if (started && nb_dt % 5 == 0 && *index < len) {
        arr[*index] = points[1]->pos.x;
        *index += 1;
        return 0;
    } else if (*index >= len) return 1;
}

void save_to_file(char* filename,int* arr,int len){
    FILE* f_out = fopen(filename,"w");
    for (int i = 0; i < len ;i++) {
        fprintf(f_out,"%d %d\n",16 * i,arr[i]);
    }
    fclose(f_out);
}