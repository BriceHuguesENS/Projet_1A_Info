#include "../head/map.h"
#include <stdlib.h>
#include <stdio.h>
Map map = {.map = NULL, .size = 0};
void create_empty_map (Map* map, int size){}
void set_map_value (Map* map, int x, int y, Color value){}
Color get_map_value (Map* map, int x, int y){
	if (map -> map == NULL || x > map -> size || y > map -> size)
	{
		printf("[ERROR] map not big enough or not initialized %p %i access (%i %i)", map -> map, map -> size, x, y);
		return ERROR;
	}
	return map -> map[y * map -> size + x];
}
void fill_map(Map* map){}
int main(int argc, char** argv){
}

