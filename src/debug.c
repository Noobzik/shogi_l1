#include "header/debug.h"
#include "header/file.h"

#include <stdio.h>

void                debug_pile(game_t * g) {
  int               i;
  pile_list_t *     l;
  pile_element_t *  e;

  l = g->capture;
  printf("DEBUG | Pile\n");
  printf("size: %d\n", l->size);

  if (pile_empty(l)) {
    printf("La pile ne contient rien.\n");
    return;
  }

  for (e = l->next, i = 0; e != NULL; i++, e = e->next) {
    printf("Maillon %d | '", i);
    piece_afficher(e->piece);
    printf("' (Type: %d; Joueur: %d) Piece : \n", e->piece.type, e->piece.color);
  }
}

void debug_file     (game_t * g) {
  int               i;
  file_list_t *     l;
  file_element_t *  e;

  l = g->file;
  printf("DEBUG | File\n");
  printf("size: %d\n", l->size);

  if (file_empty_list(l)) {
    printf("La file ne contient rien.");
    return;
  }

  for (e = l->begin, i = 0; e != NULL; i++, e = e->next) {
    printf("Maillon %d | ", i);
    printf("(%d;%d) ", e->movement.input.x, e->movement.input.y);
    printf("(%d;%d)\n", e->movement.output.x, e->movement.output.y);
  }
  printf("\n");
}

/**
 * debug game
 *
 * Parameters:
 *     game_t - game_v
 */
void debug_cell(game_t * g, coordinate_t c) {
  printf("DEBUG | Cellule\n");

  if (c.x > 11 || c.y > 11) {
    printf("Cette cellule est invalide.\n");
    return;
  }

  printf("Piece: ");
  piece_afficher(g->board[c.x][c.y]);
  printf(" (%d; %d)", c.x, c.y);
  printf("\nJoueur: %d", g->board[c.x][c.y].color);
}

game_t *    debug_new_game() {
  int x,    y;
  game_t *  res;

  res = partie_creer();
  res->capture = pile_create();
  res->file = file_create_list();
  res->player = 0;

  for (x = 0; x < 11; x++)
    for (y = 0; y < 11; y++) {
      res->board[y][x] = piece_create(EMPTY_PIECE, EMPTY, NOT_PROMOTED);
      res->board[y][x] = piece_create(EMPTY_PIECE, EMPTY, NOT_PROMOTED);
    }

  for (y = 1; y < 8; y++) res->board[5][y] = piece_create(NOIR, PION, NOT_PROMOTED);

  res->board[5][y] = piece_create(BLANC, TOUR, NOT_PROMOTED);
  return res;
}
