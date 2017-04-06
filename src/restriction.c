#include "header/restriction.h"
#include "header/mouvement.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * global
 */
coordinate_t movement_checker_tmp;

/**
 * movement restriction
 *
 * Parameters:
 *     game_t       - game_v
 *     coordinate_t - coordinate_input_v
 */
void movement_restriction(game_t *game_v, coordinate_t coordinate_input_v) {
  //======================================================================
  // Main
  //======================================================================
  switch (game_v->board[coordinate_input_v.x][coordinate_input_v.y].type) {
    {
    case PION:
      movement_restriction_general(game_v, coordinate_input_v);
      break;
    }
    {
    case TOUR:
      movement_restriction_tour(game_v, coordinate_input_v);
      break;
    }
    {
    case CAVALIER:
      movement_restriction_general(game_v, coordinate_input_v);
      break;
    }
    {
    case FOU:
      movement_restriction_fou(game_v, coordinate_input_v);
      break;
    }
    {
    case ROI:
      movement_restriction_general(game_v, coordinate_input_v);
      break;
    }
    {
    case GOLD:
      movement_restriction_general(game_v, coordinate_input_v);
      break;
    }
    {
    case SILVER:
      movement_restriction_general(game_v, coordinate_input_v);
      break;
    }
    {
    case LANCIER:
      movement_restriction_general(game_v, coordinate_input_v);
      break;
    }
    {
    case PION_PROMU:
      movement_restriction_general(game_v, coordinate_input_v);
      break;
    }
    {
    case TOUR_PROMU:
      movement_restriction_general(game_v, coordinate_input_v);
      movement_restriction_tour(game_v, coordinate_input_v);
      break;
    }
    {
    case CAVALIER_PROMU:
      movement_restriction_general(game_v, coordinate_input_v);
      break;
    }
    {
    case FOU_PROMU:
      movement_restriction_general(game_v, coordinate_input_v);
      movement_restriction_fou(game_v, coordinate_input_v);
      break;
    }
    {
    case SILVER_PROMU:
      movement_restriction_general(game_v, coordinate_input_v);
      break;
    }
    {
    case LANCIER_PROMU:
      movement_restriction_general(game_v, coordinate_input_v);
      break;
    }
    {
    default:
      break;
    }
  }
}

/**
 * movement general restriction
 *
 * Parameters:
 *     game_t       - game_v
 *     coordinate_t - coordinate_input_v
 */
void movement_restriction_general(game_t *game_v,
                                  coordinate_t coordinate_input_v) {
  //======================================================================
  // Variables
  //======================================================================
  int x, y;

  //======================================================================
  // Main
  //======================================================================
  for (x = 1; x < 10; x++) {
    movement_checker_tmp.x = x;

    for (y = 1; y < 10; y++) {
      movement_checker_tmp.y = y;

      if (movement_valid_helper(game_v, coordinate_input_v,
                                movement_checker_tmp)) {

        if (game_v->board[x][y].type == VIDE) {
          game_v->board[x][y].type = SELECT;
        }
      }
    }
  }
}

/**
 * movement tour restriction
 *
 * Parameters:
 *     game_t       - game_v
 *     coordinate_t - coordinate_input_v
 */
void movement_restriction_tour(game_t *game_v,
                               coordinate_t coordinate_input_v) {
  //======================================================================
  // Variables
  //======================================================================
  coordinate_t movement_checker_1_tmp, movement_checker_2_tmp,
      movement_checker_3_tmp, movement_checker_4_tmp;

  //======================================================================
  // Main
  //======================================================================

  /* Boucle for, vers le bas */
  for (movement_checker_1_tmp.x = coordinate_input_v.x + 1;
       movement_checker_1_tmp.x < 10 &&
       game_v->board[movement_checker_1_tmp.x][coordinate_input_v.y].type ==
           VIDE;
       movement_checker_1_tmp.x++) {

    game_v->board[movement_checker_1_tmp.x][coordinate_input_v.y].type = SELECT;
  }

  /* Boucle for, vers la droite */
  for (movement_checker_2_tmp.y = coordinate_input_v.y + 1;
       movement_checker_2_tmp.y < 10 &&
       game_v->board[coordinate_input_v.x][movement_checker_2_tmp.y].type ==
           VIDE;
       movement_checker_2_tmp.y++) {
    game_v->board[coordinate_input_v.x][movement_checker_2_tmp.y].type = SELECT;
  }

  /* Boucle for vers le haut */

  for (movement_checker_3_tmp.x = coordinate_input_v.x - 1;
       movement_checker_3_tmp.x > 0 &&
       game_v->board[movement_checker_3_tmp.x][coordinate_input_v.y].type ==
           VIDE;
       movement_checker_3_tmp.x--) {

    game_v->board[movement_checker_3_tmp.x][coordinate_input_v.y].type = SELECT;
  }

  /* Boucle for vers la gauche */

  for (movement_checker_4_tmp.y = coordinate_input_v.y - 1;
       movement_checker_4_tmp.y > 0 &&
       game_v->board[coordinate_input_v.x][movement_checker_4_tmp.y].type ==
           VIDE;
       movement_checker_4_tmp.y--) {
    game_v->board[coordinate_input_v.x][movement_checker_4_tmp.y].type = SELECT;
  }
}

