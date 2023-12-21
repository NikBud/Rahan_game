#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include "main_game.h"

int isDead(Hero * h){
    if (h->current_hp <= 0){
        return 1;
    }
    else{
        return 0;
    }
}

void movement(Hero* h,int direction, Map* map){
    int i = 0;
    int yd = 0;
    int xd = 0;
    switch(direction){
        case 1:
            xd = h->pos->x;
            yd = h->pos->y;
            for(i;i<map->position_list_size;i++){
                if(map->positions[i].x == h->pos->x && map->positions[i].y <= yd+h->speed && map->positions[i].y > yd){
                    if (map->positions[i].symbol == "#"){
                        h->pos->y=map->positions[i].y - 1;
                        h->pos->x=xd;
                    }
                    else{
                        h->pos->y = yd+h->speed;
                        h->pos->x = xd;
                    }
                    if (map->positions[i].symbol == "!" && map->positions[i].x == xd && map->positions[i].y > yd && map->positions[i].y <= h->pos->y)
                    printf("item on the way\n");
                }
                h->pos->y=h->pos->y+h->speed;  
                break;
            }
        case 2:
            h->pos->y=h->pos->y-h->speed;  
            break;
        case 3:
            h->pos->x=h->pos->x-h->speed;  
            break;
        case 4:
            h->pos->x=h->pos->x+h->speed;  
            break;
        
    }
}

void game_start(Hero* h, Map* m){
    char c[12];
    printf("test start game\n");
    while (!isDead(h)){
        scanf("%10s", c);
        if (strcmp(c, "CREPUSCULE")){
            break;
        }
        if(strcmp(c, "HAUT")){
            printf("test up\n");
            movement(h, 1, m);
        }
        else if(strcmp(c, "BAS")){
            printf("test down\n");
            movement(h, 2, m);
        }
        else if(strcmp(c, "DROIT")){
            printf("test right\n");
            movement(h, 3, m);
        }
        else if(strcmp(c, "GAUCHE")){
            printf("test left\n");
            movement(h, 4, m);
        }
    }
}