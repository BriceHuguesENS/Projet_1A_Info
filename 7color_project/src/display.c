#include "../head/display.h"
#include <stdio.h>

// Implémentation de la fonction d'affichage
void GR6_affchage_etat_actuel_partie(Map* map)
{
    for(int y=0; y<(map->size);y++)
	{
		for(int x=0; x<(map->size);x++)
		{
            
            //printf(" %i ",map->map[(map->size)*y +x]);
            //printf("get_map_value (map, x, y) : %i \n",get_map_value (map, x, y));
            //printf("map -> map[y * map -> size + x] %i \n",map -> map[y * map -> size + x]);

            switch (get_map_value (map, x, y))
            {
            case 1:
                // Réinitialiser la couleur
                printf("\033[0m");
                printf(" v ");
                break;
            
            case 2:
                // Réinitialiser la couleur
                printf("\033[0m");
                printf(" ^ ");
                break;

            case 3:
                printf(" \033[31mR ");
                break;

            case 4:
                printf(" \033[32mG ");
                break;
            
            case 5:
                printf(" \033[34mB ");
                break;

            case 6:
                printf(" \033[33mY ");
                break;

            case 7:
                printf(" \033[35mM ");
                break;
            
            case 8:
                printf(" \033[36mC ");
                break;

            case 9:
                printf(" \033[37mW ");
                break;
            
            default:
                break;
            }
        }
        printf("\n");
	}
    // Réinitialiser la couleur
    printf("\033[0m");
}