/**
 * movement bishop restriction
 *
 * Parameters:
 *     game_t       - game_v
 *     coordinate_t - coordinate_input_v
 */
void movement_restriction_fou(game_t *game_v, coordinate_t coordinate_input_v) {
  //======================================================================
  // Variables
  //======================================================================
  coordinate_t movement_checker_1_tmp, movement_checker_2_tmp,
      movement_checker_3_tmp, movement_checker_4_tmp;

  //======================================================================
  // Main
  //======================================================================

  /* Diagnonal bas droit */
  for (movement_checker_1_tmp.x = coordinate_input_v.x + 1,
      movement_checker_1_tmp.y = coordinate_input_v.y + 1;
       movement_checker_1_tmp.x < 10 && movement_checker_1_tmp.y < 10 &&
       game_v->board[movement_checker_1_tmp.x][movement_checker_1_tmp.y].type ==
           VIDE;
       movement_checker_1_tmp.x++, movement_checker_1_tmp.y++) {

    game_v->board[movement_checker_1_tmp.x][movement_checker_1_tmp.y].type =
        SELECT;
  }
  /* Diagonale haut gauche */

  for (movement_checker_2_tmp.x = coordinate_input_v.x - 1,
      movement_checker_2_tmp.y = coordinate_input_v.y - 1;
       movement_checker_2_tmp.x > 0 && movement_checker_2_tmp.y > 0 &&
       game_v->board[movement_checker_2_tmp.x][movement_checker_2_tmp.y].type ==
           VIDE;
       movement_checker_2_tmp.x--, movement_checker_2_tmp.y--) {
    game_v->board[movement_checker_2_tmp.x][movement_checker_2_tmp.y].type =
        SELECT;
  }

  /* Diagonale bas gauche */
  for (movement_checker_3_tmp.x = coordinate_input_v.x + 1,
      movement_checker_3_tmp.y = coordinate_input_v.y - 1;
       movement_checker_3_tmp.x < 10 && movement_checker_3_tmp.y > 0 &&
       game_v->board[movement_checker_3_tmp.x][movement_checker_3_tmp.y].type ==
           VIDE;
       movement_checker_3_tmp.x++, movement_checker_3_tmp.y--) {
    game_v->board[movement_checker_3_tmp.x][movement_checker_3_tmp.y].type =
        SELECT;
  }

  /* Diagonale haut droit */
  for (movement_checker_4_tmp.x = coordinate_input_v.x - 1,
      movement_checker_4_tmp.y = coordinate_input_v.y + 1;
       movement_checker_4_tmp.x > 0 && movement_checker_4_tmp.y < 10 &&
       game_v->board[movement_checker_4_tmp.x][movement_checker_4_tmp.y].type ==
           VIDE;
       movement_checker_4_tmp.x--, movement_checker_4_tmp.y++) {
    game_v->board[movement_checker_4_tmp.x][movement_checker_4_tmp.y].type =
        SELECT;
  }
}

/**
 * movement restriction destruct
 *
 * Parameters:
 *     game_t - game_v
 */
void movement_restriction_destruct(game_t *game_v) {
  //======================================================================
  // Variables
  //======================================================================
  int x, y;

  //======================================================================
  // Main
  //======================================================================
  for (x = 1; x < 10; x++) {

    for (y = 1; y < 10; y++) {
      movement_checker_tmp.x = x;
      movement_checker_tmp.y = y;

      if (game_v->board[movement_checker_tmp.x][movement_checker_tmp.y].type ==
          SELECT) {
        game_v->board[movement_checker_tmp.x][movement_checker_tmp.y].type =
            VIDE;
      }
    }
  }
}

void movement_restriction_parachute(game_t *game_v) {
  //======================================================================
  // Variables
  //======================================================================
  int x, y;

  //======================================================================
  // Main
  //======================================================================
  for (x = 1; x < 10; x++) {

    for (y = 1; y < 10; y++) {
      movement_checker_tmp.x = x;
      movement_checker_tmp.y = y;

      if (game_v->board[movement_checker_tmp.x][movement_checker_tmp.y].type ==
          VIDE) {
        game_v->board[movement_checker_tmp.x][movement_checker_tmp.y].type =
            SELECT;
      }
    }
  }
}

int restriction_detector(game_t *game_v, coordinate_t coordinate_output_v) {
  if (game_v->board[coordinate_output_v.x][coordinate_output_v.y].type ==
      SELECT)
    return 1;
  return 0;
}
