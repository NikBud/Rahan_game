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
    int i;
    create_unique_pos(position_list, position_list_size);
    final.damage = dmg;
    final.hp = hp;
    final.name = name;
    final.symbol = position_list[position_list_size].symbol = '@';
    final.pos = &position_list[position_list_size];
    return final;
}
char* get_name(){
    int r;
    int counter = 0;
    char * line = malloc(sizeof(char) *100);
    FILE*fptr;
    fptr = fopen("monsternames.txt", "r");
    r = rand() % 17;
    while (fgets(line, 100, fptr) != NULL){
            if (counter == r){
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
    m1 = malloc(sizeof(Monter) * count);
    for (i = 0; i<count; i++){
        m1[i] = generate_monster(get_name(), rand()%20, rand()%50, position_list, position_list_size);
        position_list[position_list_size++].obj = &m1[i];    
    }

    m->monsters = m1;
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
    create_monsters(game_map, position_list, pos_list_size, 1);
    pos_list_size++;
    

    game_map->positions = position_list;
    game_map->position_list_size = pos_list_size;

    return game_map;
}






