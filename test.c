#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "main_game.h"

int main(void){
    int i;
    Map* m = create_map();
    m->size_x = 10;
    m->size_y = 10;

    game_start(m->hero, m);

    return 0;
}
