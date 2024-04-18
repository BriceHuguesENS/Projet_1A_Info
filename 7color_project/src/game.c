#include "../head/game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../head/display.h"
#include "../head/ia.h"

int GR6_numCouleurChoisie = 0;	//variable pour enregistrer le choix de couleur du joueur
int GR6_numeroJoueur = 1;	//c'est le joueur 1 🤑 qui commence la partie

void GR6_initialiser_jeu(Map* map,int GR6_taille_carte)     //initialiser la carte et d'autres paramètres au début du jeu
{
    system("clear");	//effacer le contenu du terminal
	srand( time( NULL ) );		//initialiser la fonction rand() sur le timer
	create_empty_map (map, GR6_taille_carte);	//création de la carte
	fill_map(map);		//remplit les cases de la carte
}

int GR6_humain(Map* map, int GR6_numeroJoueur)
{
	system("clear");	//effacer le contenu du terminal
	GR6_affchage_etat_actuel_partie(map);	//affiche le contenu de la map
	return GR6_affichage_choix_couleurs(GR6_numeroJoueur);	//affiche les choix de couleurs disponibles et renvoie le choix du joueur
}

void GR6_500_partie_glouton_vs_aleatoire(Map* map)
{
	//initialisation des scores
	int GR6_score_glouton = 0;
	int GR6_score_aleatoire = 0;
	for(int i=0; i < 500; i++)
	{
		GR6_initialiser_jeu(map, 20);     //initialiser le jeu pour une map de taille 20x20
		int GR6_choix_mode_jeu = -1;
		int GR6_typeJoueurAleatoire = 2;
		int GR6_typeJoueurGlouton = 3;

		GR6_choix_mode_jeu = GR6_typeJoueurAleatoire;		//L'ia aléatoire (joueur 1🤑) commmence la partie

		while(GR6_determiner_si_jeu_fini(map) == -1)		//tant que le jeu doit continuer
		{
		switch (GR6_choix_mode_jeu)
			{
			case 2:
				GR6_numCouleurChoisie = GR6_ia_aleatoire(map,GR6_numeroJoueur);		//l'ia aléatoire joue un coup
				break;

			case 3:
				GR6_numCouleurChoisie = GR6_ia_glouton(map,GR6_numeroJoueur);		//l'ia glouton joue un coup
				break;
			}
		//mise à jour de la map
		while(GR6_maj_monde(map, GR6_numCouleurChoisie,GR6_numeroJoueur)== 1)
		{
			//on repasse dans la boucle while pour refaire la maj, et on en sort
			//printf("Maj de la map en cours...");
		}
		
		//Changement de joueur
		switch (GR6_numeroJoueur)
		{
		case 1:
			GR6_numeroJoueur = 2;
			GR6_choix_mode_jeu = GR6_typeJoueurGlouton;
			break;
		
		case 2:
			GR6_numeroJoueur = 1;
			GR6_choix_mode_jeu = GR6_typeJoueurAleatoire;
			break;
		
		default:
			break;
		}
	}
		switch (GR6_determiner_si_jeu_fini(map))	//ajouter un point au vainqueur
		{
			case 1:
			GR6_score_aleatoire++;
			break;

			case 2:
			GR6_score_glouton++;
			break;
		}	
	}

	//affichage des résultats pour chaque ia
	printf("Le score de l'ia glouton est : %i\n",GR6_score_glouton);
	printf("Le score de l'ia aléatoire est : %i\n",GR6_score_aleatoire);
}

void GR6_lancer_jeu(Map* map)     //lancer le jeu et gérer la partie en fonction du mode de jeu choisi
{
	system("clear");	//effacer le contenu du terminal
	printf("Jeu les 7 merveilles du monde des 7 couleurs \n\n");
	//Affichage de l'état actuel de la partie
	GR6_affchage_etat_actuel_partie(map);
	//Choix du mode de jeu
	int GR6_choix_mode_jeu = -1;
	int GR6_typeJoueur1 = -1;
	int GR6_typeJoueur2 = -1;

	GR6_typeJoueur1 = GR6_affichage_type_joueur1();		//affiche les possibilités de jeu pour le joueur 1 et renvoie son choix
	printf("%i",GR6_typeJoueur1);
	if(GR6_typeJoueur1 == 5)	//si l'on veut faire 500 parties entre ia glouton et ia aléatoire
	{
		GR6_500_partie_glouton_vs_aleatoire(map);
	}
	else
	{
	GR6_typeJoueur2 = GR6_affichage_type_joueur2();		//affiche les possibilités de jeu pour le joueur 2

	//Le joueur 1 commmence :
	GR6_choix_mode_jeu = GR6_typeJoueur1;
	}
	printf("Début de la partie \n");

	
	while(GR6_determiner_si_jeu_fini(map) == -1)		//tant que le jeu doit continuer
	{
		switch (GR6_choix_mode_jeu)
		{
		case 1:
			GR6_numCouleurChoisie = GR6_humain(map, GR6_numeroJoueur);		//l'utilisateur humain joue un coup
			break;

		case 2:
			GR6_numCouleurChoisie = GR6_ia_aleatoire(map,GR6_numeroJoueur);		//l'ia aléatoire joue un coup
			break;

		case 3:
			GR6_numCouleurChoisie = GR6_ia_glouton(map,GR6_numeroJoueur);		//l'ia glouton joue un coup
			break;
		
		case 4:
			GR6_numCouleurChoisie = GR6_ia_smart(map,GR6_numeroJoueur);		//l'ia smart joue un coup
			break;
		}
		//mise à jour de la map
		while(GR6_maj_monde(map, GR6_numCouleurChoisie,GR6_numeroJoueur)== 1)
		{
			//on repasse dans la boucle while pour refaire la maj, et on en sort
			//printf("Maj de la map en cours...");
		}
		
		system("clear");	//effacer le contenu du terminal

		//Affichage de l'état actuel de la partie
		GR6_affchage_etat_actuel_partie(map);

		//Changement de joueur
		switch (GR6_numeroJoueur)
		{
		case 1:
			GR6_numeroJoueur = 2;
			GR6_choix_mode_jeu = GR6_typeJoueur2;
			break;
		
		case 2:
			GR6_numeroJoueur = 1;
			GR6_choix_mode_jeu = GR6_typeJoueur1;
			break;
		
		default:
			break;
		}
	}
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
				if(GR6_get_map_value(map, x+1, y) == GR6_numeroJoueur || 
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

Color GR6_get_map_value(Map* map, int x, int y)     //pour récupérer la valeur d'une case du jeu, et -1 si on sort de la map (fait appel à get_map_value de map.c)
{
	if (map -> map == NULL || x >= map -> size || y >= map -> size || y < 0 || x < 0)
	{
		//printf("[ERROR] map not big enough or not initialized %p %i access (%i %i)", map -> map, map -> size, x, y);
		return ERROR;
	}
	//sinon
	return get_map_value(map, x, y);
}

//lance 500 parties entre l'ia glouton et l'ia aléatoire