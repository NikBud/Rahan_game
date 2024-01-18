#include <stddef.h>

void *stdprof_malloc_fonction(size_t, int, char*);
#define stdprof_malloc(T) stdprof_malloc_fonction(T, __LINE__, __FILE__)

void stdprof_free(void *);
void stdprof_afficher();
