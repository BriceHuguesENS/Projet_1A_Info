FLAGS=-Wall -Werror -lm -g

7color : o/map.o o/display.o o/game.o
	gcc $(FLAGS) o/map.o o/display.o o/game.o -o 7color

o/map.o: head/map.h src/map.c
	gcc $(FLAGS) -c src/map.c -o o/map.o

o/display.o: head/display.h src/display.c head/map.h
	gcc $(FLAGS) -c src/display.c -o o/display.o

o/game: head/game.h src/game.c head/map.head
	gcc $(FLAGS) -c src/game.c -o o/game.o
