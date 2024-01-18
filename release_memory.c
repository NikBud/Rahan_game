#include "libs/release_memory.h"

void release_created_names(Map *m, int foodCount, int monstersCount, int itemsCount, int rocksCount)
{
    int i;
    for (i = 0; i < foodCount; i++)
    {
        stdprof_free(m->food[i].name);
        stdprof_free(m->food[i].description);
    }

    for (i = 0; i < itemsCount; i++)
    {
        stdprof_free(m->items[i].description);
    }

    for (i = 0; i < monstersCount; i++)
    {
        stdprof_free(m->monsters[i].name);
    }
}

void release_hero_item_names(Item* itm){
    int i;
    for (i = 0; i < 3; i++)
    {
        stdprof_free(itm[i].description);
    }
}

void release_map_memory(Map *m)
{
    stdprof_free(m->positions);
    stdprof_free(m->rocks);
    stdprof_free(m->food);
    stdprof_free(m->items);
    stdprof_free(m->monsters);
    release_hero_item_names(m->hero->items);
    stdprof_free(m->hero->items);
    stdprof_free(m->hero);
    stdprof_free(m);
}

void release_final_map_memory(Map* m, int foodCount, int monstersCount, int itemsCount, int rocksCount){
    release_created_names(m, foodCount, monstersCount, itemsCount, rocksCount);
    release_map_memory(m);
}

void release_MapCell_memory(Map_Cell *mc)
{
    if (mc != NULL)
    {
        release_map_memory(mc->map);
        release_MapCell_memory(mc->next);
        stdprof_free(mc);
    }
}

void release_GameHistory_memory(Game_History *gh)
{
    release_MapCell_memory(gh->head);
    stdprof_free(gh);
}
