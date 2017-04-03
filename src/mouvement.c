#include "header/game.h"
#include <stdio.h>

/************ Debut Bloc validation des entrés et sortie **********************/

/** movement_valid_input
 * Permet de valider les coordonnées d'entrés
 * Les coordonées doivent être dans l'échiquier, et doivent correspondre à une
 * case non vide et une piece du même couleur du joueur
 * @params: game_t       - game_v
 *          coordinate_t - coordinate_v
 * @return  int
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
  printf("Vous avez saisie une case vide ou vous avez saisie la pièce de "
         "l'adversaire\n");
  return 0;
}

/** movement_valid_input
 * Permet de valider les coordonnées d'arrivée, Vérifie si les cordoonées sont
 * dans l'échiquier
 * @params :    coordinate_t    -   coordinate_v
 * @return :    int
 */

int movement_valid_output(coordinate_t coordinate_v) {
  return (coordinate_v.x < 11 && coordinate_v.y < 11) ? 1 : 0;
}

/****************** Fin Bloc validation des entrés et sortie ******************/
/****************** Debut des validations des déplacements   ******************/

/** deplacement_valide_pion
 * Détails dans les fonctions
 * @params: game_t       -   game_v
 *          coordinate_t -   coordinate_input_v
 *          coordinate_t -   coordinate_output_v
 * @return: int
 */
int deplacement_valide_pion(game_t *game_v, coordinate_t coordinate_input_v,
                            coordinate_t coordinate_output_v) {
  int movement_tmp;

  /* Initialisation par calcul de différence */
  movement_tmp = coordinate_output_v.x - coordinate_input_v.x;

  /* Condition vertical, les coordonées d'entré et de sortie doivent être le
   * même */
  if (coordinate_input_v.y == coordinate_output_v.y) {

    /* On vérifie la couleur, Si c'est noir et que la différence est -1 ->
     * Déplacement autorisé
     * Si c'est blanc, meme chose mais la différence est 1
     * Sinon 0
     */
    if (game_v->board[coordinate_input_v.x][coordinate_input_v.y].color ==
        NOIR) {
      return (movement_tmp == -1) ? 1 : 0;
    }

    else if (game_v->board[coordinate_input_v.x][coordinate_input_v.y].color ==
             BLANC) {
      return (movement_tmp == 1) ? 1 : 0;
    }
  }

  /* Valeur par défaut de return, si la condition vertical n'est pas vérifié
   * d'avance */
  return 0;
}

/** deplacement_valide_tour
 * Permet de valider le déplacement de la tour (Non promu supposé)
 * Les conditions : Meme horizontal pour entré/sortie (respectivement vertical)
 * @param game_t       -   game_v
 *        coordinate_t -   coordinate_input_v
 *        coordinate_t -   coordinate_output_v
 * @return int
 */
int deplacement_valide_tour(game_t *game_v, coordinate_t coordinate_input_v,
                            coordinate_t coordinate_output_v) {
  return (coordinate_input_v.x == coordinate_output_v.x ||
          coordinate_input_v.y == coordinate_output_v.y)
             ? 1
             : 0;
}

/** deplacement_valide_cavalier
 * Permet de valider le déplacement du cavalier (Non promu supposé)
 * Les conditions : Seulement vers l'avant pour les blanc (resp arriere noir)
 * @params  game_t       -   game_v
 *          coordinate_t -   coordinate_input_v
 *          coordinate_t -   coordinate_output_v
 * @return  int
 */
int deplacement_valide_cavalier(game_t *game_v, coordinate_t coordinate_input_v,
                                coordinate_t coordinate_output_v) {

  /* On vérifie les conditions pour les blancs */

  if (game_v->board[coordinate_input_v.x][coordinate_input_v.y].color ==
      BLANC) {

    /* On vérifie les conditions x+1 et x-1 */
    if (coordinate_input_v.x - 1 == coordinate_output_v.x ||
        coordinate_input_v.x + 1 == coordinate_output_v.x) {

      /* On vérifie les conditions vers l'avant (haut) soit y+2 */
      if (coordinate_input_v.y + 2 == coordinate_output_v.y) {
        return 1;
      }
    }
  }

  /* On vérifie les conditions pour les noirs */

  if (game_v->board[coordinate_input_v.x][coordinate_input_v.y].color == NOIR) {

    /* On vérifie les conditions x+1 et x-1 */
    if (coordinate_input_v.x - 1 == coordinate_output_v.x ||
        coordinate_input_v.x + 1 == coordinate_output_v.x) {

      /* On vérifie les conditions vers l'arriere (bas) soit y-2 */
      if (coordinate_input_v.y - 2 == coordinate_output_v.y) {
        return 1;
      }
    }
  }

  /* Valeur par défaut */

  return 0;
}

