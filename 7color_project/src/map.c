#include "../head/map.h"
#include <stdlib.h>
#include <stdio.h>
#include "../head/display.h"
#include "../head/game.h"

Map map = {.map = NULL, .size = 0};

int GR6_numCouleur=0;		//la couleur associée à un numéro qui est stocké dans cette variable

void create_empty_map (Map* map, int size)
{	
	map->map = malloc(sizeof(Color) * (size * size));	//allouant sur le tas l’espace nécessaire pour un terrain de jeu carré de côté size.
	map->size=size;
}
void set_map_value (Map* map, int x, int y, Color value)
{
	map->map[(map->size)*y +x]=value;	//se positionner au bon endroit en fonction de la valeur de x et y
}

Color get_map_value (Map* map, int x, int y){
	if (map -> map == NULL || x > map -> size || y > map -> size)
	{
		printf("[ERROR] map not big enough or not initialized %p %i access (%i %i)", map -> map, map -> size, x, y);
		return ERROR;
	}
	return map -> map[y * map -> size + x];
}
void fill_map(Map* map)
{
	//remplir la carte de valeurs aléatoires
	for(int y=0; y<map->size;y++)
	{
		for(int x=0; x<map->size;x++)
		{
			GR6_numCouleur = rand()%7+3;	//nombre aléatoire entre 3 et 9 (donc plage de taille 7)
			set_map_value (map, x, y, GR6_numCouleur);
		}
	}

	//positionner les joueurs
	set_map_value (map, 0, map->size-1, 1);		//joueur 1 en bas à gauche
	set_map_value (map, map->size-1, 0, 2);		//joueur 2 en haut à droite
}


int main(int argc, char** argv)
{
	GR6_initialiser_jeu(&map, atoi(argv[1]));     //initialiser le jeu

	GR6_lancer_jeu(&map);    //lancer le jeu et gérer la partie

	GR6_cloturer_jeu(&map);     //cloturer le jeu, libère l'espace mémoire et affiche les résultats
}


