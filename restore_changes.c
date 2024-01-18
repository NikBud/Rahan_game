#include "restore_changes.h"
#include "create_map.h"
#include "print_map.h"
#include <string.h>

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
                char* name;
                char* desc;

                fgets(line, sizeof(line), file);
                name = f[i].name;
                for(j = 0; j < 100; j++){
                    name[j] = line[j];
                }

                fgets(line, sizeof(line), file);
                desc = f[i].description;
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
                char* name;
                fgets(line, sizeof(line), file);
                name = m[i].name;
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
                char* name;
                fgets(line, sizeof(line), file);
                name = itm[i].description;
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
                    itm[i].type = 0;
                    itm[i].stat_bonus = 0;
                    itm[i].symbol = ' ';
                    fgets(line, sizeof(line), file);
                    fgets(line, sizeof(line), file);
                    fgets(line, sizeof(line), file);
                }
                else{
                    for(j = 0; j < 100; j++){
                        itm[i].description[j] = line[j];
                    }
  
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
    FILE* file;
    Map* m;

    file = fopen("txts/checkpoint.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open the file for reading\n");
    }

    m = create_map(foodCount, monsterCount, itemsCount, rocksCount);
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
        if (strcmp(tmp.description, "") == 0)
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
