#include "../head/display.h"
#include "../head/game.h"
#include <stdio.h>
#include <stdlib.h>

// Implémentation de la fonction d'affichage
void GR6_affchage_etat_actuel_partie(Map* map)
{
    printf("\033[47m  ");
    for(int y=0; y<(map->size);y++)
	{
        printf("  ");
    }
    printf("  \n");
    for(int y=0; y<(map->size);y++)
	{
        printf("\033[47m  ");
		for(int x=0; x<(map->size);x++)
		{
            switch (get_map_value (map, x, y))
            {
            case 1:
                // Réinitialiser la couleur
                printf("\033[0m");
                printf("🤑");
                break;

            case 2:
                // Réinitialiser la couleur
                printf("\033[0m");
                printf("🤖");
                break;

            case 3:
                printf("\033[0m");
                printf("🟥");
                break;

            case 4:
                printf("\033[0m");
                printf("🟩");
                break;
            
            case 5:
                printf("\033[0m");
                printf("🟦");
                break;

            case 6:
                printf("\033[0m");
                printf("🟨");
                break;

            case 7:
                printf("\033[0m");
                printf("🟪");
                break;
            
            case 8:
                printf("\033[0m");
                printf("🟫");
                break;

            case 9:
                printf("\033[0m");
                printf("⬜");
                break;
            
            default:
                break;
            }
        }
        printf("\033[47m  \033[0m\n");
	}
    printf("\033[47m  ");
    for(int y=0; y<(map->size);y++)
	{
        printf("  ");
    }
    printf("  \033[0m\n");
    // Réinitialiser la couleur
    printf("\033[0m\n");
}

int GR6_affichage_choix_couleurs(int GR6_numeroJoueur)
{
    int GR6_numCouleur=0;
    printf("\033[38;2;255;0;0m3:🟥\n\033[38;2;0;255;0m4:🟩\n\033[34m5:🟦\n\033[33m6:🟨\n\033[35m7:🟪\n\033[38;2;139;69;19m8:🟫\n\033[38;2;255;255;255m9:⬜️\n\033[0m");
	//sélection de la couleur par le joueur ou l'ia
	printf("\n\033[0mJoueur %i, entrez votre couleur: ",GR6_numeroJoueur);
	scanf("%i", &GR6_numCouleur);	//récupérer le choix du joueur
    return GR6_numCouleur;
}

int GR6_affichage_type_joueur1()    //sélectionner le type de joueur 1
{
    int GR6_typeJoueur1;
    printf("Veuillez sélectionner un type de joueur 1 🤑: \n\n1:humain \n2:ia aléatoire\n3:ia glouton\n4:ia smart\n5:500 parties entre ia glouton et ia aléatoire\n");
	scanf("%i",&GR6_typeJoueur1);
    return GR6_typeJoueur1;
}

int GR6_affichage_type_joueur2()    //sélectionner le type de joueur 2
{
    int GR6_typeJoueur2;
    printf("Veuillez sélectionner un type de joueur 2 🤖: \n\n1:humain \n2:ia aléatoire\n3:ia glouton\n4:ia smart\n5:500 parties entre ia glouton et ia aléatoire\n");
	scanf("%i",&GR6_typeJoueur2);
    return GR6_typeJoueur2;
}

void GR6_cloturer_jeu(Map* map)     //fonction pour cloturer le jeu, afficher les résultats et libérer l'espace mémoire
{
	//sélection de l'issue finale
	switch (GR6_determiner_si_jeu_fini(map))
	{
	case 1:
		printf("Fin de la partie !\nLe vainqueur est le joueur 1 🤑 \n");	
		break;

	case 2:
		printf("Fin de la partie !\nLe vainqueur est le joueur 2 🤖 \n");	
		break;
	
	case 0:
		printf("Fin de la partie !\nIl y a égalité \n");	
		break;
	}
	
	//libération de l'espace mémoire
	free(map->map);
	map->map = NULL;
}
