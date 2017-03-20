#ifndef GAME_H
#define GAME_H
#include "piece.h"

// Rakib
/* Definitions des structures */

/**
 * Echiquier
 * Contient un tableau 9*9
 * Une file determinant l'historique des coups jouées
 * Une pile pour la liste des pieces capturées
 * Un booléen pour le tour de joueur
 */

typedef struct game_s {
  piece_t board[9][9];
  //  file_list_t *played;
  //  pile_list_t *catched;
  int player;
} game_t;

/* Prototype des fonctions */
void afficher_echiquier(game_t *game_v);
game_t *partie_creer();
void partie_detruire(game_t *game_v);
#endif
