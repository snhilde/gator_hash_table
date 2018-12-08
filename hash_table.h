#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Table Table;

Table * gatortable_create(size_t capacity);
int gatortable_insert(Table * table, const char *key, const char *value);
const char * gatortable_lookup(Table *table, const char *key);
int gatortable_remove(Table *table, const char *key);
size_t gatortable_count(Table *table);
size_t gatortable_print(Table *table);
