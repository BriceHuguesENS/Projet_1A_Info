#include "../head/map.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../head/display.h"



Map map = {.map = NULL, .size = 0};

int GR6_numCouleur=0;		//la couleur associée à un numéro
int GR6_maj_monde(Map* map,int GR6_choixJoueur, int GR6_numeroJoueur);	//fonction pour mettre à jour la map après le coup d'un joueur

void create_empty_map (Map* map, int size)
{	
	map->map = malloc(sizeof(Color) * (size * size));
	//Color* GR6_Carte = malloc(sizeof(Color)*(size^2));
	map->size=size;
}
void set_map_value (Map* map, int x, int y, Color value)
{
	map->map[(map->size)*y +x]=value;
}

Color get_map_value (Map* map, int x, int y){
	if (map -> map == NULL || x >= map -> size || y >= map -> size || y < 0 || x < 0)
	{
		//printf("[ERROR] map not big enough or not initialized %p %i access (%i %i)", map -> map, map -> size, x, y);
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
	set_map_value (map, 0, map->size-1, 1);		//joueur 1
	set_map_value (map, map->size-1, 0, 2);		//joueur 2
}

int GR6_maj_monde(Map* map,int GR6_choixJoueur, int GR6_numeroJoueur)
{
	for(int y=0; y<map->size;y++)
	{
		for(int x=0; x<map->size;x++)
		{	
			int GR6_couleurCase = get_map_value (map, x, y);
			
			if(GR6_couleurCase == GR6_choixJoueur)		//si la case actuelle est celle jouée par le joueur en question
			{
				//vérification si elle est bien adjacente au territoire
				if(get_map_value (map, x+1, y)== GR6_numeroJoueur || 
				   get_map_value (map, x, y+1) == GR6_numeroJoueur ||
				   get_map_value (map, x-1, y) == GR6_numeroJoueur ||
				   get_map_value (map, x, y-1) == GR6_numeroJoueur)
				{
					set_map_value (map, x, y, GR6_numeroJoueur);	//le joueur en prend possession
					printf("Maj faite\n");
					return 1;	//signifie qu'il faut refaire une maj de la map pour vérification
				}
			}
		}
	}
	return 0;	//signifie qu'il NE faut PLUS refaire de maj de la map pour vérification
}

int GR6_determiner_si_jeu_fini(Map* map)		//fonction pour savoir si le jeu est fini
{
	//compteurs pour comptabiliser les territoires des 2 joueurs
	int GR6_compteurJ1=0;
	int GR6_compteurJ2=0;

	//analyse de la map
	for(int y=0; y<map->size;y++)
	{
		for(int x=0; x<map->size;x++)
		{
			if(get_map_value (map, x, y)== 1)
			{
				GR6_compteurJ1++;
				if(GR6_compteurJ1 > ((map->size*map->size)/2))	//si joueur occupe plus de 50%
				{
					return 1;	//fin de la partie
				}
			}
			if(get_map_value (map, x, y)== 2)
			{
				GR6_compteurJ2++;
				if(GR6_compteurJ2 > ((map->size*map->size)/2))	//si joueur occupe plus de 50%
				{
					return 2;	//fin de la partie
				}
			}
		}
	}
	//prise de décision sur l'état de la partie
	if((GR6_compteurJ1+GR6_compteurJ2) == ((map->size)*(map->size)))	//si tout le territoire est rempli
	{
		return 0;	//fin de la partie et égalité
	}
	return -1;		//la partie continue sinon
}

int main(int argc, char** argv)
{
	system("clear");	//effacer le contenu du terminal
	
	// Convertit l'argument de la ligne de commande en entier pour récupérer la taille de la carte choisie
    int taille_carte = atoi(argv[1]);

	int GR6_numCouleurChoisie = 0;	//variable pour enregistrer le choix de couleur du joueur
	int GR6_numeroJoueur = 1;	//c'est le joueur 1 ('v') qui commence la partie
	srand( time( NULL ) );		//initialiser la fonction rand sur le timer

	create_empty_map (&map, taille_carte);	//création de la carte
	fill_map(&map);		//remplie les cases de la carte


	////////////// Lancement de la partie	//////////////
	printf("Début de la partie \n\n");

	//Affichage de l'état actuel de la partie
	GR6_affchage_etat_actuel_partie(&map);
	
	while(GR6_determiner_si_jeu_fini(&map) == -1)		//tant que le jeu doit continuer
	{
		//Choix d'une couleur pour le joueur en qustion
		printf("\n\033[0mJoueur %i:\n\033[31m3:RED\n\033[32m4:GREEN\n\033[34m5:BLUE\n\033[33m6:YELLOW\n\033[35m7:MAGENTA\n\033[36m8:CYAN\n\033[37m9:WHITE\n\033[0m",GR6_numeroJoueur);
		scanf("%i", &GR6_numCouleurChoisie);	//récupérer le choix du joueur
		
		//mise à jour de la map
		while(GR6_maj_monde(&map, GR6_numCouleurChoisie,GR6_numeroJoueur)== 1)
		{
			//on repasse dans la boucle while pour refaire la maj, et on en sort
			//printf("Maj de la map en cours...");
		}

		system("clear");	//effacer le contenu du terminal
		printf("Jeu les 7 merveilles du monde des 7 couleurs \n\n");
		//Affichage de l'état actuel de la partie
		GR6_affchage_etat_actuel_partie(&map);

		//Changement de joueur
		GR6_numeroJoueur = 3 - GR6_numeroJoueur;	//passe ce numéro à 2 ou 1 en fonction de l'état au tour précédent
	}	
	switch (GR6_determiner_si_jeu_fini(&map))
	{
	case 1:
		printf("Fin de la partie !\nLe vainqueur est le joueur 1 \n");	
		break;

	case 2:
		printf("Fin de la partie !\nLe vainqueur est le joueur 2 \n");	
		break;
	
	case 0:
		printf("Fin de la partie !\nIl y a égalité \n");	
		break;
	}
	
	
	//libération de l'espace mémoire
	free(map.map);
	map.map = NULL;
	map.size = 0;
}


