#include "header/restriction.h"
#include "header/mouvement.h"
#include <stdio.h>
#include <stdlib.h>

/********************************** INDEX *************************************/
/*    1) Bloc de fonction général - movement_restriction
 *    2) Bloc de restrictions spécifiques
 *    3) movement_restriction_destruct
 *    4) Bloc de restrictions parachute (Avec pions)
 *    5) Bloc de detection de restrictions
 */

/**
 * global
 */
coordinate_t mc_tmp;

/** movement_restriction
 *  En fonction des coordonée, appele la restriction adéquate
 * @param:  game_t       - *g
 *          coordinate_t - ci
 * @return: (void)
 */
void movement_restriction           (game_t *g, coordinate_t ci) {

  /* Develement Restrictions Parachutage */
  /* Au cas ou vous avez oublié (Rapport), jsuis gentil jfais un rappel :
   * Cette condition vérifie si les coordonées d'entré font partie de la reserve
   */

  if ((ci.x == 10 && (ci.y < 11 && ci.y >= 0)) ||
      (ci.y == 10 && (ci.x < 11 && ci.x >= 0)) ||
      (ci.x == 0  && (ci.y < 11 && ci.y >=0))  ||
      (ci.y == 0  && (ci.x < 11 && ci.x >=0)))  {
    if (g->board[ci.x][ci.y].type == PION) {
      movement_restriction_pion_parachute(g);
    } else {
      movement_restriction_parachute(g);
    }
  }
  /* Fin restriction Parachutage*/

  else {
    switch (g->board[ci.x][ci.y].type) {
      {
      case PION:
        movement_restriction_general(g, ci);
        break;
      }
      {
      case TOUR:
        movement_restriction_tour(g, ci);
        break;
      }
      {
      case CAVALIER:
        movement_restriction_general(g, ci);
        break;
      }
      {
      case FOU:
        movement_restriction_fou(g, ci);
        break;
      }
      {
      case ROI:
        movement_restriction_general(g, ci);
        break;
      }
      {
      case GOLD:
        movement_restriction_general(g, ci);
        break;
      }
      {
      case SILVER:
        movement_restriction_general(g, ci);
        break;
      }
      {
      case LANCIER:
        movement_restriction_lancier(g, ci);
        break;
      }
      {
      case PION_PROMU:
        movement_restriction_general(g, ci);
        break;
      }
      {
      case TOUR_PROMU:
        movement_restriction_tour(g, ci);
        movement_restriction_general(g, ci);

        break;
      }
      {
      case CAVALIER_PROMU:
        movement_restriction_general(g, ci);
        break;
      }
      {
      case FOU_PROMU:
        movement_restriction_fou(g, ci);
        movement_restriction_general(g, ci);
        break;
      }
      {
      case SILVER_PROMU:
        movement_restriction_general(g, ci);
        break;
      }
      {
      case LANCIER_PROMU:
        movement_restriction_general(g, ci);
        break;
      }
      {
      default:
        break;
      }
    }
  }
}

/** movement_restriction_general
 * Bah, si la case du restriction est valide, on affiche l'aide visuel SELECT
 * @params:     game_t       - *g
 *              coordinate_t - ci
 * @return:     (void)
 */
void movement_restriction_general   (game_t *g, coordinate_t ci) {
  int                               x,
                                    y;

  for (x = 1; x < 10; x++) {
    mc_tmp.x = x;

    for (y = 1; y < 10; y++) {
      mc_tmp.y = y;

      if (movement_valid_helper(g, ci, mc_tmp)) {

        if (g->board[x][y].type == VIDE) {
          g->board[x][y].type = SELECT;
        }
      }
    }
  }
}

/** movement_restriction_tour
 * Bah, si la case du restriction est valide, on affiche l'aide visuel SELECT
 * La tour peut se déplacer sur sa ligne droite, gauche, haut, bas, jusqu'à qu'il y a un obstacle.
 * @params:     game_t       - *g
 *              coordinate_t - ci
 * @return:     (void)
 */
