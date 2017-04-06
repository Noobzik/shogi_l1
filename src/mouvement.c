#include "header/mouvement.h"
#include "header/game.h"
#include "header/piece.h"
#include "header/restriction.h"
#include <stdio.h>
#include <string.h>
#define MAX_CHAR 256

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
 * dans l'échiquier au format 9x9 (Sans la reserve)
 * @params :    coordinate_t    -   coordinate_v
 * @return :    int
 */

int movement_valid_output(coordinate_t coordinate_v) {
  return (coordinate_v.x > 0 && coordinate_v.y < 10 && coordinate_v.x < 10 &&
          coordinate_v.y > 0)
             ? 1
             : 0;
}

/**
 * movement board validator
 *
 * Parameters:
 *     game_t       - game_v
 *     coordinate_t - coordinate_input_v
 *     coordinate_t - coordinate_output_v
 */
void deplacement_valide(game_t *game_v, coordinate_t coordinate_input_v,
                        coordinate_t coordinate_output_v) {
  //======================================================================
  // Main
  //======================================================================
  int test = 0, y;
  piece_color_e color_tmp =
      game_v->board[coordinate_input_v.x][coordinate_input_v.y].color;

  if ((coordinate_input_v.x != coordinate_output_v.x ||
       coordinate_input_v.y != coordinate_output_v.y) &&
      (game_v->board[coordinate_input_v.x][coordinate_input_v.y].color !=
       game_v->board[coordinate_output_v.x][coordinate_output_v.y].color)) {

    switch (game_v->board[coordinate_input_v.x][coordinate_input_v.y].type) {
      {
      case PION:

        /* Develement des Parachutage du PION
         * Algo => Pas deuxieme pion sur la meme colonne
         */

        /* Ce gros if doit vérifier si les coordonnées d'entré sont dans la
         * reserve ou pas */
        if ((coordinate_input_v.x == 0 &&
             (coordinate_input_v.y < 11 && coordinate_input_v.y > -1)) ||
            (coordinate_input_v.y == 0 &&
             (coordinate_input_v.x < 11 && coordinate_input_v.y >= 0))) {

          /* Boucle for pour tester si il y a un pion dans la colonne darrivé*/
          for (y = 1; y < 10; y++) {

            if (game_v->board[coordinate_output_v.y][y].type == PION &&
                game_v->board[coordinate_output_v.y][y].color == color_tmp) {
              test = 1;
              printf("Erreur, Il y a déjà un pion dans la colonne d'arrivée\n");
              y = 42;
            }
          }
          if (test == 0)

            movement_restriction_parachute(game_v);

          /* Si c'est pas le cas , on applique les déplacement */
          if (test == 0 && restriction_detector(game_v, coordinate_output_v)) {
            deplacement_apply(game_v, coordinate_input_v, coordinate_output_v);
          }
          /* Fin du Develement pour l'algo de Parachutage pion*/
        } else if (deplacement_valide_pion(game_v, coordinate_input_v,
                                           coordinate_output_v) &&
                   restriction_detector(game_v, coordinate_output_v)) {

          deplacement_apply(game_v, coordinate_input_v, coordinate_output_v);
          printf("Le PION à été deplacé de (%d;%d) à (%d;%d) avec succès.\n",
                 coordinate_input_v.x, coordinate_input_v.y,
                 coordinate_output_v.x, coordinate_output_v.y);
        } else {
          printf("Le déplacement du PION à échoué.\n");
        }

        break;
      }
      {
      case PION_PROMU:
        if (deplacement_valide_pion_promu(game_v, coordinate_input_v,
                                          coordinate_output_v) &&
            restriction_detector(game_v, coordinate_output_v)) {
          deplacement_apply(game_v, coordinate_input_v, coordinate_output_v);
          printf(
              "Le PION_PROMU à été deplace de (%d;%d) à (%d;%d) avec succès.\n",
              coordinate_input_v.x, coordinate_input_v.y, coordinate_output_v.x,
              coordinate_output_v.y);
        } else {
          printf("Le déplacement du PION_PROMU à échoué\n");
        }
        break;
      }
      {
      case TOUR:
        if ((coordinate_input_v.x != coordinate_output_v.x ||
             coordinate_input_v.y != coordinate_output_v.y) &&
            (game_v->board[coordinate_input_v.x][coordinate_input_v.y].color !=
             game_v->board[coordinate_output_v.x][coordinate_output_v.y]
                 .color)) {
          movement_restriction_parachute(game_v);
        }

        if (deplacement_valide_tour(game_v, coordinate_input_v,
                                    coordinate_output_v) &&
            restriction_detector(game_v, coordinate_output_v)) {
          deplacement_apply(game_v, coordinate_input_v, coordinate_output_v);
          printf("La tour à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
                 coordinate_input_v.x, coordinate_input_v.y,
                 coordinate_output_v.x, coordinate_output_v.y);
        }

        else {
          printf("Le deplacement de la tour à échoué.\n");
        }

        break;
      }
      {
      case TOUR_PROMU:

        if (deplacement_valide_tour_promu(game_v, coordinate_input_v,
                                          coordinate_output_v) &&
            restriction_detector(game_v, coordinate_output_v)) {
          deplacement_apply(game_v, coordinate_input_v, coordinate_output_v);
          printf(
              "La TOUR_PROMU à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
              coordinate_input_v.x, coordinate_input_v.y, coordinate_output_v.x,
              coordinate_output_v.y);
        }

        else {
          printf("Le déplacement de la TOUR_PROMU à échoué.\n");
        }

        break;
      }
      {
      case CAVALIER:
        if ((coordinate_input_v.x != coordinate_output_v.x ||
             coordinate_input_v.y != coordinate_output_v.y) &&
            (game_v->board[coordinate_input_v.x][coordinate_input_v.y].color !=
             game_v->board[coordinate_output_v.x][coordinate_output_v.y]
                 .color)) {
          movement_restriction_parachute(game_v);
        }

        if (deplacement_valide_cavalier(game_v, coordinate_input_v,
                                        coordinate_output_v) &&
            restriction_detector(game_v, coordinate_output_v)) {
          deplacement_apply(game_v, coordinate_input_v, coordinate_output_v);
          printf(
              "Le cavalier à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
              coordinate_input_v.x, coordinate_input_v.y, coordinate_output_v.x,
              coordinate_output_v.y);
        }

        else {
          printf("Le deplacement du cavalier à échoué.\n");
        }

        break;
      }
      {
      case CAVALIER_PROMU:

        if (deplacement_valide_cavalier_promu(game_v, coordinate_input_v,
                                              coordinate_output_v) &&
            restriction_detector(game_v, coordinate_output_v)) {
          deplacement_apply(game_v, coordinate_input_v, coordinate_output_v);
          printf("Le CAVALIER_PROMU à été déplacé de (%d;%d) a (%d;%d) avec "
                 "succès.\n",
                 coordinate_input_v.x, coordinate_input_v.y,
                 coordinate_output_v.x, coordinate_output_v.y);
        }

        else {
          printf("Le déplacement du CAVALIER_PROMU à échoué.\n");
        }

        break;
      }
      {
      case FOU:

        if ((coordinate_input_v.x != coordinate_output_v.x ||
             coordinate_input_v.y != coordinate_output_v.y) &&
            (game_v->board[coordinate_input_v.x][coordinate_input_v.y].color !=
             game_v->board[coordinate_output_v.x][coordinate_output_v.y]
                 .color)) {
          movement_restriction_parachute(game_v);
        }

        else if (deplacement_valide_fou(game_v, coordinate_input_v,
                                        coordinate_output_v) &&
                 restriction_detector(game_v, coordinate_output_v)) {
          deplacement_apply(game_v, coordinate_input_v, coordinate_output_v);
          printf("Le FOU à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
                 coordinate_input_v.x, coordinate_input_v.y,
                 coordinate_output_v.x, coordinate_output_v.y);
        }

        else {
          printf("Le deplacement du FOU à échoué.\n");
        }

        break;
      }
      {
      case FOU_PROMU:

        if (deplacement_valide_fou_promu(game_v, coordinate_input_v,
                                         coordinate_output_v) &&
            restriction_detector(game_v, coordinate_output_v)) {
          deplacement_apply(game_v, coordinate_input_v, coordinate_output_v);
          printf(
              "Le FOU_PROMU à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
              coordinate_input_v.x, coordinate_input_v.y, coordinate_output_v.x,
              coordinate_output_v.y);
        } else {
          printf("Le deplacement du FOU_PROMU à échoué.\n");
        }

        break;
      }
      {
      case GOLD:

        if ((coordinate_input_v.x != coordinate_output_v.x ||
             coordinate_input_v.y != coordinate_output_v.y) &&
            (game_v->board[coordinate_input_v.x][coordinate_input_v.y].color !=
             game_v->board[coordinate_output_v.x][coordinate_output_v.y]
                 .color)) {
          movement_restriction_parachute(game_v);
        }

        else if (deplacement_valide_gold(game_v, coordinate_input_v,
                                         coordinate_output_v) &&
                 restriction_detector(game_v, coordinate_output_v)) {
          deplacement_apply(game_v, coordinate_input_v, coordinate_output_v);
          printf("Le GOLD à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
                 coordinate_input_v.x, coordinate_input_v.y,
                 coordinate_output_v.x, coordinate_output_v.y);
        } else {
          printf("Le déplacement du GOLD à échoué.\n");
        }

        break;
      }
      {
      case SILVER:

        if ((coordinate_input_v.x != coordinate_output_v.x ||
             coordinate_input_v.y != coordinate_output_v.y) &&
            (game_v->board[coordinate_input_v.x][coordinate_input_v.y].color !=
             game_v->board[coordinate_output_v.x][coordinate_output_v.y]
                 .color)) {
          movement_restriction_parachute(game_v);
        }

        else if (deplacement_valide_silver(game_v, coordinate_input_v,
                                           coordinate_output_v) &&
                 restriction_detector(game_v, coordinate_output_v)) {
          deplacement_apply(game_v, coordinate_input_v, coordinate_output_v);
          printf("Le SILVER à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
                 coordinate_input_v.x, coordinate_input_v.y,
                 coordinate_output_v.x, coordinate_output_v.y);
        } else {
          printf("Le déplacement du SILVER à échoué.\n");
        }

        break;
      }
      {
      case SILVER_PROMU:

        if (deplacement_valide_gold(game_v, coordinate_input_v,
                                    coordinate_output_v) &&
            restriction_detector(game_v, coordinate_output_v)) {
          deplacement_apply(game_v, coordinate_input_v, coordinate_output_v);
          printf("Le SILVER_PROMU à été déplacé de (%d;%d) a (%d;%d) avec "
                 "succès.\n",
                 coordinate_input_v.x, coordinate_input_v.y,
                 coordinate_output_v.x, coordinate_output_v.y);
        } else {
          printf("Le déplacement du SILVER_PROMU à échoué.\n");
        }

        break;
      }
      {
      case ROI:

        if (deplacement_valide_roi(game_v, coordinate_input_v,
                                   coordinate_output_v) &&
            restriction_detector(game_v, coordinate_output_v)) {
          deplacement_apply(game_v, coordinate_input_v, coordinate_output_v);
          printf("Le ROI à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
                 coordinate_input_v.x, coordinate_input_v.y,
                 coordinate_output_v.x, coordinate_output_v.y);
        } else {
          printf("Le deplacement du ROI à échoué.\n");
        }

        break;
      }
      {
      case LANCIER:

        if ((coordinate_input_v.x != coordinate_output_v.x ||
             coordinate_input_v.y != coordinate_output_v.y) &&
            (game_v->board[coordinate_input_v.x][coordinate_input_v.y].color !=
             game_v->board[coordinate_output_v.x][coordinate_output_v.y]
                 .color)) {
          movement_restriction_parachute(game_v);
        }

        else if (deplacement_valide_lancier(game_v, coordinate_input_v,
                                            coordinate_output_v) &&
                 restriction_detector(game_v, coordinate_output_v)) {
          deplacement_apply(game_v, coordinate_input_v, coordinate_output_v);
          printf("Le LANCIER à été déplacé de (%d;%d) à (%d;%d) avec succès\n",
                 coordinate_input_v.x, coordinate_input_v.y,
                 coordinate_output_v.x, coordinate_output_v.y);
        } else {
          printf("Le déplacement du LANCIER à échoué\n");
        }
        break;
      }
      {
      case LANCIER_PROMU:
        if (deplacement_valide_lancier_promu(game_v, coordinate_input_v,
                                             coordinate_output_v) &&
            restriction_detector(game_v, coordinate_output_v)) {
          deplacement_apply(game_v, coordinate_input_v, coordinate_output_v);
          printf("Le LANCIER_PROMU à été déplacé de (%d;%d) à (%d;%d) avec "
                 "succès\n",
                 coordinate_input_v.x, coordinate_input_v.y,
                 coordinate_output_v.x, coordinate_output_v.y);
        } else {
          printf("Le déplacement du LANCIER_PROMU à échoué\n");
        }
      }
      {
      default:
        break;
      }
    }
  } else {
    printf("Le deplacement à été annulée.\n");
  }
}

