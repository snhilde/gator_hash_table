#include "hash_table.h"

int
main(int argc, char *argv[])
{
	Table *table;
	
	table = create_table(capacity);
	if (!table)
		return 1;
	
	insert_item(table, "foo", "bar");
	printf("key: %s, value: %s\n", "foo", lookup(table, "foo"));
	printf("num items in table after insert: %ji\n", count_items(table));
	printf("\n");
	
	insert_item(table, "foo2", "bar2");
	printf("key: %s, value: %s\n", "foo2", lookup(table, "foo2"));
	printf("num items in table after insert: %ji\n", count_items(table));
	
	print_all(table);
	printf("\n");
	
	insert_item(table, "foo", "newbar");
	printf("key: %s, value: %s\n", "foo", lookup(table, "foo"));
	printf("num items in table after replace: %ji\n", count_items(table));
	
	print_all(table);
	printf("\n");
	
	remove_item(table, "foo");
	printf("num items in table after delete: %ji\n", count_items(table));
	print_all(table);
	
	return 0;
}
