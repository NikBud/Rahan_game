#include "print_map.h"

void print_hero_items(Hero* h){
    const char* item_types[3];
    Item* itm;
    int i, counter;

    itm = h->items;
    counter = 1;
    item_types[0] = "Chaussures";
    item_types[1] = "Protections";
    item_types[2] = "Armes";

    if(h->items_count == 0){
        printf("   At the moment, your hero has no items.\n");
        return;
    }

    for(i = 0; i < 3; i++){
        if (itm[i].stat_bonus != 0)
        {
            printf("   %d:\n", counter);        
            printf("   Type: %s\n", item_types[itm[i].type]);
            printf("   Description: %s", itm[i].description);
            printf("   Bonus: %c + %d\n\n", item_types[itm[i].type][0], itm[i].stat_bonus);
            counter++;
        }
    }
}

void print_hero_stats(Map* m){
    Hero* h;
    
    h = m->hero;
    printf("\nCurrent HP: %d;\n", h->current_hp);
    printf("Max HP: %d;\n", h->max_hp);
    printf("Force: %d;\n", h->force);
    printf("Speed: %d;\n", h->speed);
    printf("Current position x: %d;\n", h->pos->x);
    printf("Current position y: %d;\n", h->pos->y);
    printf("Items:\n"); print_hero_items(h);
}

char ifObjectPresentAtPosition(Map* m, int x, int y){
    int i;
    char chr;
    Position* p;
    
    chr = ' ';
    p = m->positions;
    
    for(i = 0; i < m->position_list_size; i++){
        Position c = p[i];
        if(c.x == x && c.y == y){
            chr = c.symbol;
        }
    }
    return chr;
}

void render_map(Map* m){
    int size_x, size_y, y_start, i, j;
    char chr;

    chr = ' ';
    size_x = m->size_x + m->x_increase;
    size_y = m->size_y + m->y_increase;

    for(i = 0 - m->x_decrease; i < size_x + 3; i++){
        if(i == 0 - m->x_decrease){
            printf("    ");
            for(j = 0 - m->y_decrease; j < size_y; j++){
                if (j < -9) printf("- ");
            }
            printf("\n");
            printf("    ");
            for(j = 0 - m->y_decrease; j < size_y; j++){
                if(j > 9) printf("%d ", j / 10);
                else if(j < 0 && j > -10) printf("- ");
                else if(j < -9) printf("%d ", -(j / 10));
                else printf("  ");
            }
            printf("\n");
            printf("    ");
            for(j = 0 - m->y_decrease; j < size_y; j++){
                if(j > 9) printf("%d ", j % 10);
                else if(j < 0) printf("%d ", -(j % 10));
                else printf("%d ", j);
            }
        }
        else if(i == 1 - m->x_decrease || i == size_x + 2){
            printf("   ");
            for(j = 0 - (m->y_decrease * 2); j < size_y * 2 + 1; j++){
                if(j % 2 == 0) printf("+");
                else printf("-");
            }
        }
        else{
            y_start = -1 * (m->y_decrease * 2);
            for(j = y_start; j < size_y * 2 + 2; j++){
                if(j == y_start){
                    if(i >= 2 && i < 12){
                        printf("  %d", i - 2);
                        continue;
                    }
                    else if((i < 2 && i > -8) || (i > 11 && i < 101)){
                        printf(" %d", i - 2);
                        continue;
                    }
                    else{
                        printf("%d", i - 2);
                    }
                }
                else if (j == y_start + 1 || j == size_y * 2 + 1){
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
