#include<stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "table.h"

int main(void){
    int i;
    Map* m = create_map();
    
    for(i = 0; i < 4; i++){
        printf("pos_x: %d; pos_y: %d; symbol: %c;\n", m->rocks[i].pos->x, m->rocks[i].pos->y, m->rocks[i].symbol);    
    }
    printf("-------------------------------\n");
    for(i = 0; i < 7; i++){
        printf("pos_x: %d; pos_y: %d; sym: %c;\n", m->positions[i].x, m->positions[i].y, m->positions[i].symbol);    
    }
    
  
    
    return 0;
}