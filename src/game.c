#include "header/game.h"
#include "header/piece.h"
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
    } else if (x < 6) {
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
    for (y = 0; y < 9; y++) {
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

game_t *partie_nouvelle() {
  //======================================================================
  // Variables
  //======================================================================
  int x, y;
  game_t *res;

  /* Initialize */
  res = partie_creer();
  //    res -> catched = pile_create();
  //    res -> played  = file_create();
  res->player = 0;

  //======================================================================
  // Main
  //======================================================================
  /* Empty */
  for (x = 0; x < 9; x++) {

    for (y = 0; y < 9; y++) {
      res->board[y][x] = piece_creer(VIDE_PIECE, VIDE);
      res->board[y][x] = piece_creer(VIDE_PIECE, VIDE);
    }
  }

  /* Pions */
  for (x = 0; x < 9; x++) {
    res->board[6][x] = piece_creer(NOIR, PION);
    res->board[2][x] = piece_creer(BLANC, PION);
  }

  /* Tour */

  res->board[7][1] = piece_creer(NOIR, TOUR);
  res->board[1][7] = piece_creer(BLANC, TOUR);

  /* Roi */

  res->board[8][4] = piece_creer(NOIR, ROI);
  res->board[0][4] = piece_creer(BLANC, ROI);

  /* Fou */

  res->board[7][7] = piece_creer(NOIR, FOU);
  res->board[1][1] = piece_creer(BLANC, FOU);

  /* Gold */

  res->board[0][3] = piece_creer(BLANC, GOLD);
  res->board[0][5] = piece_creer(BLANC, GOLD);
  res->board[8][3] = piece_creer(NOIR, GOLD);
  res->board[8][5] = piece_creer(NOIR, GOLD);

  /* Sivler */

  res->board[8][2] = piece_creer(NOIR, SILVER);
  res->board[8][6] = piece_creer(NOIR, SILVER);
  res->board[0][2] = piece_creer(BLANC, SILVER);
  res->board[0][6] = piece_creer(BLANC, SILVER);

  /* Cavalier */

  res->board[0][1] = piece_creer(BLANC, CAVALIER);
  res->board[0][7] = piece_creer(BLANC, CAVALIER);
  res->board[8][1] = piece_creer(NOIR, CAVALIER);
  res->board[8][7] = piece_creer(NOIR, CAVALIER);

  /* Lancier */

  res->board[0][0] = piece_creer(BLANC, LANCIER);
  res->board[0][8] = piece_creer(BLANC, LANCIER);
  res->board[8][0] = piece_creer(NOIR, LANCIER);
  res->board[8][8] = piece_creer(NOIR, LANCIER);

  return res;
}
