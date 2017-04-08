#ifndef GAME_H
#define GAME_H
#include "file.h"
#include "piece.h"
#include "pile.h"

#define MAX_CHAR 256

// Rakib
/* Definitions des structures */

/** Structure connu sous le nom de partie
 * Echiquier
 * Contient un tableau 9*9
 * Une file determinant l'historique des coups jouées
 * Une pile pour la liste des pieces capturées
 * Un booléen pour le tour de joueur
 */
typedef struct game_s {
  piece_t board[11][11];
  file_list_t *file;
  pile_list_t *capture;
  unsigned int player;
} game_t;

/* Prototype des fonctions */
void afficher_echiquier(game_t *game_v, coordinate_t);
game_t *partie_creer(void);
void partie_detruire(game_t *game_v);
game_t *partie_nouvelle(void);

void annuler_deplacement(game_t *game_v);
int case_vide(piece_t piece_v);
void modifier_case(game_t *game_v, piece_t piece_v, coordinate_t coordinate_v);
void changer_joueur(game_t *game_v);
void deplacement_apply(game_t *game_v, coordinate_t coordinate_input_v,
                       coordinate_t coordinate_output_v);

int game_selector(char *game_command, const char *select_v);
int game_exit(game_t *game_v);
coordinate_t saisie_case(void);
void game_seperator(void);
void partie_jouer(game_t *game_v);

#endif