void movement_restriction_tour      (game_t *g, coordinate_t ci) {
    coordinate_t                    mc_1_tmp,
                                    mc_2_tmp,
                                    mc_3_tmp,
                                    mc_4_tmp;

  /* Boucle for, vers le bas */

  for (mc_1_tmp.x = ci.x + 1;
       mc_1_tmp.x < 10 && g->board[mc_1_tmp.x][ci.y].type == VIDE;
       mc_1_tmp.x++) {

    g->board[mc_1_tmp.x][ci.y].type = SELECT;
  }

  /* Boucle for, vers la droite */
  for (mc_2_tmp.y = ci.y + 1;
       mc_2_tmp.y < 10 && g->board[ci.x][mc_2_tmp.y].type == VIDE;
       mc_2_tmp.y++) {
    g->board[ci.x][mc_2_tmp.y].type = SELECT;
  }

  /* Boucle for vers le haut */

  for (mc_3_tmp.x = ci.x - 1;
       mc_3_tmp.x > 0 && g->board[mc_3_tmp.x][ci.y].type == VIDE;
       mc_3_tmp.x--) {

    g->board[mc_3_tmp.x][ci.y].type = SELECT;
  }

  /* Boucle for vers la gauche */

  for (mc_4_tmp.y = ci.y - 1;
       mc_4_tmp.y > 0 && g->board[ci.x][mc_4_tmp.y].type == VIDE;
       mc_4_tmp.y--) {
    g->board[ci.x][mc_4_tmp.y].type = SELECT;
  }
}

/** movement_restriction_lancier
 * Bah, si la case du restriction est valide, on affiche l'aide visuel SELECT
 * Les lanciers peuvent seulement se déplacer sur la ligne droite devant eux.
 * @params:     game_t       - *g
 *              coordinate_t - ci
 * @return:     (void)
 */
void movement_restriction_lancier   (game_t *g, coordinate_t ci) {

  /* Vers le haut, donc pour les blancs*/

  if (g->board[ci.x][ci.y].color == BLANC) {
    for (mc_tmp.x = ci.x - 1;
         mc_tmp.x > 0 && g->board[mc_tmp.x][ci.y].type == VIDE; mc_tmp.x--) {

      g->board[mc_tmp.x][ci.y].type = SELECT;
    }
  }

  /* Vers le bas, donc pour les noirs */

  else {

    for (mc_tmp.x = ci.x + 1;
         mc_tmp.x < 10 && g->board[mc_tmp.x][ci.y].type == VIDE; mc_tmp.x++) {

      g->board[mc_tmp.x][ci.y].type = SELECT;
    }
  }
}

/** movement_restriction_fou
 * movement fou restriction
 * Normalement on connait la chanson par déduction logique...
 * Sinon, Le fou peut se déplacer sur toute sa diagonal jusqu'à qu'il y a un obstacle
 * @params:*     game_t       - g
 *               coordinate_t - ci
 * @return:     (void)
 */
void movement_restriction_fou       (game_t *g, coordinate_t ci) {
  coordinate_t                      mc_1_tmp,
                                    mc_2_tmp,
                                    mc_3_tmp,
                                    mc_4_tmp;

  /* Diagnonal bas droit */
  for (mc_1_tmp.x = ci.x + 1, mc_1_tmp.y = ci.y + 1;
       mc_1_tmp.x < 10 && mc_1_tmp.y < 10 &&
       g->board[mc_1_tmp.x][mc_1_tmp.y].type == VIDE;
       mc_1_tmp.x++, mc_1_tmp.y++) {

    g->board[mc_1_tmp.x][mc_1_tmp.y].type = SELECT;
  }
  /* Diagonale haut gauche */

  for (mc_2_tmp.x = ci.x - 1, mc_2_tmp.y = ci.y - 1;
       mc_2_tmp.x > 0 && mc_2_tmp.y > 0 &&
       g->board[mc_2_tmp.x][mc_2_tmp.y].type == VIDE;
       mc_2_tmp.x--, mc_2_tmp.y--) {
    g->board[mc_2_tmp.x][mc_2_tmp.y].type = SELECT;
  }

  /* Diagonale bas gauche */
  for (mc_3_tmp.x = ci.x + 1, mc_3_tmp.y = ci.y - 1;
       mc_3_tmp.x < 10 && mc_3_tmp.y > 0 &&
       g->board[mc_3_tmp.x][mc_3_tmp.y].type == VIDE;
       mc_3_tmp.x++, mc_3_tmp.y--) {
    g->board[mc_3_tmp.x][mc_3_tmp.y].type = SELECT;
  }

  /* Diagonale haut droit */
  for (mc_4_tmp.x = ci.x - 1, mc_4_tmp.y = ci.y + 1;
       mc_4_tmp.x > 0 && mc_4_tmp.y < 10 &&
       g->board[mc_4_tmp.x][mc_4_tmp.y].type == VIDE;
       mc_4_tmp.x--, mc_4_tmp.y++) {
    g->board[mc_4_tmp.x][mc_4_tmp.y].type = SELECT;
  }
}

