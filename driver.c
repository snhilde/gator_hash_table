#include "hash_table.h"

int
main(int argc, char *argv[])
{
	Table *table;
	
	table = gatortable_create(20);
	if (!table)
		return 1;
	
	gatortable_insert(table, "foo", "bar");
	printf("key: %s, value: %s\n", "foo", gatortable_lookup(table, "foo"));
	printf("num items in table after insert: %ji\n", gatortable_count(table));
	printf("\n");
	
	gatortable_insert(table, "foo2", "bar2");
	printf("key: %s, value: %s\n", "foo2", gatortable_lookup(table, "foo2"));
	printf("num items in table after insert: %ji\n", gatortable_count(table));
	
	gatortable_print(table);
	printf("\n");
	
	gatortable_insert(table, "foo", "newbar");
	printf("key: %s, value: %s\n", "foo", gatortable_lookup(table, "foo"));
	printf("num items in table after replace: %ji\n", gatortable_count(table));
	
	gatortable_print(table);
	printf("\n");
	
	gatortable_remove(table, "foo");
	printf("num items in table after delete: %ji\n", gatortable_count(table));
	gatortable_print(table);
	
	return 0;
}
