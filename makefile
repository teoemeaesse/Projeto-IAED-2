CFLAGS = -g -Wall -Wextra -Werror -ansi -pedantic

proj: *.c *.h
	gcc $(CFLAGS) -o proj *.c
