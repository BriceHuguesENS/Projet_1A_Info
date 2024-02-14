#include "../head/game.h"
#include <stdio.h>


void GR6_initialiser_jeu()     //fonction pour initialiser la carte et d'autres paramètres au début du jeu
{
    system("clear");	//effacer le contenu du terminal
	// Convertit l'argument de la ligne de commande en entier pour récupérer la taille de la carte choisie
    int taille_carte = atoi(argv[1]);

	int GR6_numCouleurChoisie = 0;	//variable pour enregistrer le choix de couleur du joueur
	int GR6_numeroJoueur = 1;	//c'est le joueur 1 ('v') qui commence la partie
	srand( time( NULL ) );		//initialiser la fonction rand sur le timer

	create_empty_map (&map, taille_carte);	//création de la carte
	fill_map(&map);		//remplie les cases de la carte
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