/** deplacement_valide_fou
 * Permet de valider le déplacement du fou (Non promu supposé)
 * Les conditions : Diagonnales
 * @params  game_t       -   game_v
 *          coordinate_t -   coordinate_input_v
 *          coordinate_t -   coordinate_output_v
 * @return int
 */
int deplacement_valide_fou(game_t *game_v, coordinate_t coordinate_input_v,
                           coordinate_t coordinate_output_v) {
  int movement_1_tmp;
  int movement_2_tmp;
  int movement_1_bis_tmp;
  int movement_2_bis_tmp;

  /* Initialize */

  movement_1_tmp = (coordinate_output_v.x + coordinate_output_v.y);
  movement_2_tmp = (coordinate_input_v.x + coordinate_input_v.y);

  movement_1_bis_tmp = (coordinate_input_v.x - coordinate_input_v.y);
  movement_2_bis_tmp = (coordinate_output_v.x - coordinate_output_v.y);

  if (movement_1_tmp == movement_2_tmp ||
      movement_2_bis_tmp == movement_1_bis_tmp) {
    return 1;
  }

  return 0;
}
/** deplacement_valide_roi
 * Permet de valider les déplacement du roi
 * Conditions : Déplacement d'une case Seulement
 *                x+1 ou x ou x-1
 *                y+1 ou y ou y-1
 * @params:     game_t       - game_v
 *              coordinate_t - coordinate_input_v
 *              coordinate_t - coordinate_output_v
 * @return      int
 */
int deplacement_valide_roi(game_t *game_v, coordinate_t coordinate_input_v,
                           coordinate_t coordinate_output_v) {
  //======================================================================
  // Main
  //======================================================================
  /* vertical checking */
  if (coordinate_input_v.x - 1 == coordinate_output_v.x ||
      coordinate_input_v.x + 1 == coordinate_output_v.x ||
      coordinate_input_v.x == coordinate_output_v.x) {

    if (coordinate_input_v.y - 1 == coordinate_output_v.y ||
        coordinate_input_v.y + 1 == coordinate_output_v.y ||
        coordinate_input_v.y == coordinate_output_v.y) {
      return 1;
    }
  }

  return 0;
}

/** deplacement_valide_gold
 * Permet de valider les déplacement du gold
 * Reprends le Prototype du roi, mais avec une Restrictions y-1 pour les blanc
 * et y+1 pour les noir
 * @params :  game_t       - game_v
 *            coordinate_t - coordinate_input_v
 *            coordinate_t - coordinate_output_v
 * @return    int
 */
int deplacement_valide_gold(game_t *game_v, coordinate_t coordinate_input_v,
                            coordinate_t coordinate_output_v) {
  if (piece_couleur(
          game_v->board[coordinate_input_v.x][coordinate_input_v.y]) == BLANC) {

    /* Verifications déplacement sur x */
    if (coordinate_input_v.x - 1 == coordinate_output_v.x ||
        coordinate_input_v.x + 1 == coordinate_output_v.x ||
        coordinate_input_v.x == coordinate_output_v.x) {

      /* Restrictions déplacement sur y+1 et y*/

      if (coordinate_input_v.y + 1 == coordinate_output_v.y ||
          coordinate_input_v.y == coordinate_output_v.y) {
        return 1;
      }
      return 0;
    }
  }

  if (piece_couleur(
          game_v->board[coordinate_input_v.x][coordinate_input_v.y]) == NOIR) {

    /* Verifications déplacement sur y */
    if (coordinate_input_v.x - 1 == coordinate_output_v.x ||
        coordinate_input_v.x + 1 == coordinate_output_v.x ||
        coordinate_input_v.x == coordinate_output_v.x) {

      /* Restrictions déplacement sur y-1 et y */
      if (coordinate_input_v.y - 1 == coordinate_output_v.y ||
          coordinate_input_v.y == coordinate_output_v.y) {
        return 1;
      }
      return 0;
    }
  }

  return 0;
}

/** deplacement_valide_silver
 * Permet de valider les déplacement du silver
 * Reprends le Prototype du roi et silver, mais avec une Restrictions de pas de
 * déplacement sur x et y+1 pour les noir
 * @params :  game_t       - game_v
 *            coordinate_t - coordinate_input_v
 *            coordinate_t - coordinate_output_v
 * @return    int
 */
