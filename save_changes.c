#include "save_changes.h"
#include "create_map.h"
#include "print_map.h"
#include <string.h>

void read_food(FILE* file, Food* f){
    char line[100];
    int i;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "Food:") != NULL)
        {
            int count = atoi(&line[5]);

            for (i = 0; i < count; i++)
            {
                int j;
                fgets(line, sizeof(line), file);
                char* name = f[i].name;
                for(j = 0; j < 100; j++){
                    name[j] = line[j];
                }

                fgets(line, sizeof(line), file);
                char* desc = f[i].description;
                for(j = 0; j < 100; j++){
                    desc[j] = line[j];
                }

                fgets(line, sizeof(line), file);
                f[i].heal = atoi(&line[0]);

                fgets(line, sizeof(line), file);
                f[i].symbol = line[0];

                fgets(line, sizeof(line), file);
                f[i].pos->x = atoi(&line[0]);

                fgets(line, sizeof(line), file);
                f[i].pos->y = atoi(&line[0]);
            }
            break;
        }
    }
}

void read_rocks(FILE* file, Rock* r){
    char line[100];
    int i;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "Rocks:") != NULL)
        {
            int count = atoi(&line[6]);

            for (i = 0; i < count; i++)
            {
                fgets(line, sizeof(line), file);
                r[i].symbol = line[0];
                fgets(line, sizeof(line), file);
                r[i].pos->x = atoi(&line[0]);
                fgets(line, sizeof(line), file);
                r[i].pos->y = atoi(&line[0]);
            }
            break;
        }
    }
}

int lineToInt(char* str){
    int result = 0;
    while (*str != '\n') {
        if (*str >= '0' && *str <= '9') {
            result = result * 10 + (*str - '0');
        }
        str++;
    }
    return result;
}

void read_monsters(FILE* file, Monster* m){
    char line[100];
    int i;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "Monsters:") != NULL)
        {
            int count = atoi(&line[9]);

            for (i = 0; i < count; i++)
            {
                int j;
                fgets(line, sizeof(line), file);
                char* name = m[i].name;
                for(j = 0; j < 100; j++){
                    name[j] = line[j];
                }
                
                fgets(line, sizeof(line), file);
                m[i].hp = lineToInt(line);
                fgets(line, sizeof(line), file);
                m[i].damage = lineToInt(line);
                fgets(line, sizeof(line), file);
                m[i].symbol = line[0];
                fgets(line, sizeof(line), file);
                m[i].pos->x = lineToInt(line);
                fgets(line, sizeof(line), file);
                m[i].pos->y = lineToInt(line);
            }
            break;
        }
    }
}

void read_items(FILE* file, Item* itm){
    char line[100];
    int i;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "Items:") != NULL)
        {
            int count = atoi(&line[6]);

            for (i = 0; i < count; i++)
            {
                int j;
                fgets(line, sizeof(line), file);
                char* name = itm[i].description;
                for(j = 0; j < 100; j++){
                    name[j] = line[j];
                }
                
                fgets(line, sizeof(line), file);
                itm[i].type = lineToInt(line);
                fgets(line, sizeof(line), file);
                itm[i].stat_bonus = lineToInt(line);
                fgets(line, sizeof(line), file);
                itm[i].symbol = line[0];
                fgets(line, sizeof(line), file);
                itm[i].pos->x = lineToInt(line);
                fgets(line, sizeof(line), file);
                itm[i].pos->y = lineToInt(line);
            }
            break;
        }
    }
}

void read_hero(FILE* file, Hero* h){
    char line[100];
    
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strcmp(line, "Hero:") != 0)
        {
            fgets(line, sizeof(line), file);
            fgets(line, sizeof(line), file);
            h->max_hp = lineToInt(line);
            fgets(line, sizeof(line), file);
            h->current_hp = lineToInt(line);
            fgets(line, sizeof(line), file);
            h->force = lineToInt(line);
            fgets(line, sizeof(line), file);
            h->speed = lineToInt(line);
            fgets(line, sizeof(line), file);
            h->items_count = lineToInt(line);
            fgets(line, sizeof(line), file);
            h->victories_count = lineToInt(line);
            fgets(line, sizeof(line), file);
            h->symbol = line[0];
            fgets(line, sizeof(line), file);
            h->pos->x = lineToInt(line);
            fgets(line, sizeof(line), file);
            h->pos->y = lineToInt(line);
        }
        break;
    }
}

void read_hero_items(FILE* file, Item* itm){
    char line[100];
    int i;
    
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "Hero_Items:") != NULL)
        {
            int count = atoi(&line[11]);
            for (i = 0; i < count; i++)
            {
                int j;
                fgets(line, sizeof(line), file);
                if (strcmp(line, "null\n") == 0)
                {
                    itm[i].description = NULL;
                    itm[i].type = 0;
                    itm[i].stat_bonus = 0;
                    itm[i].symbol = ' ';
                    fgets(line, sizeof(line), file);
                    fgets(line, sizeof(line), file);
                    fgets(line, sizeof(line), file);
                }
                else{
                    char* desc = stdprof_malloc(100);
                    for(j = 0; j < 100; j++){
                        desc[j] = line[j];
                    }
                    itm[i].description = desc;
                    fgets(line, sizeof(line), file);
                    itm[i].type = lineToInt(line);
                    fgets(line, sizeof(line), file);
                    itm[i].stat_bonus = lineToInt(line);
                    fgets(line, sizeof(line), file);
                    itm[i].symbol = line[0];
                }
            }
            break;
        }
    }
}

