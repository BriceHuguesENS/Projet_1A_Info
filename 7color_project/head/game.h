#ifndef GAME_H
#define GAME_H
#include "map.h"

int GR6_maj_monde(Map* map,int GR6_choixJoueur, int GR6_numeroJoueur);	//fonction pour mettre à jour la map après le coup d'un joueur

int GR6_determiner_si_jeu_fini(Map* map);		//fonction pour savoir si le jeu est fini

void GR6_initialiser_jeu();     //fonction pour initialiser la carte et d'autres paramètres au début du jeu

#endif