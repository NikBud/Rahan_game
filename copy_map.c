#include "copy_map.h"

Position* copy_pos(Map* copy_map, void* obj, void* new_obj, int obj_type){
    int pos_list_size;
    Rock* rocks;
    Monster* monsters;
    Food* food;
    Item* items;
    Hero* hero;

    Position* pos_to_copy, * copy;
    if (obj_type == 0)
    {
        rocks = (Rock*) obj;
        pos_to_copy = rocks->pos;
    }
    else if(obj_type == 1){
        monsters = (Monster*) obj;
        pos_to_copy = monsters->pos;
    }
    else if(obj_type == 2){
        food = (Food*) obj;
        pos_to_copy = food->pos;
    }
    else if(obj_type == 3){
        items = (Item*) obj;
        pos_to_copy = items->pos;
    }
    else{
        hero = (Hero*) obj;
        pos_to_copy = hero->pos;
    }
    copy = copy_map->positions;
    pos_list_size = copy_map->position_list_size;

    copy[pos_list_size].x = pos_to_copy->x;
    copy[pos_list_size].y = pos_to_copy->y;
    copy[pos_list_size].symbol = pos_to_copy->symbol;
    copy[pos_list_size].obj = new_obj;

    copy_map->position_list_size++;
    return &copy_map->positions[pos_list_size];
}

void copy_monsters(Map* map_to_copy, Map* copy_map, int monsters_count){
    int i;
    Monster *new_monsters, *monsters_to_copy;

    monsters_to_copy = map_to_copy->monsters;
    new_monsters = stdprof_malloc(sizeof(Monster) * monsters_count);

    for(i = 0; i < monsters_count; i++){
        new_monsters[i].symbol = monsters_to_copy[i].symbol;
        new_monsters[i].name = monsters_to_copy[i].name;
        new_monsters[i].damage = monsters_to_copy[i].damage;
        new_monsters[i].hp = monsters_to_copy[i].hp;
        new_monsters[i].pos = copy_pos(copy_map, &monsters_to_copy[i], &new_monsters[i], 1);
    }
    copy_map->monsters = new_monsters;
}

void copy_rocks(Map* map_to_copy, Map* copy_map, int rocks_count){
    int i;
    Rock *new_rocks, *rocks_to_copy;

    new_rocks = stdprof_malloc(sizeof(Rock) * rocks_count);
    rocks_to_copy = map_to_copy->rocks;

    for(i = 0; i < rocks_count; i++){
        new_rocks[i].symbol = rocks_to_copy[i].symbol;
        new_rocks[i].pos = copy_pos(copy_map, &rocks_to_copy[i], &new_rocks[i], 0);
    }
    copy_map->rocks = new_rocks;
}

void copy_items(Map* map_to_copy, Map* copy_map, int items_count){
    int i;
    Item *new_items, *items_to_copy;

    new_items = stdprof_malloc(sizeof(Item) * items_count);
    items_to_copy = map_to_copy->items;
    
    for(i = 0; i < items_count; i++){
        new_items[i].symbol = items_to_copy[i].symbol;
        new_items[i].type = items_to_copy[i].type;
        new_items[i].description = items_to_copy[i].description;
        new_items[i].stat_bonus = items_to_copy[i].stat_bonus;
        new_items[i].pos = copy_pos(copy_map, &items_to_copy[i], &new_items[i], 3);
    }
    copy_map->items = new_items;
}

void copy_food(Map* map_to_copy, Map* copy_map, int food_count){
    int i;
    Food *new_food, *food_to_copy;

    new_food = stdprof_malloc(sizeof(Food) * food_count);
    food_to_copy = map_to_copy->food;
    
    for(i = 0; i < food_count; i++){
        new_food[i].symbol = food_to_copy[i].symbol;
        new_food[i].name = food_to_copy[i].name;
        new_food[i].description = food_to_copy[i].description;
        new_food[i].heal = food_to_copy[i].heal;
        new_food[i].pos = copy_pos(copy_map, &food_to_copy[i], &new_food[i], 2);
    }
    copy_map->food = new_food;
}

void copy_hero_items(Hero* hero_to_copy, Hero* new_hero){
    int i, j;
    Item *items_to_copy, *new_items;

    items_to_copy = hero_to_copy->items;
    new_items = stdprof_malloc(sizeof(Item) * 3);
    new_hero->items_count = hero_to_copy->items_count;
    for (i = 0; i < 3; i++){
        new_items[i].description = stdprof_malloc(100);
    }

    for(i = 0; i < 3; i++){
        new_items[i].symbol = items_to_copy[i].symbol;
        new_items[i].type = items_to_copy[i].type;
        for(j = 0; j < 100; j++){
            new_items[i].description[j] = items_to_copy[i].description[j];
        }
        new_items[i].stat_bonus = items_to_copy[i].stat_bonus;
    }

    new_hero->items = new_items;
}

void copy_rahan(Map* map_to_copy, Map* copy_map){
    Hero* hero_to_copy, *new_hero;
    
    hero_to_copy = map_to_copy->hero;
    new_hero = stdprof_malloc(sizeof(Hero));

    new_hero->current_hp = hero_to_copy->current_hp;
    new_hero->force = hero_to_copy->force;
    new_hero->items_count = hero_to_copy->items_count;
    new_hero->max_hp = hero_to_copy->max_hp;
    new_hero->speed = hero_to_copy->speed;
    new_hero->symbol = hero_to_copy->symbol;
    new_hero->victories_count = hero_to_copy->victories_count;
    copy_hero_items(hero_to_copy, new_hero);
    new_hero->pos = copy_pos(copy_map, hero_to_copy, new_hero, 4);
    
    copy_map->hero = new_hero;
}

void copy_arbre_olivier(Map* m){
    Position* position_list;
    position_list = m->positions;
    position_list[m->position_list_size].x = 5;
    position_list[m->position_list_size].y= 4;
    position_list[m->position_list_size++].symbol = 'Y';
}

Map* copy_map(Map* m, int foodCount, int monstersCount, int itemsCount, int rocksCount){
    Map* map_copy;
    int pos_list_size;
    
    pos_list_size = 2 + foodCount + monstersCount + itemsCount + rocksCount;
    map_copy = stdprof_malloc(sizeof(Map));
    map_copy->positions = stdprof_malloc(pos_list_size * sizeof(Position));
    map_copy->monster_list_size = m->monster_list_size;

    copy_arbre_olivier(map_copy);
    copy_food(m, map_copy, foodCount);
    copy_items(m, map_copy, itemsCount);
    copy_rocks(m, map_copy, rocksCount);
    copy_monsters(m, map_copy, monstersCount);
    copy_rahan(m, map_copy);
    map_copy->x_decrease = m->x_decrease;
    map_copy->y_decrease = m->y_decrease;
    map_copy->x_increase = m->x_increase;
    map_copy->y_increase = m->y_increase;
    map_copy->size_x = m->size_x;
    map_copy->size_y = m->size_y;
    map_copy->position_list_size = m->position_list_size;

    return map_copy;
}
