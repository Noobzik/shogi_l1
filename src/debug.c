#include "header/debug.h"
#include "header/file.h"

#include <stdio.h>

/** Info
 *  BLANC = 0
 *  NOIR  = 1
 */

void debug_pile(game_t *game_v) {
  //======================================================================
  // Variables
  //======================================================================
  int i;
  pile_list_t *pile_list_tmp;
  pile_element_t *pile_element_tmp;

  /* Initialize */
  pile_list_tmp = game_v->capture;

  //======================================================================
  // Main
  //======================================================================
  printf("DEBUG | Pile\n");
  printf("Taille: %d\n", pile_list_tmp->taille);

  if (!pile_vide(pile_list_tmp)) {

    for (pile_element_tmp = pile_list_tmp->suivant, i = 0;
         pile_element_tmp != NULL;
         i++, pile_element_tmp = pile_element_tmp->suivant) {

      printf("Maillon %d | '", i);
      piece_afficher(pile_element_tmp->piece);
      printf("' (Type: %d; Joueur: %d) Piece : \n",
             pile_element_tmp->piece.type, pile_element_tmp->piece.color);
    }

  } else {
    printf("La pile ne contient rien.\n");
  }
}

void debug_file(game_t *game_v) {

  /* Variables */
  file_list_t *file_list_tmp;
  file_element_t *file_element_tmp;
  int i;
  /* Initialize */
  file_list_tmp = game_v->file;

  /* Main */
  printf("DEBUG | File\n");
  printf("Taille: %d\n", file_list_tmp->taille);

  if (!file_list_vide(file_list_tmp)) {
    for (file_element_tmp = file_list_tmp->debut, i = 0;
         file_element_tmp != NULL;
         i++, file_element_tmp = file_element_tmp->suivant) {
      printf("Maillon %d | ", i);
      printf("(%d;%d) ", file_element_tmp->movement.input.x,
             file_element_tmp->movement.input.y);
      printf("(%d;%d)\n", file_element_tmp->movement.output.x,
             file_element_tmp->movement.output.y);
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
 *     game_t - game_v
 */
void debug_cell(game_t *game_v, coordinate_t coordinate_v) {
  //======================================================================
  // Main
  //======================================================================
  printf("DEBUG | Cellule\n");

  if (coordinate_v.x < 11 && coordinate_v.y < 11) {
    printf("Piece: ");
    piece_afficher(game_v->board[coordinate_v.x][coordinate_v.y]);
    printf(" (%d; %d)", coordinate_v.x, coordinate_v.y);
    printf("\nJoueur: %d", game_v->board[coordinate_v.x][coordinate_v.y].color);
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
