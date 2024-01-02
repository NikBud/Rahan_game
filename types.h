#include<stdio.h>
#include <stdlib.h>
#include <limits.h>

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
} Monter;

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
    int x_toPlace;
    int y_toPlace;
    Hero* hero;
    Item* items;
    Food* food;
    Monter* monsters;
    int monster_list_size;
    int food_list_size;
    int rock_list_size;
    int item_list_size;
    Rock* rocks;    
    Position* positions;
    int position_list_size;
} Map;
