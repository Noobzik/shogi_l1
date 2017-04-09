#include "header/debug.h"
#include "header/file.h"

#include <stdio.h>

/** Info
 *  BLANC = 0
 *  NOIR  = 1
 */

void debug_pile(game_t *g) {
  //======================================================================
  // Variables
  //======================================================================
  int i;
  pile_list_t *l;
  pile_element_t *e;

  /* Initialize */
  l = g->capture;

  //======================================================================
  // Main
  //======================================================================
  printf("DEBUG | Pile\n");
  printf("Taille: %d\n", l->taille);

  if (!pile_vide(l)) {

    for (e = l->suivant, i = 0; e != NULL; i++, e = e->suivant) {

      printf("Maillon %d | '", i);
      piece_afficher(e->piece);
      printf("' (Type: %d; Joueur: %d) Piece : \n", e->piece.type,
             e->piece.color);
    }

  } else {
    printf("La pile ne contient rien.\n");
  }
}

void debug_file(game_t *g) {

  /* Variables */
  file_list_t *l;
  file_element_t *e;
  int i;
  /* Initialize */
  l = g->file;

  /* Main */
  printf("DEBUG | File\n");
  printf("Taille: %d\n", l->taille);

  if (!file_list_vide(l)) {
    for (e = l->debut, i = 0; e != NULL; i++, e = e->suivant) {
      printf("Maillon %d | ", i);
      printf("(%d;%d) ", e->movement.input.x, e->movement.input.y);
      printf("(%d;%d)\n", e->movement.output.x, e->movement.output.y);
    }
  } else {
    printf("La file ne contient rien.");
  }
  printf("\n");
}

/**
 * debug game
 *
 * Parameters:
 *     game_t - g
 */
void debug_cell(game_t *g, coordinate_t c) {
  //======================================================================
  // Main
  //======================================================================
  printf("DEBUG | Cellule\n");

  if (c.x < 11 && c.y < 11) {
    printf("Piece: ");
    piece_afficher(g->board[c.x][c.y]);
    printf(" (%d; %d)", c.x, c.y);
    printf("\nJoueur: %d", g->board[c.x][c.y].color);
  } else {
    printf("Cette cellule est invalide.\n");
  }
}

game_t *debug_partie_nouvelle() {
  //======================================================================
  // Variables
  //======================================================================
  int x, y;
  game_t *res;

  /* Initialize */
  res = partie_creer();
  res->capture = pile_create();
  res->file = file_creer_list();

  /** Info
   *  BLANC = 1
   *  NOIR  = 0
   */

  res->player = 0;

  /* Remplissage case vide */
  for (x = 0; x < 11; x++) {

    for (y = 0; y < 11; y++) {
      res->board[y][x] = piece_creer(VIDE_PIECE, VIDE, NON_PROMU);
      res->board[y][x] = piece_creer(VIDE_PIECE, VIDE, NON_PROMU);
    }
  }

  /* Pions */
  for (y = 1; y < 8; y++) {
    res->board[5][y] = piece_creer(NOIR, PION, NON_PROMU);
  }
  res->board[5][y] = piece_creer(BLANC, TOUR, NON_PROMU);
  return res;
}
