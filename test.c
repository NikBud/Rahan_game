#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "main_game.h"

int main(void){
    int i;
    Map* m = create_map();
    m->size = 10;

    Item* itm = m->items;
    itm->pos->x = 3;
    itm->pos->y = 4;

    game_start(m->hero, m);


    return 0;
}
