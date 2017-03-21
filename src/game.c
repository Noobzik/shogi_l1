#include "header/game.h"
#include "header/piece.h"
#include <stdio.h>
#include <stdlib.h>
// Rakib

/** Afficher_echiquier
 * Description :
 * La premiere boucle for permet l'espacement et d'afficher le tour actuelle du joueur
 * La deuxieme boucle for affiche le contenue de chaque case de l'échiquier
 * Parameters :
 * @param : game_t - game_v
 * @return : VOID
*/
void afficher_echiquier(game_t *game_v) {

 /* Variables de boucles pour les coordonnes*/
  int x, y;

  printf("\n");
  printf("                       0  1  2  3  4  5  6  7  8  9  10\n");
  printf("                      _________________________________\n");


  for (x = 0; x < 11; x++) {
    if (x < 6 && x > 2) {
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
      } else if(x == 10){
          printf("                  %d  ", x);
      } else
          printf("                   %d  ", x);
    }

    /* Selection detector */
    /*
        if (game_input_tmp.x != 42 || game_input_tmp.y != 42) {
          //      movement_restriction(game_v, game_input_tmp);
        }
    */
    /* Chess board */
    for (y = 0; y < 11; y++) {
      piece_afficher(game_v->board[x][y]);
      printf("  ");
    }

    printf("\n");
  }
}

/** partie_creer
 * Description :
 * Permet de retourner un echiquier initialisé
 */
game_t *partie_creer() {
  game_t *res;
  return res = (game_t *)malloc(sizeof(game_t));
}

/** partie_detruire
 * Détruit tout simplement l'echiquier
 */
void partie_detruire(game_t *game_v) { free(game_v); }

/** partie_nouvelle
 * Description: Initialize tout les case en piece VIDE
 * Puis Place tout les pieces de debut de partie
 * Parameters :
 * @return Retourne un echiquier pret à etre jouer
 */
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

  /* Remplissage case vide */
  for (x = 0; x < 11; x++) {

    for (y = 0; y < 11; y++) {
      res->board[y][x] = piece_creer(VIDE_PIECE, VIDE, NON_PROMU);
      res->board[y][x] = piece_creer(VIDE_PIECE, VIDE, NON_PROMU);
    }
  }

  /* Pions */
  for (x = 1; x < 10; x++) {
    res->board[7][x] = piece_creer(NOIR, PION, NON_PROMU);
    res->board[3][x] = piece_creer(BLANC, PION, NON_PROMU);
  }

  /* Tour */

  res->board[8][2] = piece_creer(NOIR, TOUR, NON_PROMU);
  res->board[2][8] = piece_creer(BLANC, TOUR, NON_PROMU);

  /* Roi */

  res->board[9][5] = piece_creer(NOIR, ROI, NON_PROMU);
  res->board[1][5] = piece_creer(BLANC, ROI, NON_PROMU);

  /* Fou */

  res->board[8][8] = piece_creer(NOIR, FOU, NON_PROMU);
  res->board[2][2] = piece_creer(BLANC, FOU, NON_PROMU);

  /* Gold */

  res->board[1][4] = piece_creer(BLANC, GOLD, NON_PROMU);
  res->board[1][6] = piece_creer(BLANC, GOLD, NON_PROMU);
  res->board[9][4] = piece_creer(NOIR, GOLD, NON_PROMU);
  res->board[9][6] = piece_creer(NOIR, GOLD, NON_PROMU);

  /* Sivler */

  res->board[9][3] = piece_creer(NOIR, SILVER, NON_PROMU);
  res->board[9][7] = piece_creer(NOIR, SILVER, NON_PROMU);
  res->board[1][3] = piece_creer(BLANC, SILVER, NON_PROMU);
  res->board[1][7] = piece_creer(BLANC, SILVER, NON_PROMU);

  /* Cavalier */

  res->board[1][2] = piece_creer(BLANC, CAVALIER, NON_PROMU);
  res->board[1][8] = piece_creer(BLANC, CAVALIER, NON_PROMU);
  res->board[9][2] = piece_creer(NOIR, CAVALIER, NON_PROMU);
  res->board[9][8] = piece_creer(NOIR, CAVALIER, NON_PROMU);

  /* Lancier */

  res->board[1][1] = piece_creer(BLANC, LANCIER, NON_PROMU);
  res->board[1][9] = piece_creer(BLANC, LANCIER, NON_PROMU);
  res->board[9][1] = piece_creer(NOIR, LANCIER, NON_PROMU);
  res->board[9][9] = piece_creer(NOIR, LANCIER, NON_PROMU);

  return res;
}