int movement_valid_win(game_t *game_v, coordinate_t coordinate_v) {
  if (game_v->player == 1) {

    if (game_v->board[coordinate_v.x][coordinate_v.y].type == ROI) {
      printf("La partie est gagné par les BLANCS\n");
      return 0;
    }
  }

  else if (game_v->player == 0) {
    if (game_v->board[coordinate_v.x][coordinate_v.y].type == ROI) {
      printf("La partie est gagné par les NOIR\n");
      return 0;
    }
  }

  return 1;
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
    if (coordinate_input_v.y - 1 == coordinate_output_v.y ||
        coordinate_input_v.y + 1 == coordinate_output_v.y) {

      /* On vérifie les conditions vers l'avant (haut) soit y+2 */
      if (coordinate_input_v.x + 2 == coordinate_output_v.x) {
        return 1;
      }
    }
  }

  /* On vérifie les conditions pour les noirs */

  if (game_v->board[coordinate_input_v.x][coordinate_input_v.y].color == NOIR) {

    /* On vérifie les conditions y+1 et y-1 */
    if (coordinate_input_v.y - 1 == coordinate_output_v.y ||
        coordinate_input_v.y + 1 == coordinate_output_v.y) {

      /* On vérifie les conditions vers l'arriere (bas) soit x-2 */
      if (coordinate_input_v.x - 2 == coordinate_output_v.x) {
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

  return (movement_1_tmp == movement_2_tmp ||
          movement_2_bis_tmp == movement_1_bis_tmp)
             ? 1
             : 0;
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

    /* Restriction sur les diagonales en arriere */
    if (coordinate_input_v.x - 1 == coordinate_output_v.x) {
      if (coordinate_input_v.y == coordinate_output_v.y)
        return 1;
    }
    /* Deplacement vers l'avant */
    if (coordinate_input_v.x + 1 == coordinate_output_v.x &&
        (coordinate_input_v.y + 1 == coordinate_output_v.y ||
         coordinate_input_v.y - 1 == coordinate_output_v.y ||
         coordinate_input_v.y == coordinate_output_v.y)) {
      return 1;
    }
    /* Deplacement vers la gauche sur la meme ligne */
    if (coordinate_input_v.x == coordinate_output_v.x &&
        coordinate_input_v.y - 1 == coordinate_output_v.y) {
      return 1;
    }
    /* Deplacement vers la droite sur la meme ligne */
    if (coordinate_input_v.x == coordinate_output_v.x &&
        coordinate_input_v.y + 1 == coordinate_output_v.y) {
      return 1;
    }
  }

  if (piece_couleur(
          game_v->board[coordinate_input_v.x][coordinate_input_v.y]) == NOIR) {

    /* Restriction sur les diagonales en arriere */
    if (coordinate_input_v.x + 1 == coordinate_output_v.x) {
      if (coordinate_input_v.y == coordinate_output_v.y)
        return 1;
    }
    /* Deplacement vers l'avant */
    if (coordinate_input_v.x - 1 == coordinate_output_v.x &&
        (coordinate_input_v.y + 1 == coordinate_output_v.y ||
         coordinate_input_v.y - 1 == coordinate_output_v.y ||
         coordinate_input_v.y == coordinate_output_v.y)) {
      return 1;
    }
    /* Deplacement vers la gauche sur la meme ligne */
    if (coordinate_input_v.x == coordinate_output_v.x &&
        coordinate_input_v.y - 1 == coordinate_output_v.y) {
      return 1;
    }
    /* Deplacement vers la droite sur la meme ligne */
    if (coordinate_input_v.x == coordinate_output_v.x &&
        coordinate_input_v.y + 1 == coordinate_output_v.y) {
      return 1;
    }
  }

  return 0;
}

/** deplacement_valide_silver
 * Permet de valider les déplacement du silver
 * Reprends le Prototype du roi et gold, mais avec une Restrictions de pas de
 * déplacement sur x et y+1 pour les noir
 * @params :  game_t       - game_v
 *            coordinate_t - coordinate_input_v
 *            coordinate_t - coordinate_output_v
 * @return    int
 */
int deplacement_valide_silver(game_t *game_v, coordinate_t coordinate_input_v,
                              coordinate_t coordinate_output_v) {

  /* En faite c'est les noir ici */
  if (piece_couleur(
          game_v->board[coordinate_input_v.x][coordinate_input_v.y]) == BLANC) {

    /* Restrictions au déplacement ligne +1 et ses diagonales +1 */
    if (coordinate_input_v.x + 1 == coordinate_output_v.x &&
        (coordinate_input_v.y + 1 == coordinate_output_v.y ||
         coordinate_input_v.y - 1 == coordinate_output_v.y ||
         coordinate_input_v.y == coordinate_output_v.y)) {
      return 1;
    }

    /* Restrictions aux diagonales arriere */
    if (coordinate_input_v.x - 1 == coordinate_output_v.x &&
        (coordinate_input_v.y + 1 == coordinate_output_v.y ||
         coordinate_input_v.y - 1 == coordinate_output_v.y))
      return 1;
  }

  /* En faite c'est les blanc ici */
  if (piece_couleur(
          game_v->board[coordinate_input_v.x][coordinate_input_v.y]) == NOIR) {

    /* Restrictions au déplacement ligne +1 et ses diagonales +1 */
    if (coordinate_input_v.x - 1 == coordinate_output_v.x &&
        (coordinate_input_v.y + 1 == coordinate_output_v.y ||
         coordinate_input_v.y - 1 == coordinate_output_v.y ||
         coordinate_input_v.y == coordinate_output_v.y)) {
      return 1;
    }

    /* Restrictions aux diagonales arriere */
    if (coordinate_input_v.x + 1 == coordinate_output_v.x &&
        (coordinate_input_v.y + 1 == coordinate_output_v.y ||
         coordinate_input_v.y - 1 == coordinate_output_v.y))
      return 1;
  }

  return 0;
}

/** deplacement_valide_lancier
 *  Le lancier se deplace seulement en vertical, il ne peut pas revenir en
 * arrière
 *  @params:    game_t          -   game_v
 *              coordinate_t    -   coordinate_input_v
 *              coordinate_t    -   coordinate_output_v
 *  @return:    int
 */
int deplacement_valide_lancier(game_t *game_v, coordinate_t coordinate_input_v,
                               coordinate_t coordinate_output_v) {

  if (coordinate_input_v.y == coordinate_output_v.y) {
    if ((coordinate_input_v.x < coordinate_output_v.x) &&
        piece_couleur(
            game_v->board[coordinate_input_v.x][coordinate_input_v.y]) == BLANC)
      return 1;
    else if ((coordinate_input_v.x > coordinate_output_v.x) &&
             piece_couleur(
                 game_v->board[coordinate_input_v.x][coordinate_input_v.y]) ==
                 NOIR)
      return 1;
  }
  return 0;
}

/** deplacement_valide_parachutage
 * Permet de valider un déplacement depuis la réserve
 * Condition, les coordonées de départs doit correspondre à la reserve du
 * joueur actuelle et les coordonnees d'arrivée à une case vide
 */
int deplacement_valide_parachutage(game_t *game_v,
                                   coordinate_t coordinate_input_v,
                                   coordinate_t coordinate_output_v) {

  /*  Parachutage blanc
   if (game_v->player == BLANC) {

      Test si les coordonnées d'entré correspondent a la reserve
     if (coordinate_input_v.x >= 0 && coordinate_input_v.x < 11) {
       if (coordinate_input_v.y == 10) {

         Teste si les coordonnées de sortie est une case vide
         return (game_v->board[coordinate_output_v.x][coordinate_output_v.y]
                     .color == VIDE_PIECE)
                    ? 1
                    : 0;
       }
     }
   }

    Parachutage noir

   if (game_v->player == NOIR) {

      Test si les coordonnées d'entré correspondent a la reserve
     if (coordinate_input_v.y > 0 && coordinate_input_v.y < 11) {
       if (coordinate_input_v.x == 10) {

          Test si les coordonnées de sortie correspondent à une case vide
         return (game_v->board[coordinate_output_v.x][coordinate_output_v.y]
                     .color == VIDE_PIECE)
                    ? 1
                    : 0;
       }
     }
 }*/
  return 0;
}
/****************** Fin des validations des déplacements   ******************/
/**************** Debut des validations des déplacements  PROMU *************/

/** deplacement_valide_pion_promu
 * Algo de GOLD
 * @params :   game_t          -   game_v
 *             coordinate_t    -   coordinate_input_v
 *             coordinate_t    -   coordinate_output_v
 * @return :   int
 */
int deplacement_valide_pion_promu(game_t *game_v,
                                  coordinate_t coordinate_input_v,
                                  coordinate_t coordinate_output_v) {
  return deplacement_valide_gold(game_v, coordinate_input_v,
                                 coordinate_output_v);
}

/** deplacement_valide_tour_promu
 *  Algo de TOUR + ROI
 *  @params:        game_t          -       game_v
 *                  coordinate_t    -       coordinate_input_v
 *                  coordinate_t    -       coordinate_output_v
 *  @return:        int
 */
int deplacement_valide_tour_promu(game_t *game_v,
                                  coordinate_t coordinate_input_v,
                                  coordinate_t coordinate_output_v) {
  return (
      deplacement_valide_tour(game_v, coordinate_input_v,
                              coordinate_output_v) ||
      deplacement_valide_roi(game_v, coordinate_input_v, coordinate_output_v));
}

/** deplacement_valide_cavalier_promu
 *  Algo de GOLD
 *  @params:        game_t          -       game_v
 *                  coordinate_t    -       coordinate_input_v
 *                  coordinate_t    -       coordinate_output_v
 *  @return:        int
 */
int deplacement_valide_cavalier_promu(game_t *game_v,
                                      coordinate_t coordinate_input_v,
                                      coordinate_t coordinate_output_v) {
  return (
      deplacement_valide_gold(game_v, coordinate_input_v, coordinate_output_v));
}

/** deplacement_valide_fou_promu
 *  Algo de FOU + ROI
 *  @params:        game_t          -       game_v
 *                  coordinate_t    -       coordinate_input_v
 *                  coordinate_t    -       coordinate_output_v
 *  @return:        int
 */
int deplacement_valide_fou_promu(game_t *game_v,
                                 coordinate_t coordinate_input_v,
                                 coordinate_t coordinate_output_v) {
  return (
      deplacement_valide_fou(game_v, coordinate_input_v, coordinate_output_v) ||
      deplacement_valide_roi(game_v, coordinate_input_v, coordinate_output_v));
}

/** deplacement_valide_silver_promu
 *  Algo de GOLD
 *  @params:        game_t          -       game_v
 *                  coordinate_t    -       coordinate_input_v
 *                  coordinate_t    -       coordinate_output_v
 *  @return:        int
 */
int deplacement_valide_silver_promu(game_t *game_v,
                                    coordinate_t coordinate_input_v,
                                    coordinate_t coordinate_output_v) {
  return (
      deplacement_valide_gold(game_v, coordinate_input_v, coordinate_output_v));
}

/** deplacement_valide_lancier_promu
 *  Le lancier se deplace seulement en vertical
 *  @params:    game_t          -   game_v
 *              coordinate_t    -   coordinate_input_v
 *              coordinate_t    -   coordinate_output_v
 *  @return:    int
 */
int deplacement_valide_lancier_promu(game_t *game_v,
                                     coordinate_t coordinate_input_v,
                                     coordinate_t coordinate_output_v) {
  return deplacement_valide_gold(game_v, coordinate_input_v,
                                 coordinate_output_v);
}
/**************** FIN des validations des déplacements  PROMU
 * ****************/

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
    case PION_PROMU:
      return (deplacement_valide_pion_promu(game_v, coordinate_input_v,
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
    case TOUR_PROMU:
      return (deplacement_valide_tour_promu(game_v, coordinate_input_v,
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
    case CAVALIER_PROMU:
      return (deplacement_valide_cavalier_promu(game_v, coordinate_input_v,
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
    case FOU_PROMU:
      return (deplacement_valide_fou_promu(game_v, coordinate_input_v,
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
    case SILVER_PROMU:
      return (deplacement_valide_silver_promu(game_v, coordinate_input_v,
                                              coordinate_output_v))
                 ? 1
                 : 0;
      break;
    }
    {
    case LANCIER:
      return (deplacement_valide_lancier(game_v, coordinate_input_v,
                                         coordinate_output_v))
                 ? 1
                 : 0;
    }
    {
    case LANCIER_PROMU:
      return (deplacement_valide_lancier_promu(game_v, coordinate_input_v,
                                               coordinate_output_v))
                 ? 1
                 : 0;
    }
    {
    default:
      return 0;
    }
  }
  return 0;
}

/** movement is_promoted
 *  Permet de savoir si la piece en coordonnées d'arrivé a la possibilité
 * d'être promu
 *  @params:    game_t          -   game_v
 *              coordinate_t    -   coordinate_input_v
 *              coordinate_t    -   coordinate_output_v
 *  @return:    void
 */
int is_promoted(game_t *game_v, coordinate_t coordinate_input_v,
                coordinate_t coordinate_output_v) {

  char promotion_confirmation[MAX_CHAR];

  /* On veut pas promouvoir les roi et les gold */

  if (game_v->board[coordinate_input_v.x][coordinate_input_v.y].type == GOLD ||
      game_v->board[coordinate_input_v.x][coordinate_input_v.y].type == ROI) {
    return 0;
  }
  /* Application des règle spécifique de promotion pour le cavalier */

  else if (game_v->board[coordinate_input_v.x][coordinate_input_v.y].type ==
           CAVALIER) {
    if (game_v->player == 0) {
      if (coordinate_output_v.x == 3) {
        printf("Voulez vous promovoir la piece ? (oui/non)\n");

        if (scanf("%s", promotion_confirmation) != 1) {
          printf("Entrez au moins un caractere\n");
        }

        if (strcmp(promotion_confirmation, "oui") == 0) {
          promote_grant(
              &game_v->board[coordinate_input_v.x][coordinate_input_v.y]);
          printf("La pièce à été promu.\n");
          return 1;
        }
      } else if (coordinate_output_v.x == 2 || coordinate_output_v.x == 1) {
        printf("(Info) Votre pièce a été directement promu\n");
        promote_grant(
            &game_v->board[coordinate_input_v.x][coordinate_input_v.y]);
        return 1;
      }
    }

    else if (game_v->player == 1) {
      if (coordinate_output_v.x == 7) {
        printf("Voulez vous promovoir la piece ? (oui/non)\n");

        if (scanf("%s", promotion_confirmation) != 1) {
          printf("Entrez au moins un caractere\n");
        }

        if (strcmp(promotion_confirmation, "oui") == 0) {
          promote_grant(
              &game_v->board[coordinate_input_v.x][coordinate_input_v.y]);
          printf("La pièce à été promu.\n");
          return 1;
        }
      } else if (coordinate_output_v.x == 8 || coordinate_output_v.x == 9) {
        printf("(Info) Votre pièce a été directement promu\n");
        promote_grant(
            &game_v->board[coordinate_input_v.x][coordinate_input_v.y]);
        return 1;
      }
    }
  }

  /* Si la piece selectionné est une piece de la reserve, on arrete la fonction
   */
  else if (((coordinate_input_v.x == 0 && coordinate_input_v.y < 11) ||
            (coordinate_input_v.x == 10 && coordinate_input_v.y < 11))) {
    return 0;
  }

  /* Sinon : Application du cas général */
  else {
    if (game_v->board[coordinate_input_v.x][coordinate_input_v.y].statut ==
        NON_PROMU) {

      /* Traitement pour joueur BLANC */

      if (game_v->player == 0) {

        /* Test si la pièce à atteint les deux premiers ligne adverse */
        if (coordinate_output_v.x == 3 || coordinate_output_v.x == 2) {

          /* Application strict du règlement : Laisser le choix*/
          printf("Voulez vous promovoir la piece ? (oui/non)\n");

          if (scanf("%s", promotion_confirmation) != 1) {
            printf("Entrez au moins un caractere\n");
          }

          if (strcmp(promotion_confirmation, "oui") == 0) {
            promote_grant(
                &game_v->board[coordinate_input_v.x][coordinate_input_v.y]);
            printf("La pièce à été promu.\n");
            return 1;
          }

          /* Application strict du règlement : Promouvoir automatiquement*/
        } else if (coordinate_output_v.x == 1) {
          printf("(Info) Votre pièce a été directement promu\n");
          promote_grant(
              &game_v->board[coordinate_input_v.x][coordinate_input_v.y]);
          return 1;
        }

      }

      else if (game_v->player == 1) {

        /* Test si la pièce à atteint les deux premiers ligne adverse */
        if (coordinate_output_v.x == 7 || coordinate_output_v.x == 8) {

          /* Application strict du règlement : Laisser le choix*/
          printf("Voulez vous promovoir la pièce ? (oui/non)\n");

          if (scanf("%19s", promotion_confirmation) != 1) {
            printf("Entrez au moins un caractere\n");
          }

          if (strcmp(promotion_confirmation, "oui") == 0) {
            promote_grant(
                &game_v->board[coordinate_input_v.y][coordinate_input_v.x]);
            printf("La pièce à été promu\n");
            return 1;
          }

          /* Application strict du règlement : Promouvoir automatiquement*/
        } else if (coordinate_output_v.x == 9) {
          printf("(Info) Votre pièce a été directement promu\n");
          promote_grant(
              &game_v->board[coordinate_input_v.x][coordinate_input_v.y]);
          return 1;
        }
      }
    }
  }
  return 0;
}

/** promote_grant
 *  Permet de promovoir la piece
 *  @params:    piece_t     -   piece
 *  @return:    void
 */
void promote_grant(piece_t *piece) {
  switch (piece->type) {
    {
    case PION:
      piece->type = PION_PROMU;
      piece->statut = PROMU;
      break;
    }
    {
    case LANCIER:
      piece->type = LANCIER_PROMU;
      piece->statut = PROMU;
      break;
    }
    {
    case CAVALIER:
      piece->type = CAVALIER_PROMU;
      piece->statut = PROMU;
      break;
    }
    {
    case FOU:
      piece->type = FOU_PROMU;
      piece->statut = PROMU;
      break;
    }
    {
    case TOUR:
      piece->type = TOUR_PROMU;
      piece->statut = PROMU;
      break;
    }
    {
    case SILVER:
      piece->type = SILVER_PROMU;
      piece->statut = PROMU;
      break;
    }
  default:
    break;
  }
}
