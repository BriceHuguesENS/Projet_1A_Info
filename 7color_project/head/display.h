#ifndef DISPLAY_H
#define DISPLAY_H
#include "map.h"
void GR6_affchage_etat_actuel_partie(Map* map);
int GR6_affichage_choix_couleurs(int GR6_numeroJoueur);
int GR6_affichage_type_joueur1();
int GR6_affichage_type_joueur2();
void GR6_cloturer_jeu(Map* map);
#endif