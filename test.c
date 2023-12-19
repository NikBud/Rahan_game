#include<stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "table.h"

int main(void){
    int i;
    Map* m = create_map(); 
    for (i = 0; i < 3; i++){
        printf("Name of monster: %s\n", m->monsters[i].name);
    }
    return 0;
}
