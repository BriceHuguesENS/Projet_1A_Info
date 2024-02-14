#ifndef GAME_H
#define GAME_H
#include "map.h"

int GR6_maj_monde(Map* map,int GR6_choixJoueur, int GR6_numeroJoueur);	//fonction pour mettre à jour la map après le coup d'un joueur

int GR6_determiner_si_jeu_fini(Map* map);		//fonction pour savoir si le jeu est fini

void GR6_initialiser_jeu(Map* map,int taille_carte);     //fonction pour initialiser la carte et d'autres paramètres au début du jeu

void GR6_lancer_jeu(Map* map);     //fonction pour lancer le jeu et gérer la partie

void GR6_cloturer_jeu(Map* map);     //fonction pour cloturer le jeu

Color GR6_get_map_value(Map* map, int x, int y);     //pour récupérer la valeur d'une cse du jeu, et -1 si on sort de la map (fait appel à get_map_value de map.c)
#endif