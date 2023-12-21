#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "main_game.h"

int main(void){
    int i;
    Map* m = create_map();
    m->size = 10;
    
    render_map(m);
    printf("is dead: %i \n", isDead(m->hero));
    game_start(m->hero, m);


    return 0;
}
