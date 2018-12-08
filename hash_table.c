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
gatortable_create(size_t size)
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
	Item **list, *item;
	
	if (flag)
		printf("\n*** all items in table: ***");
	
	for (i = 0, list = table->items; i < table->capacity; i++, list++)
		for (item = *list; item; item = item->next) {
			if (!flag)
				count++;
			if (flag)
				printf("\n\nkey: %s\nvalue: %s", item->key, item->value);
			}
	
	if (!flag)
		return count;
	if (flag)
		printf("\n*** end table ***\n");
	
	return 0;
}

size_t
gatortable_count(Table *table)
{
	return enumerate(table, 0);
}

size_t
gatortable_print(Table *table)
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
	
	while(item && strcmp(item->key, key) != 0)
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

static void
link_in(Item **head, Item *item)
{
	if (*head)
		item->next = *head;
	
	*head = item;
}

static void
unlink(Item **head, Item *item)
{
	while (strcmp((*head)->key, item->key) != 0)
		head = &(*head)->next;
	
	*head = item->next;
}

static void
destroy_item(Item **head_item, Item *item)
{
	unlink(head_item, item);
	
	free(item->key);
	free(item->value);
	free(item);
}

static int
replace_value(Item *item, const char *value)
{
	free(item->value);
	item->value = strdup(value);
	if (!item->value)
		return -1;
	
	return 0;
}

int
gatortable_insert(Table *table, const char *key, const char *value)
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

const char *
gatortable_lookup(Table *table, const char *key)
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
gatortable_remove(Table *table, const char *key)
{
	size_t index;
	Item *item;
	
	index = get_index(table, key);
	item = get_item(table, index, key);
	if (!item)
		return -1;
	
	destroy_item(&table->items[index], item);
	
	return 0;
}

void
gatortable_destroy(Table *table)
{
	size_t i;
	Item **list;
	
	for (i = 0, list = table->items; i < table->capacity; i++, list++)
		while (*list)
			destroy_item(list, *list);
	
	free(table->items);
	free(table);
}
