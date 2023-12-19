#include "types.h"

void render(Map m);
void create_rocks3(Map* map, Position* position_list, int position_list_size);
Rock* create_rocks(int count, Position* position_list, int position_list_size);
Rock* create_rocks2(Position** position_list, int position_list_size);
Map* create_map();