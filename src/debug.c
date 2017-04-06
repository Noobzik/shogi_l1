#include "header/debug.h"
#include "header/file.h"

#include <stdio.h>
void debug_pile(game_t *game_v) {
  int i;
  /* Variables */
  pile_list_t *pile_list_tmp;
  pile_element_t *pile_element_tmp;

  /* Initialize */
  pile_list_tmp = game_v->capture;

  /* Main */
  printf("DEBUG | Pile\n");
  printf("Taille: %d\n", pile_list_tmp->taille);

  if (!pile_vide(pile_list_tmp)) {
    for (pile_element_tmp = pile_list_tmp->last, i = 0;
         pile_element_tmp != NULL;
         i++, pile_element_tmp = pile_element_tmp->suivant) {
      printf("Maillon %d | '", i);
      piece_afficher(pile_element_tmp->piece);
      printf("' (Type : %d; Element : %d)\n", pile_element_tmp->piece.type,
             pile_element_tmp->piece.color);
    }
  } else {
    printf("La pile ne contient rien.");
  }

  printf("\n");
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
  printf("Longueur: %d\n", file_list_tmp->taille);

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
  res->player = 0;

  /* Remplissage case vide */
  for (x = 0; x < 11; x++) {

    for (y = 0; y < 11; y++) {
      res->board[y][x] = piece_creer(VIDE_PIECE, VIDE, NON_PROMU);
      res->board[y][x] = piece_creer(VIDE_PIECE, VIDE, NON_PROMU);
    }
  }

  /* Pions */
  res->board[5][5] = piece_creer(NOIR, CAVALIER, NON_PROMU);

  return res;
}
