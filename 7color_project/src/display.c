#include "../head/display.h"
#include <stdio.h>

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
                printf("🤖");
                break;
            
            case 2:
                // Réinitialiser la couleur
                printf("\033[0m");
                printf("🤑");
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
