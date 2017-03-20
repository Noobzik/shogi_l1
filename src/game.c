#include "header/game.h"
//#include "header/piece.h"
#include <stdio.h>
#include <stdlib.h>
// Rakib
void afficher_echiquier(game_t *game_v) {

  int x, y;

  printf("\n");
  printf("                      0  1  2  3  4  5  6  7  8\n");

  for (x = 0; x < 9; x++) {
    if (x < 6 && x > 1) {
      printf("                   %d  ", x);
    } else if (x < 7) {
      /* Player Indicator */
      if (game_v->player == 0) {
        printf("  NOIR->           %d  ", x);
      } else {
        printf("                   %d  ", x);
      }

    } else if (x > 1) {
      /* Player Indicator */
      if (game_v->player == 1) {
        printf("  BLANC->          %d  ", x);
      } else {
        printf("                   %d  ", x);
      }
    }

    /* Selection detector */
    /*
        if (game_input_tmp.x != 42 || game_input_tmp.y != 42) {
          //      movement_restriction(game_v, game_input_tmp);
        }
    */
    /* Chess board */
    for (y = 0; y < 8; y++) {
      piece_afficher(game_v->board[x][y]);
      printf("  ");
    }

    printf("\n");
  }
}

game_t *partie_creer() {
  game_t *res;
  return res = (game_t *)malloc(sizeof(game_t));
}

void partie_detruire(game_t *game_v) { free(game_v); }
