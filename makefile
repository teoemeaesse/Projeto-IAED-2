CFLAGS = -g -Wall -Wextra -Werror -ansi -pedantic

proj: src/*.c src/*.h
	gcc $(CFLAGS) -o proj src/*.c 
