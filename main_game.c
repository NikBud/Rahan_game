#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include "main_game.h"

int isDead(Hero *h)
{
    if (h->current_hp <= 0)
    {
        return 1;
    }
    return 0;
}

int generate_x_pos(int current_x, int direction)
{
    if (direction == 1)
        current_x -= 1;
    else if (direction == 2)
        current_x += 1;
    return current_x;
}

int generate_y_pos(int current_y, int direction)
{
    if (direction == 3)
        current_y += 1;
    else if (direction == 4)
        current_y -= 1;
    return current_y;
}

void improve_hero(Hero* h, char* stat_to_improve, int stat_bonus){
    if (strcmp(stat_to_improve, "speed") == 0)
    {
        h->speed = stat_bonus + 1;
    }
    else if(strcmp(stat_to_improve, "hp") == 0)
    {
        h->max_hp = stat_bonus + 50;
    }
    else{
        h->force = stat_bonus + 10;
    }
}
int battle_init(Hero* h, Monter* m){
    int initiated = 1;
    while (initiated){
        m->hp = m->hp - h->force;
        if (m->hp <= 0){
            printf("Rahan defeated %s, a solid victory\n", m->name);
            return 1;
        }
        h->current_hp = h->current_hp - m->damage;
        if(isDead(h)){
            printf("Rahan suffered a mortal wound inflicted by %s\n", m->name);
            return 0;
        }
    }
}
void movement(Hero *h, int direction, Map *map)
{
    int i = 0, flag = 0, calc_heal = 0;
    int xd = generate_x_pos(h->pos->x, direction);
    int yd = generate_y_pos(h->pos->y, direction);
    for (i; i < map->position_list_size; i++){
        if (map->positions[i].x == xd && map->positions[i].y == yd){
            if (map->positions[i].symbol == '#'){
                printf("There is a rock on your way !");
                flag = 1;
            }
            else if (map->positions[i].symbol == '*'){
                Food *f = (Food *)map->positions[i].obj;
                if (h->current_hp < h->max_hp){
                    if (h->current_hp + f->heal > h -> max_hp){
                        calc_heal = h->max_hp - h->current_hp;
                        h->current_hp = h->max_hp;
                        f->symbol = ' ';
                        f->pos->x = 100000;
                        printf("Healed Rahan for %i\n", calc_heal);
                        break;
                    }
                    else{
                        h->current_hp = h->current_hp + f->heal;
                        f->symbol = ' ';
                        f->pos->x = 100000;
                        free(map->positions[i].obj);
                        printf("Healed Rahan for %i\n", f->heal);
                        break;
                    }
                }
                else if (h->current_hp == h->max_hp){
                    printf("Rahan doesn't feel hungry right now\n");
                    f->pos->x = 100000;
                    break;
                }
            }
            else if (map->positions[i].symbol == '!'){
                Item *itm = (Item *)map->positions[i].obj;
                int type = itm->type;
                char* item_bonus_types[] = {
                    "speed",
                    "hp",
                    "force"
                };
                Item existed_itm = h->items[type];
                if (existed_itm.stat_bonus < itm->stat_bonus)
                {
                    h->items[type] = *itm;
                    if (existed_itm.stat_bonus == 0) h->items_count++;
                    improve_hero(h, item_bonus_types[type], h->items[type].stat_bonus);
                    printf("\nCongrarulations! You have new item in your bag!\n");
                    printf("It's name is: %s", h->items[type].description);
                    printf("It gives to you %s bonus + %d\n", item_bonus_types[type], h->items[type].stat_bonus);
                }
                else{
                    printf("\nIt is item on your way!\n");
                    printf("But there is already an item of the same type in your bag that is stronger than the one you just encountered.\n");
                }
                itm->pos->x = 1000;
            }
            else if (map->positions[i].symbol == '@'){
                Monter *mnstr = (Monter*)map->positions[i].obj; 
                battle_init(h, mnstr);
                mnstr->pos->x = 1000;          
            }
        }
    }
    if (!flag)
    {
        h->pos->x = xd;
        h->pos->y = yd;
    }
    printf("pos x: %i size map x: %i\n", h->pos->x, 0 - map->x_decrease);
    printf("pos Y: %i size map y: %i\n", h->pos->y, 0  - map->y_decrease);
    if(h->pos->x >= map->size_x + map->x_increase){
        printf("augmented x\n");
        map->x_increase++;
    }
    if(h->pos->y >= map->size_y + map->y_increase){
        printf("augmented y\n");
        map->y_increase++;
    }
    if(h->pos->x <= 0 - map->x_decrease){
        printf("decreased x\n");
        map->x_decrease++;
    }
    if(h->pos->y <= 0 - map->y_decrease){
        printf("decreased y\n");
        map->y_decrease++;
    }
    
}

void game_start(Hero *h, Map *m)
{
    char c[12];
    printf("Welcome to the Rahan Game !\n");
    printf("Type the word \'AUBE\' to start the game: ");
    scanf("%10s", c);
    while (strcmp(c, "AUBE") != 0)
    {
        printf("Sorry, you cannot start the game with this command!\nTry one more time: ");
        scanf("%10s", c);
    }

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    render_map(m);
    printf("THE GAME BEGINS\n");

    while (!isDead(h))
    {
        printf("\nYour command: ");
        scanf("%10s", c);

        if (strcmp(c, "CREPUSCULE") == 0)
        {
            printf("\nYou decided to end up the game, thank you and our team are waiting for you again!\n");
            break;
        }
        else if (strcmp(c, "HAUT") == 0)
        {
            movement(h, 1, m);
        }
        else if (strcmp(c, "BAS") == 0)
        {
            movement(h, 2, m);
        }
        else if (strcmp(c, "DROIT") == 0)
        {
            movement(h, 3, m);
        }
        else if (strcmp(c, "GAUCHE") == 0)
        {
            movement(h, 4, m);
        }
        else if (strcmp(c, "VISION") == 0)
        {
            render_map(m);
        }
        else if (strcmp(c, "INVOCATION") == 0)
        {
            print_hero_stats(m);
        }
        else
        {
            printf("\nUnknown command, please try again.\nAllowed commands are: AUBE (start game), CREPUSCULE (finish game),\nVISION (print map), INVOCATION (stats of player),\nHAUT (make a step up), BAS (make a step down),\nGAUCHE (make a step left), DROITE (make a step right).\n");
        }
    }
}