/** movement_restriction_destruct
 * Les cases SELECT sont remis en case VIDE
 * @params:     game_t - g
 * @return:     (void)
 */
void movement_restriction_destruct  (game_t *g) {
  int                               x,
                                    y;

  for (x = 1; x < 10; x++) {

    for (y = 1; y < 10; y++) {
      mc_tmp.x = x;
      mc_tmp.y = y;

      if (g->board[mc_tmp.x][mc_tmp.y].type == SELECT) {
        g->board[mc_tmp.x][mc_tmp.y].type = VIDE;
      }
    }
  }
}

/** movement_restriction_parachute
 * Théoriqument vu que c'est un Parachutage, toute les cases vides sont changé
 * en case SELECT
 * @param:  game_t  *   -   g
 * @return: (void)
 */
void movement_restriction_parachute (game_t *g) {
  int                               x,
                                    y;

  for (x = 1; x < 10; x++) {

    for (y = 1; y < 10; y++) {
      mc_tmp.x = x;
      mc_tmp.y = y;

      if (g->board[mc_tmp.x][mc_tmp.y].type == VIDE) {
        g->board[mc_tmp.x][mc_tmp.y].type = SELECT;
      }
    }
  }
}

/** movement_restriction_pion_parachute()
 *  Parcours chaque colonne pour voir la présence de pièce, plus de détail dans la doc
 *  @params:  game_t  -   g
 *  @return:  (void)
 */
void movement_restriction_pion_parachute    (game_t *g) {
  int                                       x,
                                            y;

  /* Booléen conditionnel pour entrer dans la troisieme boucle for*/
  int test = 1;

  /* Check les colonnes */
  for (x = 1; x < 10; x++) {
    test = 1;
    /* On parcours la colonne pour présence de pion*/

    for (y = 1; y < 10; y++) {
      if (((g->board[y][x].type == PION || g->board[y][x].type == PION_PROMU) &&
           g->player == g->board[y][x].color))
        test = 0;
    }

    /* Si on ne detecte pas de pion dans la colonne*/
    if (test == 1) {
      for (y = 1; y < 10; y++) {
        if (g->board[y][x].type == VIDE)
          g->board[y][x].type = SELECT;
      }
    }
  }
}

/** restriction_detector
 * Permet de detecter si la case selectionnée est vide ou bien d'une couleur
 * différente du joueur actuelle pour capture
 *  @params:  game_t    -       *g
 *            coordinate_t  -   ci
 *  @return:  int
 */
int restriction_detector            (game_t *g, coordinate_t ci) {
  if (g->board[ci.x][ci.y].type == SELECT ||
      (g->board[ci.x][ci.y].color != g->player &&
       g->board[ci.x][ci.y].color != VIDE_PIECE))
    return 1;
  return 0;
}

/** restriction_detector_parachute
 *  Permet de detecter si la case selectionnée est uniquement selectionn
 *  C'est pour éviter de parachuter des pièces en capturant directement les pièces
 *  adverse
 *  @params:  game_t  *     -   g
 *            coordinate_t  -   ci
 *  @return   int
 */
int restriction_detector_parachute (game_t *g, coordinate_t ci){
  return (g->board[ci.x][ci.y].type == SELECT)? 1 : 0;
}
