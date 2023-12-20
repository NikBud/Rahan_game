#include<stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "table.h"

char ifObjectPresentAtPosition(Map* m, int x, int y){
    int i;
    char chr;
    chr = ' ';
    Position* p = m->positions;
    for(i = 0; i < m->position_list_size; i++){
        Position c = p[i];
        if(c.x == x && c.y == y){
            chr = c.symbol;
        }
    }
    return chr;
}

void render_map(Map* m){
    int size, i, j; 
    char chr;
    chr = ' ';
    size = m->size;
    for(i = 0; i < size + 3; i++){
        if(i == 0){
            printf("  ");
            for(j = 0; j < size; j++){
                printf("%d ", j);
            }
        }
        else if(i == 1 || i == size + 2){
            printf(" ");
            for(j = 0; j < size * 2 + 1; j++){
                if(j % 2 == 0) printf("+");
                else printf("-");
            }
        }
        else{
            for(j = 0; j < size * 2 + 2; j++){
                if(j == 0){
                    printf("%d", i - 2);
                    continue;
                }
                else if (j == 1 || j == size * 2 + 1){
                    printf("|");
                    continue;
                }
                else if (j % 2 == 0){
                    chr = ifObjectPresentAtPosition(m, i - 2, j / 2 - 1);
                    printf("%c", chr);
                }
                else{
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
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

Monter generate_monster(char* name, int dmg, int hp, Position* position_list, int position_list_size){
    Monter final;
    create_unique_pos(position_list, position_list_size);
    final.damage = dmg;
    final.hp = hp;
    final.name = name;
    final.symbol = position_list[position_list_size].symbol = '@';
    final.pos = &position_list[position_list_size];
    return final;
}
Food generate_food(char* name, char* description, int heal, Position* position_list, int position_list_size){
    Food final;
    create_unique_pos(position_list, position_list_size);
    final.heal = rand() % 30;
    final.name = name;
    final.description = description;
    final.symbol = position_list[position_list_size].symbol = '*';
    final.pos = &position_list[position_list_size];
    return final;
}
Item generate_item(char* description, int bonus, Item_Type type, Position* position_list, int position_list_size){
    Item final;
    create_unique_pos(position_list, position_list_size);
    final.description = description;
    final.stat_bonus = bonus;
    final.type = type;
    final.symbol = position_list[position_list_size].symbol = '!';
    final.pos = &position_list[position_list_size];
    return final;
}
char* get_food_desc(int rando){
    int counter = 0;
    char * line = malloc(sizeof(char) *100);
    FILE*fptr;
    fptr = fopen("foodesc.txt", "r");
    while (fgets(line, 100, fptr) != NULL){
            if (counter == rando){
                printf("generated: %s\n", line);
                fclose(fptr);
                return line;
            }
            else{
                counter++;
            }
    }
    fclose(fptr);
    return NULL;
}
char* get_name(int i, int rando){
    int counter = 0;
    char * line = malloc(sizeof(char) *100);
    FILE*fptr;
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
                printf("generated: %s\n", line);
                fclose(fptr);
                return line;
            }
            else{
                counter++;
            }
    }
    fclose(fptr);
    return NULL;
}
void create_monsters(Map* m, Position* position_list, int position_list_size, int count){
    Monter* m1;
    int i;
    int r;
    m1 = malloc(sizeof(Monter) * count);
    for (i = 0; i<count; i++){
        r = rand() % 100;
        m1[i] = generate_monster(get_name(1, r), rand()%20, rand()%50, position_list, position_list_size);
        position_list[position_list_size++].obj = &m1[i];    
    }

    m->monsters = m1;
}
void create_food(Map* m, Position* position_list, int position_list_size, int count){
    Food* f1;
    int i;
    int r;
    f1 = malloc(sizeof(Food) * count);
    for (i = 0; i<count; i++){
        r = rand() % 10;
        f1[i] = generate_food(get_name(2, r), get_food_desc(r), r*2, position_list, position_list_size);
        position_list[position_list_size++].obj = &f1[i];    
    }
    m->food = f1;
}
void create_items(Map* m, Position* position_list, int position_list_size, int count){
    Item* i1;
    int i;
    int r;
    int bonus;
    int cycle = 1;
    i1 = malloc(sizeof(Item) * count);
    for (i = 0; i<count; i++){
        cycle = (i+1)%4;
        r = rand() % 25;
        bonus = rand() % 5;
        printf("%i\n", cycle);
        printf("Rand = %i\n", r);
        switch(cycle){
            case 1:
            i1[i] = generate_item(get_name(3, 2*r), bonus+1, Protections, position_list, position_list_size);
            position_list[position_list_size++].obj = &i1[i];  
            break;
            case 2:
            i1[i] = generate_item(get_name(3, 50 + r), bonus+1, Armes, position_list, position_list_size);
            position_list[position_list_size++].obj = &i1[i];  
            break;
            case 3:
            i1[i] = generate_item(get_name(3, 75+r), bonus+1, Chaussures, position_list, position_list_size);
            position_list[position_list_size++].obj = &i1[i];  
            break;
            default:
            i1[i] = generate_item(get_name(3, 2*r), bonus, Protections, position_list, position_list_size);
            position_list[position_list_size++].obj = &i1[i];  
            break;
        }
    }
    m->items = i1;
}



Map* create_map() {
    int pos_list_size;
    Map* game_map;
    Position* position_list;

    pos_list_size = 0;
    game_map = malloc(sizeof(Map));
    position_list = malloc(16 * sizeof(sizeof(Position)));

    srand(time(NULL));

    create_rocks(game_map, position_list, pos_list_size, 4);
    pos_list_size = 4;
    create_monsters(game_map, position_list, pos_list_size, 3);
    pos_list_size+=3;
    create_food(game_map, position_list, pos_list_size, 2);
    pos_list_size+=2;
    create_items(game_map, position_list, pos_list_size, 2);
    pos_list_size+=2;

    

    game_map->positions = position_list;
    game_map->position_list_size = pos_list_size;

    return game_map;
}






