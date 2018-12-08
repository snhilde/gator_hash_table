#include "hash_table.h"

typedef struct _Item {
	char *key;
	char *value;
	struct _Item *next;
} Item;

struct _Table {
	size_t capacity;
	Item **items;
};

static Item *
create_item(const char *key, const char *value)
{
	Item *item;
	
	item = malloc(sizeof(*item));
	if (!item)
		return NULL;
	
	item->key = strdup(key);
	if (!item->key)
		return NULL;
	
	item->value = strdup(value);
	if (!item->value)
		return NULL;
	
	item->next = NULL;
	
	return item;
}

Table *
create_table(size_t size)
{
	Table *table;
	
	table = malloc(sizeof(*table));
	if (!table)
		return NULL;
	
	table->items = calloc(size, sizeof(*table->items));
	if (!table->items)
		return NULL;
	
	table->capacity = size;
	
	return table;
}

static size_t
enumerate(Table *table, int flag)
{
	size_t count = 0, i;
	Item **item, *list;
	
	if (flag)
		printf("\n*** all items in table: ***");
	
	for (i = 0, item = table->items; i < TABLESIZE; i++, item++)
		for (list = *item; list; list = list->next) {
			if (!flag)
				count++;
			if (flag)
				printf("\n\nkey: %s\nvalue: %s", list->key, list->value);
			}
	
	if (!flag)
		return count;
	if (flag)
		printf("\n*** end table ***\n");
	
	return 0;
}

size_t
count_items(Table *table)
{
	return enumerate(table, 0);
}

size_t
print_all(Table *table)
{
	return enumerate(table, 1);
}
	
static u_int64_t
calc_hash(const char *key)
{
	/* stub */
	
	u_int64_t hash;
	
	hash = key[0] ^ key[1] ^ key[2];
	
	return hash;
}

static Item *
get_item(Table *table, size_t index, const char *key)
{
	Item *item;
	
	item = table->items[index];
	
	while(item && strcmp(item->key, key))
		item = item->next;
	
	return item;
}

static size_t
get_index(Table *table, const char *key)
{
	u_int64_t hash;
	size_t index;
	
	hash = calc_hash(key);
	index = hash % table->capacity;
	
	return index;
}

void
link_in(Item **head, Item *item)
{
	while (*head && strcmp((*head)->key, item->key))
		head = &(*head)->next;
	
	*head = item;
}

void
unlink(Item **head, Item *item)
{
	while (strcmp((*head)->key, item->key))
		head = &(*head)->next;
	
	*head = item->next;
}

int
replace_value(Item *item, const char *value)
{
	free(item->value);
	item->value = strdup(value);
	if (!item->value)
		return -1;
	
	return 0;
}

int
insert_item(Table *table, const char *key, const char *value)
{
	size_t index;
	Item *item;
	
	index = get_index(table, key);
	item = get_item(table, index, key);
	
	if (item) {
		return replace_value(item, value);
	} else {
		item = create_item(key, value);
		if (!item)
			return -1;
		
		link_in(&table->items[index], item);
	}
	
	return 0;
}

char *
lookup(Table *table, const char *key)
{
	size_t index;
	Item *item;
	
	index = get_index(table, key);
	item = get_item(table, index, key);
	if (!item)
		return NULL;
	
	return item->value;
}

int
remove_item(Table *table, const char *key)
{
	size_t index;
	Item *item;
	
	index = get_index(table, key);
	item = get_item(table, index, key);
	if (!item)
		return -1;
	
	unlink(&table->items[index], item);
	
	free(item->key);
	free(item->value);
	free(item);
	
	return 0;
}
