FLAGS=-Wall -Werror -lm -g

7color : o/map.o o/display.o o/game.o o/ia.o
	gcc $(FLAGS) o/map.o o/display.o o/game.o o/ia.o -o 7color


o/map.o: head/map.h src/map.c
	gcc $(FLAGS) -c src/map.c -o o/map.o

o/display.o: head/display.h src/display.c head/map.h
	gcc $(FLAGS) -c src/display.c -o o/display.o

o/game.o: head/game.h src/game.c head/map.h
	gcc $(FLAGS) -c src/game.c -o o/game.o

o/ia.o: head/ia.h src/ia.c head/map.h
	gcc $(FLAGS) -c src/ia.c -o o/ia.o
