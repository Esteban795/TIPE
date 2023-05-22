#include "../include/data.h"

int write_to_arr(int* data_sol,int* data_top,int len,bool started, int* index,int nb_dt,point** points){
    if (started && nb_dt % 5 == 0 && *index < len) {
        data_sol[*index] = points[1]->pos.x;
        data_top[*index] = points[3]->pos.x;
        *index += 1;
        return 0;
    } else if (*index >= len) return 1;
}

void save_to_file(char* filename,int* data_sol, int* data_top,int len,double stiffness,double damping,double B_H){
    FILE* f_out = fopen(filename,"w");
    fprintf(f_out,"%f %f %f\n",stiffness,damping,B_H);
    for (int i = 0; i < len ;i++) {
        fprintf(f_out,"%d %d %d\n",16 * i,data_sol[i],data_top[i]);
    }
    fclose(f_out);
}