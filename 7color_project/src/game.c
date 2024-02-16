#include "../head/game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../head/display.h"
#include "../head/ia.h"

int GR6_numCouleurChoisie = 0;	//variable pour enregistrer le choix de couleur du joueur
int GR6_numeroJoueur = 1;	//c'est le joueur 1 ('v') qui commence la partie

void GR6_initialiser_jeu(Map* map,int GR6_taille_carte)     //fonction pour initialiser la carte et d'autres paramètres au début du jeu
{
    system("clear");	//effacer le contenu du terminal
	srand( time( NULL ) );		//initialiser la fonction rand sur le timer
	create_empty_map (map, GR6_taille_carte);	//création de la carte
	fill_map(map);		//remplie les cases de la carte
}

int GR6_humain(Map* map, int GR6_numeroJoueur)
{
	//Affichage des choix de couleur disponible avec le chiffre correspondant
	printf("\n\033[31m3:🟥\n\033[32m4:🟩\n\033[34m5:🟦\n\033[33m6:🟨\n\033[35m7:🟪\n\033[36m8:🟫\n\033[37m9:⬜️\n\033[0m");
	//sélection de la couleur par le joueur ou l'ia
	printf("\n\033[0mJoueur %i, entrez votre couleur: ",GR6_numeroJoueur);
	scanf("%i", &GR6_numCouleurChoisie);	//récupérer le choix du joueur
	return GR6_numCouleurChoisie;
}

void GR6_lancer_jeu(Map* map)     //fonction pour lancer le jeu et gérer la partie en fonction du mode de jeu choisi
{
	printf("Jeu les 7 merveilles du monde des 7 couleurs \n\n");
	//Affichage de l'état actuel de la partie
	GR6_affchage_etat_actuel_partie(map);
	//Choix du mode de jeu
	int GR6_choix_mode_jeu = -1;
	printf("Veuillez sélectionner un mode de jeu: \n\n1:humain vs humain\n2:humain vs ia aléatoire\n3:humain vs ia glouton\n4:humain vs ia améliorée\n");
	scanf("%i",&GR6_choix_mode_jeu);
	system("clear");	//effacer le contenu du terminal

	int GR6_old_choix_mode_jeu = 0;
	int* GR6_pointeur_old = &GR6_old_choix_mode_jeu;
	*GR6_pointeur_old = GR6_choix_mode_jeu;
	printf("Début de la partie \n");
	
	
	while(GR6_determiner_si_jeu_fini(map) == -1)		//tant que le jeu doit continuer
	{
		switch (GR6_choix_mode_jeu)
		{
		case 1:
			GR6_numCouleurChoisie = GR6_humain(map, GR6_numeroJoueur);		//l'utilisateur joue un coup
			GR6_choix_mode_jeu = GR6_old_choix_mode_jeu;
			break;

		case 2:
			GR6_numCouleurChoisie = GR6_ia_aleatoire(map,GR6_numeroJoueur);		//l'ia aléatoire joue un coup
			GR6_choix_mode_jeu = 3 - GR6_choix_mode_jeu;
			break;

		case 3:
			GR6_numCouleurChoisie = GR6_ia_glouton(map,GR6_numeroJoueur);		//l'ia glouton joue un coup
			GR6_choix_mode_jeu = 4 - GR6_choix_mode_jeu;
			break;
		
		case 4:
			GR6_numCouleurChoisie = GR6_ia_smart(map,GR6_numeroJoueur);		//l'ia smart joue un coup
			GR6_choix_mode_jeu = 5 - GR6_choix_mode_jeu;
			break;
		}

		//mise à jour de la map
		while(GR6_maj_monde(map, GR6_numCouleurChoisie,GR6_numeroJoueur)== 1)
		{
			//on repasse dans la boucle while pour refaire la maj, et on en sort
			//printf("Maj de la map en cours...");
		}

		//system("clear");	//effacer le contenu du terminal
		printf("Jeu les 7 merveilles du monde des 7 couleurs \n\n");
		//Affichage de l'état actuel de la partie
		GR6_affchage_etat_actuel_partie(map);

		//Changement de joueur
		GR6_numeroJoueur = 3 - GR6_numeroJoueur;	//passe ce numéro à 2 ou 1 en fonction de l'état au tour précédent
	}	
}

void GR6_cloturer_jeu(Map* map)     //fonction pour cloturer le jeu
{
	//sélection de l'issue finale
	switch (GR6_determiner_si_jeu_fini(map))
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
	free(map->map);
	map->map = NULL;
}


int GR6_maj_monde(Map* map,int GR6_choixJoueur, int GR6_numeroJoueur)
{
	for(int y=0; y<map->size;y++)
	{
		for(int x=0; x<map->size;x++)
		{	
			if(GR6_get_map_value(map, x, y) == GR6_choixJoueur)		//si la case actuelle est celle jouée par le joueur en question
			{
				//vérification si elle est bien adjacente au territoire
				if(GR6_get_map_value(map, x+1, y)== GR6_numeroJoueur || 
				   GR6_get_map_value(map, x, y+1) == GR6_numeroJoueur ||
				   GR6_get_map_value(map, x-1, y) == GR6_numeroJoueur ||
				   GR6_get_map_value(map, x, y-1) == GR6_numeroJoueur)
				{
					set_map_value (map, x, y, GR6_numeroJoueur);	//le joueur en prend possession
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
			if(GR6_get_map_value(map, x, y)== 1)
			{
				GR6_compteurJ1++;
				if(GR6_compteurJ1 > ((map->size*map->size)/2))	//si joueur occupe plus de 50%
				{
					return 1;	//fin de la partie
				}
			}
			if(GR6_get_map_value(map, x, y)== 2)
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

Color GR6_get_map_value(Map* map, int x, int y)     //pour récupérer la valeur d'une cse du jeu, et -1 si on sort de la map (fait appel à get_map_value de map.c)
{
	if (map -> map == NULL || x >= map -> size || y >= map -> size || y < 0 || x < 0)
	{
		//printf("[ERROR] map not big enough or not initialized %p %i access (%i %i)", map -> map, map -> size, x, y);
		return ERROR;
	}
	//sinon
	return get_map_value(map, x, y);
}