void read_map_data(FILE* file, Map* m){
    char line[100];
    
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strcmp(line, "Map:") != 0)
        {
            fgets(line, sizeof(line), file);
            fgets(line, sizeof(line), file);
            m->monster_list_size = lineToInt(line);
            fgets(line, sizeof(line), file);
            m->position_list_size = lineToInt(line);
            fgets(line, sizeof(line), file);
            m->size_x = lineToInt(line);
            fgets(line, sizeof(line), file);
            m->size_y = lineToInt(line);
            fgets(line, sizeof(line), file);
            m->x_decrease = lineToInt(line);
            fgets(line, sizeof(line), file);
            m->x_increase = lineToInt(line);
            fgets(line, sizeof(line), file);
            m->y_decrease = lineToInt(line);
            fgets(line, sizeof(line), file);
            m->y_increase = lineToInt(line);
        }
        break;
    }
}

Map* restore_map(int foodCount, int monsterCount, int itemsCount, int rocksCount){
    FILE* file = fopen("checkpoint.txt", "r");
    int i;
    if (file == NULL) {
        fprintf(stderr, "Could not open the file for reading\n");
    }

    Map* m = create_map(foodCount, monsterCount, itemsCount, rocksCount);
    Hero* h = m->hero;
    read_food(file, m->food);
    read_rocks(file, m->rocks);
    read_monsters(file, m->monsters);
    read_items(file, m->items);

    //printf("%d\n%d\n%d\n%d\n%d\n%d\n%c\n%d\n%d\n", h->max_hp, h->current_hp, h->force, h->speed, h->items_count, h->victories_count, h->symbol, h->pos->x, h->pos->y);
    read_hero(file, m->hero);
    //printf("%d\n%d\n%d\n%d\n%d\n%d\n%c\n%d\n%d\n\n\n", h->max_hp, h->current_hp, h->force, h->speed, h->items_count, h->victories_count, h->symbol, h->pos->x, h->pos->y);


    read_hero_items(file, m->hero->items);
    /*for (i = 0; i < 3; i++)
    {
        Item tmp = m->hero->items[i];
        if (tmp.description == NULL)
        {
            printf("Item: %s\n%u\n%d\n%s\n", "null", tmp.type, tmp.stat_bonus, "null");
        }
        else{
            printf("Item: %s%u\n%d\n%c\n", tmp.description, tmp.type, tmp.stat_bonus, tmp.symbol);
        }
    }*/
    read_map_data(file, m);
    //printf("\n\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", m->monster_list_size, m->position_list_size, m->size_x, m->size_y, m->x_decrease, m->x_increase, m->y_decrease, m->y_increase);
    render_map(m);
    print_hero_stats(m);
    
    fclose(file);
    return m;
}

void upload_food(Food* f, FILE* file, int count){
    fprintf(file, "%s%d\n", "Food:", count);
    int i;
    for(i = 0; i < count; i++){
        Food tmp = f[i];
        fprintf(file, "%s%s%d\n%c\n%d\n%d\n", tmp.name, tmp.description, tmp.heal, tmp.symbol, tmp.pos->x, tmp.pos->y);
    }
    fprintf(file, "\n");
}

void upload_rocks(Rock* r, FILE* file, int count){
    fprintf(file, "%s%d\n", "Rocks:", count);
    int i;
    for(i = 0; i < count; i++){
        Rock tmp = r[i];
        fprintf(file, "%c\n%d\n%d\n", tmp.symbol, tmp.pos->x, tmp.pos->y);
    }
    fprintf(file, "\n");
}

void upload_monsters(Monster* m, FILE* file, int count){
    fprintf(file, "%s%d\n", "Monsters:", count);
    int i;
    for(i = 0; i < count; i++){
        Monster tmp = m[i];
        fprintf(file, "%s%d\n%d\n%c\n%d\n%d\n", tmp.name, tmp.hp, tmp.damage ,tmp.symbol, tmp.pos->x, tmp.pos->y);
    }
    fprintf(file, "\n");
}

void upload_items(Item* itm, FILE* file, int count){
    fprintf(file, "%s%d\n", "Items:", count);
    int i;
    for(i = 0; i < count; i++){
        Item tmp = itm[i];
        fprintf(file, "%s%u\n%d\n%c\n%d\n%d\n", tmp.description, tmp.type, tmp.stat_bonus, tmp.symbol, tmp.pos->x, tmp.pos->y);
    }
    fprintf(file, "\n");
}

void upload_hero_items(Item* itm, FILE* file, int count){
    fprintf(file, "%s%d\n", "Hero_Items:", count);
    int i;
    for(i = 0; i < count; i++){
        Item tmp = itm[i];
        if (tmp.description == NULL)
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
    FILE* f = fopen("checkpoint.txt", "w");
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