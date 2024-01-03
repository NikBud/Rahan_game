#include<stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "create_map.h"

void create_unique_pos(Map* m) {
    Position* position_list;
    int pos_x, pos_y, j;

    j = 0;
    position_list = m->positions;
    pos_x = rand() % 10;
    pos_y = rand() % 10;

    for(j = 0; j < m->position_list_size; j++){
        if(position_list[j].x == pos_x && position_list[j].y == pos_y){
            pos_x = rand() % 10;
            pos_y = rand() % 10;
            j = 0;
        }
    }
    m->positions[m->position_list_size].x = pos_x;
    m->positions[m->position_list_size].y= pos_y;
}

void create_rocks(Map* map, int count){
    int i;
    Rock* rocks; 
    Position* position_list;

    position_list = map->positions;
    rocks = malloc(sizeof(Rock) * count);
    
    for(i = 0; i < count; i++){
        create_unique_pos(map);
        rocks[i].symbol = position_list[map->position_list_size].symbol = '#';
        position_list[map->position_list_size].obj = &rocks[i];
        rocks[i].pos = &position_list[map->position_list_size++];
    }
    map->rocks = rocks;
}

Monster generate_monster(Map* m, char* name, int dmg, int hp){
    Position* position_list;
    int position_list_size;
    Monster final;

    position_list = m->positions;
    position_list_size = m->position_list_size;
    
    create_unique_pos(m);
    final.damage = dmg;
    final.hp = hp;
    final.name = name;
    final.symbol = position_list[position_list_size].symbol = '@';
    final.pos = &position_list[position_list_size];
    return final;
}

Food generate_food(Map* m, char* name, char* description, int heal){
    Position* position_list;
    int position_list_size;
    Food final;

    position_list = m->positions;
    position_list_size = m->position_list_size;
    
    create_unique_pos(m);
    final.heal = rand() % 30;
    final.name = name;
    final.description = description;
    final.symbol = position_list[position_list_size].symbol = '*';
    final.pos = &position_list[position_list_size];
    return final;
}

Item generate_item(Map* m, char* description, int bonus, Item_Type type){
    Position* position_list;
    int position_list_size;
    Item final;

    position_list = m->positions;
    position_list_size = m->position_list_size;
    
    create_unique_pos(m);
    final.description = description;
    final.stat_bonus = bonus;
    final.type = type;
    final.symbol = position_list[position_list_size].symbol = '!';
    final.pos = &position_list[position_list_size];
    return final;
}

char* get_food_desc(int rando){
    int counter;
    char * line;
    FILE*fptr;

    counter = 0;
    line = malloc(sizeof(char) *100);
    fptr = fopen("foodesc.txt", "r");
    
    while (fgets(line, 100, fptr) != NULL){
        if (counter == rando){
            fclose(fptr);
            return line;
        }
        counter++;
    }

    fclose(fptr);
    return NULL;
}

char* get_name(int i, int rando){
    FILE*fptr;
    int counter;
    char * line;

    line = malloc(sizeof(char) *100);
    counter = 0;
    
    switch(i){
        case 1:
        fptr = fopen("monsternames.txt", "r");
        break;
        case 2:
        fptr = fopen("foodnames.txt", "r");
        break;
        case 3:
        fptr = fopen("itemnames.txt", "r");
        break;
        default:
        fptr = fopen("monsternames.txt", "r");
        break;
    }

    while (fgets(line, 100, fptr) != NULL){
        if (counter == rando){
            fclose(fptr);
            return line;
        }
        counter++;
    }

    fclose(fptr);
    return NULL;
}

void create_monsters(Map* m, int count){
    Position* position_list;
    Monster* m1;
    int i, r;

    position_list = m->positions;
    m1 = malloc(sizeof(Monster) * count);
    
    for (i = 0; i<count; i++){
        r = rand() % 100;
        m1[i] = generate_monster(m, get_name(1, r), rand()%20, rand()%50);
        position_list[m->position_list_size++].obj = &m1[i];
    }

    m->monsters = m1;
}
void create_food(Map* m, int count){
    Position* position_list;
    Food* f1;
    int i, r;

    position_list = m->positions;
    f1 = malloc(sizeof(Food) * count);

    for (i = 0; i<count; i++){
        r = rand() % 10;
        f1[i] = generate_food(m, get_name(2, r), get_food_desc(r), r*2);
        position_list[m->position_list_size++].obj = &f1[i]; 
    }
    m->food = f1;
}

void create_items(Map* m, int count){
    Position* position_list;
    Item* i1;
    Item_Type itm_type;
    int i, r, bonus, cycle;

    cycle = 1;
    i1 = malloc(sizeof(Item) * count);
    position_list = m->positions;

    for (i = 0; i < count; i++){
        cycle = i % 3;
        itm_type = cycle;
        r = rand() % 25;
        bonus = (rand() % 4) + 1;
        switch(cycle){
            case 0:
                i1[i] = generate_item(m, get_name(3, 2*r), bonus + 1, itm_type);
            case 1:
                i1[i] = generate_item(m, get_name(3, 50 + r), bonus + 1, itm_type);
            case 2:
                i1[i] = generate_item(m, get_name(3, 75+r), bonus + 1, itm_type);
            default:
                i1[i] = generate_item(m, get_name(3, 2*r), bonus, itm_type);
        }
        position_list[m->position_list_size++].obj = &i1[i];
    }
    m->items = i1;
}

void create_rahan(Map* m){
    Hero* h;
    Item* itm;
    Position* position_list;
    int position_list_size;

    h = malloc(sizeof(Hero));
    itm = malloc(sizeof(Item) * 3);
    position_list = m->positions;
    position_list_size = m->position_list_size;
    
    h->max_hp = 50;
    h->current_hp = h->max_hp;
    h->force = 10;
    h->speed = 1;
    h->items = itm;
    position_list[position_list_size].x = position_list[position_list_size - 1].x - 1;
    position_list[position_list_size].y = position_list[position_list_size - 1].y;
    h->pos = &position_list[position_list_size];
    position_list[position_list_size].obj = h;
    h->symbol = position_list[position_list_size].symbol = 'R';

    m->position_list_size++;
    m->hero = h;
}

void create_arbre_olivier(Map* m){
    Position* position_list;
    position_list = m->positions;
    position_list[m->position_list_size].x = 5;
    position_list[m->position_list_size].y= 4;
    position_list[m->position_list_size++].symbol = 'Y';
}

Map* create_map() {
    Map* game_map;
    srand(time(NULL));
    
    game_map = malloc(sizeof(Map));
    game_map->positions = malloc(16 * sizeof(Position));
    game_map->position_list_size = 0;

    game_map->x_decrease = 0;
    game_map->y_decrease = 0;
    game_map->x_increase = 0;
    game_map->y_increase = 0;
    game_map->monster_list_size = 3;

    create_arbre_olivier(game_map);
    create_rahan(game_map);
    create_rocks(game_map, 4);
    create_monsters(game_map, 3);
    create_food(game_map, 2);
    create_items(game_map, 4);

    return game_map;
}






