#ifndef SHOGI_GAME_H
#define SHOGI_GAME_H

/* Helpers */

#include "file.h"
#include "pile.h"

#define MAX_CHAR 256

/* Definitions des structures */

/** Structure connu sous le nom de partie
 * Echiquier
 * Contient un tableau 11*11 de type piece
 * Une file determinant l'historique des coups jouées
 * Une pile pour la liste des pieces capturées
 * Un booléen pour le tour de joueur
 */
typedef struct        game_s {
  piece_t             board[11][11];
  file_list_t   *     file;
  pile_list_t   *     capture;
  unsigned int        player;
}                     game_t;

/*  Usual functions */

void            afficher_echiquier      (game_t *g, coordinate_t g_i);

game_t       *  partie_creer            (void);
void            partie_detruire         (game_t *g);
game_t       *  partie_nouvelle         (void);

int             case_vide               (piece_t p);
void            modifier_case           (game_t *g, piece_t p, coordinate_t c);
void            changer_joueur          (game_t *g);

int             game_selector           (char *game_command, const char *select_v);
int             game_exit               (game_t *g);
coordinate_t    saisie_case             (void);
void            game_seperator          (void);
void            partie_jouer            (game_t *g);

#endif //SHOGI_GAME_H
