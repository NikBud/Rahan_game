#include<stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "table.h"

int main(void){
    int i;
    Map* m = create_map();
    m->size = 10;
    
    render_map(m);
    for (i =0; i < 2;i++){
        printf("Food: %s  Desc: %s; Heal: %d\n", m->food[i].name, m->food[i].description, m->food[i].heal);
        printf("Item: %s  Bonus: %d\n", m->items[i].description, m->items[i].stat_bonus);
    }
        
    for(i = 0; i < m->position_list_size; i++){
        printf("pos_x: %d; pos_y: %d\n", m->positions[i].x, m->positions[i].y);
    }

    return 0;
}
