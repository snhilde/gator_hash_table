TARGET=hash_table

CC=gcc
DRIVER=driver.c

CFLAGS= -I. \
		-Wall \
		-g

@all:
	${CC} ${CFLAGS} -o ${TARGET} ${DRIVER} hash_table.c
