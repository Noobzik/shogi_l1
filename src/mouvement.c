#include "header/game.h"
#include <stdio.h>

/** movement_valid_input
 * Permet de valider les coordonnées d'entrés
 * Les coordonées doivent être dans l'échiquier, et doivent correspondre à une
 * case non vide Parameters: game_t       - game_v coordinate_t - coordinate_v
 *
 * @return int
 */
int movement_valid_input(game_t *game_v, coordinate_t coordinate_v) {
  //======================================================================
  // Main
  //======================================================================
  if (coordinate_v.x < 11 && coordinate_v.y < 11) {

    if (game_v->board[coordinate_v.x][coordinate_v.y].type != 0) {

      if (game_v->player ==
          game_v->board[coordinate_v.x][coordinate_v.y].color) {
        return 1;
      }
    }
  }
  printf("Vous avez saisie une case vide\n");
  return 0;
}
