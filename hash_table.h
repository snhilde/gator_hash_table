#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t capacity = 20;
typedef struct _Table Table;

Table * create_table(size_t);
int insert_item(Table *, const char *, const char *);
const char * lookup(Table *, const char *);
int remove_item(Table *, const char *);
size_t count_items(Table *);
size_t print_all(Table *);
