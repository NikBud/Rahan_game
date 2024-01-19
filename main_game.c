#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include "libs/main_game.h"

static int itemsCount;
static int monstersCount;
static int rocksCount;
static int foodCount;
 
int isDead(Map* m)
{
    Hero* h = m->hero;
    if (h->current_hp <= 0)
        return 1;
    return 0;
}

int isVictory(Map *m)
{
    return m->hero->victories_count == m->monster_list_size;
}

int desired_x_pos(int current_x, int direction)
{
    if (direction == 1)
        current_x -= 1;
    else if (direction == 2)
        current_x += 1;
    return current_x;
}

int desired_y_pos(int current_y, int direction)
{
    if (direction == 3)
        current_y += 1;
    else if (direction == 4)
        current_y -= 1;
    return current_y;
}

int isEmptyFile(char* filename){
    char line[100];
    FILE* file;

    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open the file for reading\n");
    }

    if (fgets(line, sizeof(line), file) != NULL){
        return 0;
    }
    return 1;
}

void improve_hero(Hero *h, char *stat_to_improve, int stat_bonus)
{
    if (strcmp(stat_to_improve, "speed") == 0)
        h->speed = stat_bonus + 1;
    else if (strcmp(stat_to_improve, "hp") == 0)
        h->max_hp = stat_bonus + 50;
    else
        h->force = stat_bonus + 10;
}

int battle_init(Map *map, Monster *m)
{
    Hero* h = map->hero;
    while (1)
    {
        m->hp = m->hp - h->force;
        if (m->hp <= 0)
        {
            printf("\nA solid victory !\nRahan defeated %s\n", m->name);
            h->victories_count++;
            return 1;
        }
        h->current_hp = h->current_hp - m->damage;
        if (isDead(map))
        {
            printf("\nRahan suffered a mortal wound inflicted by %s\n", m->name);
            return 0;
        }
    }
}

void handle_food_case(Map *m, int i)
{
    Hero *h;
    Food *f;
    int calc_heal;

    h = m->hero;
    f = (Food *)m->positions[i].obj;
    calc_heal = 0;

    if (h->current_hp < h->max_hp)
    {
        if (h->current_hp + f->heal > h->max_hp)
        {
            calc_heal = h->max_hp - h->current_hp;
            h->current_hp = h->max_hp;
            f->symbol = ' ';
            f->pos->x = 1000;
            printf("\nHealed Rahan for %i\n", calc_heal);
        }
        else
        {
            h->current_hp = h->current_hp + f->heal;
            f->symbol = ' ';
            f->pos->x = 1000;
            printf("\nHealed Rahan for %i\n", f->heal);
        }
    }
    else if (h->current_hp == h->max_hp)
    {
        printf("\nRahan doesn't feel hungry right now\n");
        f->pos->x = 1000;
    }
}

void handle_item_case(Map *m, int i)
{
    Hero *h;
    Item *itm;
    int type, j;
    Item existed_itm;
    char *item_bonus_types[3];
    
    h = m->hero;
    itm = (Item *)m->positions[i].obj;
    type = itm->type;
    existed_itm = h->items[type];

    item_bonus_types[0] = "speed";
    item_bonus_types[1] = "hp";
    item_bonus_types[2] = "force";

    if (existed_itm.stat_bonus < itm->stat_bonus)
    {
        h->items[type].symbol = itm->symbol;
        h->items[type].stat_bonus = itm->stat_bonus;
        h->items[type].type = itm->type;
        for(j = 0; j < 100; j++){
            h->items[type].description[j] = itm->description[j];
        }

        if (existed_itm.stat_bonus == 0)
            h->items_count++;
        improve_hero(h, item_bonus_types[type], h->items[type].stat_bonus);
        printf("\nCongrarulations! You have new item in your bag!\n");
        printf("It's name is: %s", h->items[type].description);
        printf("It gives to you %s bonus + %d\n", item_bonus_types[type], h->items[type].stat_bonus);
    }
    else
    {
        printf("\nIt is item on your way!\n");
        printf("But there is already an item of the same type in your bag that is stronger than the one you just encountered.\n");
    }
    itm->pos->x = 1000;
}

