#include "../head/ia.h"
#include "../head/game.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int GR6_ia_aleatoire(Map* map, int GR6_numeroJoueur)
{
    return rand()%7+3;   //nombre aléatoire entre 3 et 9 (donc plage de taille 7)
}

int GR6_ia_glouton(Map* map, int GR6_numeroJoueur)       //ia glouton qui joue un coup pour + de territoire "Question 7"
{
    //initilisation du tableau des couleurs possibles
    int* GR6_couleursPossibles = malloc(sizeof(int)*7);
    memset(GR6_couleursPossibles, 0, 7*sizeof(int));    //initialiser le tableau précédent avec que des 0

    for(int y=0; y<map->size;y++)
	{
		for(int x=0; x<map->size;x++)
		{
            if(GR6_get_map_value(map, x, y) >= 3)		//si la case actuelle est une couleur
			{

				//vérification si elle est bien adjacente au territoire du joueur
				if(GR6_get_map_value(map, x+1, y)== GR6_numeroJoueur || 
				   GR6_get_map_value(map, x, y+1) == GR6_numeroJoueur ||
				   GR6_get_map_value(map, x-1, y) == GR6_numeroJoueur ||
				   GR6_get_map_value(map, x, y-1) == GR6_numeroJoueur)
				{
                    //ajout à la liste des couleurs possibles à jouer pour le joueur
                    GR6_couleursPossibles[GR6_get_map_value(map, x, y)-3] = GR6_get_map_value(map, x, y);    //ajoute la valeur de la couleur dans la liste
				}
			}
        }
    }
    //on retire les 0 du tableau, ie les couleurs non adjacentes à la map
    int GR6_nbCouleurs = 0;
    int* GR6_couleursPossiblesDefinitives = malloc(sizeof(int)*GR6_nbCouleurs);
    for(int i = 0; i < 7; i++)
    {
        if(GR6_couleursPossibles[i] != 0)       //si la case n'est pas vide
        {
            GR6_couleursPossiblesDefinitives[GR6_nbCouleurs] = GR6_couleursPossibles[i];    //elle est ajoutée aux couleurs à jouer potentiellement
            GR6_nbCouleurs++;
        }
    }

    int GR6_couleurChoisie = GR6_couleursPossiblesDefinitives[rand()%GR6_nbCouleurs]; //retourne un numéro de couleur en prenant un indice aléatoire dans la liste des couleurs possibles
    //libération de l'espace mémoire
    free(GR6_couleursPossibles);
    free(GR6_couleursPossiblesDefinitives);

    return GR6_couleurChoisie;
}


int GR6_ia_smart(Map* map, int GR6_numeroJoueur)     //ia qui joue le coup qui lui fait gagner le plus de territoire
{
    //nouvelle map sur laquelle on va faire des tests
    Map GR6_map_virtuelle = {.map = NULL, .size = 0};
    GR6_map_virtuelle.map = malloc(sizeof(Color) * (map->size * map->size));
    GR6_map_virtuelle.size = map->size;
    memcpy(GR6_map_virtuelle.map, map->map,GR6_map_virtuelle.size*GR6_map_virtuelle.size*sizeof(Color));
	

    //initilisation du tableau des couleurs possibles
    int GR6_nbCouleurs = 0;
    int* GR6_couleursPossibles = malloc(sizeof(int)*7);
    memset(GR6_couleursPossibles, 0, 7*sizeof(int));    //initialiser le tableau précédent avec que des 0

    //parcourir la map pour savoir les cases adjacentes au territoire du joueur
    for(int y=0; y<map->size;y++)
	{
		for(int x=0; x<map->size;x++)
		{
            if(GR6_get_map_value(map, x, y) >= 3)		//si la case actuelle est une couleur
			{

				//vérification si elle est bien adjacente au territoire
				if(GR6_get_map_value(&GR6_map_virtuelle, x+1, y) == GR6_numeroJoueur || 
				   GR6_get_map_value(&GR6_map_virtuelle, x, y+1) == GR6_numeroJoueur ||
				   GR6_get_map_value(&GR6_map_virtuelle, x-1, y) == GR6_numeroJoueur ||
				   GR6_get_map_value(&GR6_map_virtuelle, x, y-1) == GR6_numeroJoueur)
				{
                    //ajout à la liste des couleurs possibles
                    GR6_couleursPossibles[GR6_get_map_value(&GR6_map_virtuelle, x, y)-3] = GR6_get_map_value(&GR6_map_virtuelle, x, y);    //ajoute la valeur de la couleur dans la liste des couleurs possibles
                    GR6_nbCouleurs++;
				}
			}
        }
    }
    //on retire les 0 du tableau
    int* GR6_couleursPossiblesDefinitives = malloc(sizeof(int)*GR6_nbCouleurs);
    int i2 = 0; //indice pour parcourir la liste "GR6_couleursPossiblesDefinitives"
    for(int i = 0; i < 7; i++)
    {
        if(GR6_couleursPossibles[i] != 0)       //si la case n'est pas vide
        {
            GR6_couleursPossiblesDefinitives[i2] = GR6_couleursPossibles[i];        //elle est ajoutée aux couleurs à jouer potentiellement
            i2++;
        }
    }

    //simulation d'un coup sur une map virtuelle
    int GR6_maxCase = 0;		//pour compter le nombre maximal de cases en jouant le meilleur coup
	int GR6_numeroMaxCase = 0;  //pour stocker le numero de la couleur qui permet de faire le meilleur coup
    int GR6_compteurCase = 0;

    for(int i = 0; i < GR6_nbCouleurs; i++)
    {
        GR6_compteurCase = 0;
        //mise à jour de la map
		while(GR6_maj_monde(&GR6_map_virtuelle, GR6_couleursPossiblesDefinitives[i],GR6_numeroJoueur)== 1)
		{
            GR6_compteurCase++;
			//on repasse dans la boucle while pour refaire la maj, et on en sort
			//printf("Maj de la map en cours...");
		}
        //on sauvegarde le meilleur coup
        if(GR6_compteurCase > GR6_maxCase)
        {
            GR6_numeroMaxCase = GR6_couleursPossiblesDefinitives[i];
            GR6_maxCase = GR6_compteurCase;
        }
        //remettre la map dans la configuration précédente pour essayer avec une nouvelle couleur
        memcpy(GR6_map_virtuelle.map, map->map,GR6_map_virtuelle.size*GR6_map_virtuelle.size*sizeof(Color));
    }

    int GR6_couleurChoisie = GR6_numeroMaxCase; //retourne le numero de la couleur qui permet de faire le meilleur coup
    
    //Libération de l'espace mémoire
    free(GR6_couleursPossibles);
    free(GR6_couleursPossiblesDefinitives);
    
    free(GR6_map_virtuelle.map);
	GR6_map_virtuelle.map = NULL;

    return GR6_couleurChoisie;
}