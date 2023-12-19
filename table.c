#include<stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "types.h"

void render(Map m){

}

void create_unique_pos(Position* position_list, int position_list_size) {
    int pos_x, pos_y, j;
    j = 0;
    pos_x = rand() % 10;
    pos_y = rand() % 10;
    for(j = 0; j < position_list_size; j++){
        if(position_list[j].x == pos_x && position_list[j].y == pos_y){
            pos_x = rand() % 10;
            pos_y = rand() % 10;
            j = 0;
        }
    }
    position_list[position_list_size].x = pos_x;
    position_list[position_list_size].y= pos_y;
}


void create_rocks(Map* map, Position* position_list, int position_list_size, int count){
    int i;
    Rock* rocks = malloc(sizeof(Rock) * count);
    
    for(i = 0; i < count; i++){
        create_unique_pos(position_list, position_list_size);
        rocks[i].symbol = position_list[position_list_size].symbol = '#';
        position_list[position_list_size].obj = &rocks[i];
        rocks[i].pos = &position_list[position_list_size++];
    }
    map->rocks = rocks;
}


void create_monsters(Map* m, Position* position_list, int position_list_size, int count){
    Monter* m1;
    m1 = malloc(sizeof(Monter) * count);

    m1[0].name = "Kraken";
    m1[0].damage = 10;
    m1[0].hp = 100;
    create_unique_pos(position_list, position_list_size);
    m1[0].symbol = position_list[position_list_size].symbol = '!';
    m1[0].pos = &position_list[position_list_size];
    position_list[position_list_size++].obj = m1;

    m->monsters = m1;
}


Map* create_map() {
    int position_list_size;
    Map* game_map;
    Position* position_list;

    position_list_size = 0;
    game_map = malloc(sizeof(Map));
    position_list = malloc(16 * sizeof(sizeof(Position)));

    srand(time(NULL));

    create_rocks(game_map, position_list, position_list_size, 4);
    position_list_size = 4;
    create_monsters(game_map, position_list, position_list_size, 1);
    position_list_size++;


    game_map->positions = position_list;


    return game_map;
}






