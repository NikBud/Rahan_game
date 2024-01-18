#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "libs/main_game.h"

int main(void){
    int foodCount, monstersCount, itemsCount, rocksCount;
    foodCount = 3;
    monstersCount = 3;
    itemsCount = 4;
    rocksCount = 4;

    game_start(foodCount, monstersCount, itemsCount, rocksCount);

    stdprof_afficher();

    return 0;
}
