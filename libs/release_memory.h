#include "types.h"

void release_map_memory(Map *m);
void release_final_map_memory(Map* m, int foodCount, int monsterCount, int itemsCount, int rocksCount);
void release_GameHistory_memory(Game_History *gh);
void release_MapCell_memory(Map_Cell *mc);
