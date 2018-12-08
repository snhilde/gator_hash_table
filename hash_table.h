#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Table Table;

Table * gatortable_create(size_t);
int gatortable_insert(Table *, const char *, const char *);
const char * gatortable_lookup(Table *, const char *);
int gatortable_remove(Table *, const char *);
size_t gatortable_count(Table *);
size_t gatortable_print(Table *);
