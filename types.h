#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "stdprof.h"

typedef struct pos{
    int x;
    int y;
    int dx;
    int dy;
    int dX;
    int dY;
    char symbol;
    void* obj;
} Position;

typedef struct enemy {
    char * name;
    char symbol;
    int damage;
    int hp;
    Position* pos;
} Monster;

typedef struct rock {
    char symbol;
    Position* pos;
} Rock;

typedef struct food {
    char* name;
    int heal;
    char symbol;
    char* description;
    Position* pos;
} Food;

typedef enum type{
    Chaussures = 0,
    Protections,
    Armes
} Item_Type;

typedef struct item{
    Item_Type type;
    int stat_bonus;
    char symbol;
    char* description;
    Position* pos;
} Item;

typedef struct hero{
    int max_hp;
    int current_hp;
    int force;
    int speed;
    char symbol;
    Item* items;
    int items_count;
    int victories_count;
    Position* pos;
} Hero;

typedef struct map {
    int size_x;
    int size_y;
    int x_increase;
    int y_increase;
    int x_decrease;
    int y_decrease;
    Hero* hero;
    Item* items;
    Food* food;
    Monster* monsters;
    int monster_list_size;
    Rock* rocks;    
    Position* positions;
    int position_list_size;
} Map;

typedef struct cell{
    Map* map;
    struct cell* next;
} Map_Cell;

typedef struct list{
    Map_Cell* head;
    int size;
} Game_History;

#endif
