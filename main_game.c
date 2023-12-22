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
    return 0;
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
                if(map->positions[i].x == h->pos->x && map->positions[i].y <= yd + h->speed && map->positions[i].y > yd){
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
    printf("Welcome to the Rahan Game !\n");
    printf("Type the word \'AUBE\' to start the game: ");
    scanf("%10s", c);
    while(strcmp(c, "AUBE") != 0){
        printf("Sorry, you cannot start the game with this command!\nTry one more time: ");
        scanf("%10s", c);
    }

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    render_map(m);
    printf("THE GAME BEGINS\n");    

    while (!isDead(h)){
        printf("\nYour command: ");
        scanf("%10s", c);

        if (strcmp(c, "CREPUSCULE") == 0){
            printf("\nYou decided to end up the game, thank you and our team are waiting for you again!\n");
            break;
        }
        else if(strcmp(c, "HAUT") == 0){
            movement(h, 1, m);
        }
        else if(strcmp(c, "BAS") == 0){
            movement(h, 2, m);
        }
        else if(strcmp(c, "DROIT") == 0){
            movement(h, 3, m);
        }
        else if(strcmp(c, "GAUCHE") == 0){
            movement(h, 4, m);
        }
        else if(strcmp(c, "VISION") == 0){
            render_map(m);
        }
        else if(strcmp(c, "INVOCATION") == 0){
            print_hero_stats(m);
        }
        else{
            printf("\nUnknown command, please try again.\nAllowed commands are: AUBE (start game), CREPUSCULE (finish game),\nVISION (print map), INVOCATION (stats of player),\nHAUT (make a step up), BAS (make a step down),\nGAUCHE (make a step left), DROITE (make a step right).\n");
        }
    }
}