void handle_monster_case(Map *m, int i)
{
    Monster *mnstr;

    mnstr = (Monster *)m->positions[i].obj;

    battle_init(m, mnstr);
    mnstr->pos->x = 1000;
}

void check_map_size(Map *m)
{
    Hero *h;
    h = m->hero;

    if (h->pos->x >= m->size_x + m->x_increase)
        m->x_increase++;
    if (h->pos->y >= m->size_y + m->y_increase)
        m->y_increase++;
    if (h->pos->x < 0 - m->x_decrease)
        m->x_decrease++;
    if (h->pos->y < 0 - m->y_decrease)
        m->y_decrease++;
}

void movement(int direction, Map *map)
{
    Hero* h = map->hero;
    int i, j, flag, calc_heal, xd, yd, current_speed;
    current_speed = h->speed;
    j = 0;
    while (j < current_speed && !isDead(map) && !isVictory(map))
    {
        xd = desired_x_pos(h->pos->x, direction);
        yd = desired_y_pos(h->pos->y, direction);
        flag = calc_heal = 0;

        for (i = 0; i < map->position_list_size; i++)
        {
            if (map->positions[i].x == xd && map->positions[i].y == yd)
            {
                if (map->positions[i].symbol == '#')
                {
                    printf("\nThere is a rock on your way !\n");
                    flag = 1;
                }
                else if (map->positions[i].symbol == '*')
                    handle_food_case(map, i);
                else if (map->positions[i].symbol == '!')
                    handle_item_case(map, i);
                else if (map->positions[i].symbol == '@')
                    handle_monster_case(map, i);
                break;
            }
        }

        if (!flag)
        {
            h->pos->x = xd;
            h->pos->y = yd;
        }
        check_map_size(map);
        j++;
    }
}

Game_History* init_gh(){
    Game_History* gh;
    gh = stdprof_malloc(sizeof(Game_History));
    gh->head = NULL;
    gh->size = 0;
    
    return gh;
}

void add_new_checkpoint(Map *m, Game_History *gh)
{
    Map_Cell *mc;

    if (gh->size < 3)
        gh->size++;
    else
    {
        Map_Cell *second = gh->head->next;
        release_MapCell_memory(second->next);
        second->next = NULL;
    }
    mc = stdprof_malloc(sizeof(Map_Cell));
    mc->map = m;
    mc->next = gh->head;
    gh->head = mc;
}

Map* beginFromSavedChanges(Map* m, Game_History* gh){
    char c[12];
    if (isEmptyFile("txts/checkpoint.txt") == 0){
        printf("You have saved progress, would you like to start the game from there?\n");
        printf("Your decision(YES/NO): ");
        scanf("%10s", c);
        if (strcmp(c, "YES") == 0)
        {
            Map* cpy = restore_map(foodCount, monstersCount, itemsCount, rocksCount);
            release_final_map_memory(m, foodCount, monstersCount, itemsCount, rocksCount);
            release_GameHistory_memory(gh);

            printf("\nData was successfully read\n");
            return cpy;
        }
    }
    return NULL;
}

