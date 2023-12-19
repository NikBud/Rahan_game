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
    char* name;
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
    Chaussures,
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
    Position* pos;
} Hero;

typedef struct map {
    int size;
    Item* items;
    Food* food;
    Monter* monsters;
    Rock* rocks;    
    Position* positions;
} Map;
