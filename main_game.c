#include<stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "table.h"

void movement(Hero* h,char* direction, Map* map){
    int i = 0;
    int yd = 0;
    int xd = 0;
    switch(direction){
        case "HAUT":
            xd = h->pos->x;
            yd = h->pos->y;
            for(i;i<map->position_list_size;i++){
            if(map->positions[i].x==h->xd && map->positions[i].y <= yd+h->speed && map->positions[i].y > yd){
                if (map->positions[i].symbol == "#"){
                    h->pos->y=map->positions[i].y - 1;
                    h->pos->x=xd;
                }
                else{
                    h->pos->y = yd+h->speed;
                    h->pos->x = xd;
                }
                if (map->positions[i].symbol == "!" && map->positions[i].x == xd && map->positions[i].y > yd && map->positions[i].y <= h->pos->y)
            }
            h->pos->y=h->pos->y+h->speed;  
            break;
        case "BAS":
            h->pos->y=h->pos->y-h->speed;  
            break;
        case "GAUCHE":
            h->pos->x=h->pos->x-h->speed;  
            break;
        case "DROIT":
            h->pos->x=h->pos->x+h->speed;  
            break;
}
}
}