void game_plot(Map *m, Game_History *gh)
{
    Hero *h;
    char c[12];
    Map* mapToRestoreChanges;

    h = m->hero;
    printf("Welcome to the Rahan Game !\n");
    printf("Type the word \'AUBE\' to start the game: ");
    scanf("%10s", c);
    while (strcmp(c, "AUBE") != 0)
    {
        printf("Sorry, you cannot start the game with this command!\nTry one more time: ");
        scanf("%10s", c);
    }

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

    mapToRestoreChanges = beginFromSavedChanges(m, gh);
    if (mapToRestoreChanges != NULL)
    {
        m = mapToRestoreChanges;
        gh = init_gh();
    }

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

    render_map(m);
    printf("THE GAME BEGINS\n");

    while (!isDead(m) && !isVictory(m))
    {
        h = m->hero;
        printf("\nYour command: ");
        scanf("%10s", c);

        if (strcmp(c, "CREPUSCULE") == 0 || strcmp(c, "C") == 0)
        {
            printf("\nYou decided to end up the game, thank you and our team are waiting for you again!\n");
            break;
        }
        else if (strcmp(c, "HAUT") == 0 || strcmp(c, "BAS") == 0 || strcmp(c, "DROIT") == 0 || strcmp(c, "GAUCHE") == 0 || strcmp(c, "H") == 0 || strcmp(c, "B") == 0 || strcmp(c, "D") == 0 || strcmp(c, "G") == 0)
        {
            Map *copy = copy_map(m, foodCount, monstersCount, itemsCount, rocksCount);
            add_new_checkpoint(copy, gh);
            if (strcmp(c, "HAUT") == 0 || strcmp(c, "H") == 0)
                movement(1, m);
            else if (strcmp(c, "BAS") == 0 || strcmp(c, "B") == 0)
                movement(2, m);
            else if (strcmp(c, "DROIT") == 0 || strcmp(c, "D") == 0)
                movement(3, m);
            else if (strcmp(c, "GAUCHE") == 0 || strcmp(c, "G") == 0)
                movement(4, m);
        }
        else if (strcmp(c, "VISION") == 0 || strcmp(c, "V") == 0)
            render_map(m);
        else if (strcmp(c, "INVOCATION") == 0 || strcmp(c, "I") == 0)
            print_hero_stats(m);
        else if (strcmp(c, "SAVE") == 0 || strcmp(c, "S") == 0){
            upload_changes(m);
            printf("\nChanges was successfully uploaded!\n");
        }
        else if (strcmp(c, "RESTORE") == 0 || strcmp(c, "R") == 0){
            Map* cpy;
            if (isEmptyFile("txts/checkpoint.txt") == 1){
                printf("\nSory, you cannot restore saved changes, because file with changes is empty.\n");
                continue;
            }

            cpy = restore_map(foodCount, monstersCount, itemsCount, rocksCount);
            release_GameHistory_memory(gh);
            release_final_map_memory(m, foodCount, monstersCount, itemsCount, rocksCount);
            m = cpy;
            gh = init_gh();

            render_map(m);
            print_hero_stats(m);

            printf("\nData was successfully read\n");
        }
        else if (strcmp(c, "ANNULER") == 0 || strcmp(c, "A") == 0)
        {
            if (gh->size == 0)
            {
                printf("Sorry, you can undo the last 3 steps at most.\n");
                printf("Of course, you also need to take these 3 steps in order to cancel one of them :)\n");
            }
            else
            {
                Map_Cell *mc = gh->head;
                gh->head = gh->head->next;
                gh->size--;
                render_map(mc->map);
                release_map_memory(m);
                m = mc->map;
                stdprof_free(mc);
            }
        }
        else
            printf("\nUnknown command, please try again.\nAllowed commands are: AUBE (start game), CREPUSCULE (finish game),\nVISION (print map), INVOCATION (stats of player),\nSAVE (to save your progress and next time start game from point of your progress),\nRESTORE (to restore saved data from file and start the game from the point of your progress),\nANNELER (to cancel your last step),\nHAUT (make a step up), BAS (make a step down),\nGAUCHE (make a step left), DROITE (make a step right).\n");
    }

    if (isDead(m))
        printf("\nRahan fought bravely, but unfortunately fell at the hands of his strongest enemies.\nGive Rahan a chance to try his luck again!\n");
    else if(isVictory(m))
        printf("\nThe game ends with a majestic victory for Rahan.\nHe managed to defeat all the enemies in his path and was able to maintain %d health.\n", h->current_hp);
    
    release_GameHistory_memory(gh);
    release_final_map_memory(m, foodCount, monstersCount, itemsCount, rocksCount);
}

void game_start(int fc, int mc, int ic, int rc)
{
    Map *m;
    Game_History *gh;

    foodCount = fc;
    monstersCount = mc;
    itemsCount = ic;
    rocksCount = rc;

    m = create_map(foodCount, monstersCount, itemsCount, rocksCount);
    m->size_x = 10;
    m->size_y = 10;
    gh = init_gh();

    game_plot(m, gh);
}
