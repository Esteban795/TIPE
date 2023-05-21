#include "../include/stick.h"


stick create_stick(point* p1, point* p2,bool active){
    stick s;
    s.p1 = p1;
    s.p2 = p2;
    vect2 pos_diff = vect2_diff(p1->pos,p2->pos);
    s.x_offset = pos_diff.x;
    s.y_offset = pos_diff.y;
    s.active = active;
    return s;
}
stick* create_sticks(point** points){
    stick* sticks = malloc(sizeof(stick) * NB_STICKS);

    //maintains structure at any time
    sticks[0] = create_stick(points[1],points[2],true);
    sticks[1] = create_stick(points[1],points[3],true);
    sticks[2] = create_stick(points[1],points[5],true);
    sticks[3] = create_stick(points[2],points[4],true);
    sticks[4] = create_stick(points[2],points[6],true);

    
    sticks[5] = create_stick(points[4],points[3],false);
    sticks[6] = create_stick(points[3],points[2],false);
    sticks[7] = create_stick(points[1],points[4],false);
    sticks[8] = create_stick(points[1],points[6],false);
    sticks[9] = create_stick(points[5],points[2],false);
    sticks[10] = create_stick(points[3],points[4],false);
    
    return sticks;
    
}

void update_stick(stick s){
    if (!s.active) return;
    s.p2->pos.x = s.p1->pos.x + s.x_offset;
    s.p2->pos.y = s.p1->pos.y + s.y_offset;
}