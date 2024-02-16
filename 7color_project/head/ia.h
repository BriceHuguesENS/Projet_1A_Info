#ifndef IA_H
#define IA_H
#include "map.h"

int GR6_ia_aleatoire(Map* map, int GR6_numeroJoueur);       //ia qui joue un coup aléatoire "Question 6"

int GR6_ia_glouton(Map* map, int GR6_numeroJoueur);       //ia qui joue un coup aléatoire pour + de territoire "Question 7"

int GR6_ia_smart(Map* map, int GR6_numeroJoueur);        //ia qui joue le coup qui lui fait gagner le plus de territoire
#endif