int deplacement_valide_silver(game_t *game_v, coordinate_t coordinate_input_v,
                              coordinate_t coordinate_output_v) {
  if (piece_couleur(
          game_v->board[coordinate_input_v.x][coordinate_input_v.y]) == BLANC) {

    /* Verifications déplacement sur les cases Diagonnales (coins) */
    if (coordinate_input_v.x - 1 == coordinate_output_v.x ||
        coordinate_input_v.x + 1 == coordinate_output_v.x) {

      /* Restrictions déplacement sur y et y-1*/

      if (coordinate_input_v.y + 1 == coordinate_output_v.y ||
          coordinate_input_v.y - 1 == coordinate_output_v.y) {
        return 1;
      }
      return 0;
    }

    /* Restriction sur y+1 */
    else if (coordinate_input_v.x == coordinate_output_v.x) {
      if (coordinate_input_v.y + 1 == coordinate_output_v.y) {
        return 1;
      }
    }
    return 0;
  }

  if (piece_couleur(
          game_v->board[coordinate_input_v.x][coordinate_input_v.y]) == NOIR) {

    /* Verifications déplacement sur les cases Diagonnales (coins) */
    if (coordinate_input_v.x - 1 == coordinate_output_v.x ||
        coordinate_input_v.x + 1 == coordinate_output_v.x) {

      /* Restrictions déplacement sur y et y-1*/

      if (coordinate_input_v.y + 1 == coordinate_output_v.y ||
          coordinate_input_v.y - 1 == coordinate_output_v.y) {
        return 1;
      }
      return 0;
    }

    /* Restriction sur y-1 */
    else if (coordinate_input_v.x == coordinate_output_v.x) {
      if (coordinate_input_v.y - 1 == coordinate_output_v.y) {
        return 1;
      }
    }
    return 0;
  }

  return 0;
}

int deplacement_valide_parachutage(game_t *game_v,
                                   coordinate_t coordinate_input_v,
                                   coordinate_t coordinate_output_v) {
  if (game_v->player == BLANC) {
    if (coordinate_input_v.x >= 0 && coordinate_input_v.x < 11) {
      if (coordinate_input_v.y == 10) {
        return (game_v->board[coordinate_output_v.x][coordinate_output_v.y]
                    .color == VIDE_PIECE)
                   ? 1
                   : 0;
      }
    }
  }
  if (game_v->player == NOIR) {
    if (coordinate_input_v.y > 0 && coordinate_input_v.y < 11) {
      if (coordinate_input_v.x == 10) {
        return (game_v->board[coordinate_output_v.x][coordinate_output_v.y]
                    .color == VIDE_PIECE)
                   ? 1
                   : 0;
      }
    }
  }
  return 0;
}
/****************** Fin des validations des déplacements   ******************/

/** movement_valid_helper
 * movement board validator for helper
 *
 * Parameters:
 *     game_t       - game_v
 *     coordinate_t - coordinate_input_v
 *     coordinate_t - coordinate_output_v
 *
 * @return int
 */
int movement_valid_helper(game_t *game_v, coordinate_t coordinate_input_v,
                          coordinate_t coordinate_output_v) {
  //======================================================================
  // Main
  //======================================================================
  switch (game_v->board[coordinate_input_v.x][coordinate_input_v.y].type) {
    {
    case PION:
      return (deplacement_valide_pion(game_v, coordinate_input_v,
                                      coordinate_output_v))
                 ? 1
                 : 0;
      break;
    }
    {
    case TOUR:
      return (deplacement_valide_tour(game_v, coordinate_input_v,
                                      coordinate_output_v))
                 ? 1
                 : 0;
      break;
    }
    {
    case CAVALIER:

      return (deplacement_valide_cavalier(game_v, coordinate_input_v,
                                          coordinate_output_v))
                 ? 1
                 : 0;

      break;
    }
    {
    case FOU:

      return (deplacement_valide_fou(game_v, coordinate_input_v,
                                     coordinate_output_v))
                 ? 1
                 : 0;
      break;
    }
    {
    case GOLD:

      return (deplacement_valide_gold(game_v, coordinate_input_v,
                                      coordinate_output_v))
                 ? 1
                 : 0;
      break;
    }
    {
    case ROI:

      return (deplacement_valide_roi(game_v, coordinate_input_v,
                                     coordinate_output_v))
                 ? 1
                 : 0;
      break;
    }
    {
    case SILVER:
      return (deplacement_valide_silver(game_v, coordinate_input_v,
                                        coordinate_output_v))
                 ? 1
                 : 0;
      break;
    }
    {
    default:
      return 0;
    }
  }
  return 0;
}
