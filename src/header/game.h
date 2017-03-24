#ifndef GAME_H
#define GAME_H
#include "file.h"
#include "piece.h"
// Rakib
/* Definitions des structures */

/** Structure connu sous le nom de partie
 * Echiquier
 * Contient un tableau 11*11
 * Une file determinant l'historique des coups jouées
 * Une pile pour la liste des pieces capturées
 * Un booléen pour le tour de joueur
 */
typedef struct game_s {
  piece_t board[11][11];
  file_list_t *file;
  int player;
} game_t;

/* Prototype des fonctions */
void afficher_echiquier(game_t *game_v);
game_t *partie_creer();
void partie_detruire(game_t *game_v);
game_t *partie_nouvelle();

int case_vide(piece_t piece_v);
void modifier_case(game_t *game_v, piece_t piece_v, coordinate_t coordinate_v);
void changer_joueur(game_t *game_v);
coordinate_t saisie_case();
#endif
