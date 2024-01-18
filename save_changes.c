#include "save_changes.h"
#include "create_map.h"
#include "print_map.h"
#include <string.h>

void upload_food(Food* f, FILE* file, int count){
    int i;
    fprintf(file, "%s%d\n", "Food:", count);
    
    for(i = 0; i < count; i++){
        Food tmp = f[i];
        fprintf(file, "%s%s%d\n%c\n%d\n%d\n", tmp.name, tmp.description, tmp.heal, tmp.symbol, tmp.pos->x, tmp.pos->y);
    }
    fprintf(file, "\n");
}

void upload_rocks(Rock* r, FILE* file, int count){
    int i;
    fprintf(file, "%s%d\n", "Rocks:", count);
    
    for(i = 0; i < count; i++){
        Rock tmp = r[i];
        fprintf(file, "%c\n%d\n%d\n", tmp.symbol, tmp.pos->x, tmp.pos->y);
    }
    fprintf(file, "\n");
}

void upload_monsters(Monster* m, FILE* file, int count){
    int i;
    fprintf(file, "%s%d\n", "Monsters:", count);
    
    for(i = 0; i < count; i++){
        Monster tmp = m[i];
        fprintf(file, "%s%d\n%d\n%c\n%d\n%d\n", tmp.name, tmp.hp, tmp.damage ,tmp.symbol, tmp.pos->x, tmp.pos->y);
    }
    fprintf(file, "\n");
}

void upload_items(Item* itm, FILE* file, int count){
    int i;
    fprintf(file, "%s%d\n", "Items:", count);
    
    for(i = 0; i < count; i++){
        Item tmp = itm[i];
        fprintf(file, "%s%u\n%d\n%c\n%d\n%d\n", tmp.description, tmp.type, tmp.stat_bonus, tmp.symbol, tmp.pos->x, tmp.pos->y);
    }
    fprintf(file, "\n");
}

void upload_hero_items(Item* itm, FILE* file, int count){
    int i;
    fprintf(file, "%s%d\n", "Hero_Items:", count);
    
    for(i = 0; i < count; i++){
        Item tmp = itm[i];
        if (strcmp(tmp.description, "") == 0)
        {
            fprintf(file, "%s\n%u\n%d\n%s\n", "null", tmp.type, tmp.stat_bonus, "null");
        }
        else{
            fprintf(file, "%s%u\n%d\n%c\n", tmp.description, tmp.type, tmp.stat_bonus, tmp.symbol);
        }
    }
    fprintf(file, "\n");
}

void upload_hero(Hero* h, FILE* file){
    fprintf(file, "%s\n", "Hero:");
    fprintf(file, "%d\n%d\n%d\n%d\n%d\n%d\n%c\n%d\n%d\n", h->max_hp, h->current_hp, h->force, h->speed, h->items_count, h->victories_count, h->symbol, h->pos->x, h->pos->y);
}

void upload_map(Map* m, FILE* file){
    fprintf(file, "%s\n", "Map:");
    fprintf(file, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", m->monster_list_size, m->position_list_size, m->size_x, m->size_y, m->x_decrease, m->x_increase, m->y_decrease, m->y_increase);
}

void upload_changes(Map* m){
    FILE* f;
    f = fopen("txts/checkpoint.txt", "w");
    if (f == NULL) {
        fprintf(stderr, "Could not open the file for appending\n");
    }

    upload_food(m->food, f, 3);
    upload_rocks(m->rocks, f, 4);
    upload_monsters(m->monsters, f, 3);
    upload_items(m->items, f, 4);
    upload_hero(m->hero, f);
    upload_hero_items(m->hero->items, f, 3);
    upload_map(m, f);

    fclose(f);
}
