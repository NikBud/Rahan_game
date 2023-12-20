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
    for (i =0; i<2;i++){
        printf("Food: %s  Desc: %s\n", m->food[i].name, m->food[i].description);
        printf("Item: %s  Bonus: %d\n", m->items[i].description, m->items[i].stat_bonus);
    }

    render_map(m);
   
    return 0;
}
