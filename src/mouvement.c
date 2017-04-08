#include "header/mouvement.h"
#include "header/game.h"
#include "header/piece.h"
#include "header/restriction.h"
#include <stdio.h>
#include <string.h>
#define MAX_CHAR 256

/********************************** INDEX *************************************
 */
/*   1) Bloc de validation d'entré et de sortie (valid_input et valid_output)
 *    2) Bloc de deplacement_valide et valide_win
 *    3) Bloc de deplacement_valide_($INSERT_TYPE_DE_PIECE)
 *    4) Bloc movement_valid_helper
 *    5) Bloc de is_promoted et promote_grant
 */
/************ Debut Bloc validation des entrés et sortie **********************/

/** movement_valid_input
 * Permet de valider les coordonnées d'entrés
 * Les coordonées doivent être dans l'échiquier, et doivent correspondre à une
 * case non vide et une piece du même couleur du joueur
 * @params: game_t       - g
 *          coordinate_t - c
 * @return: int
 */
int movement_valid_input(game_t * g, coordinate_t c) {
  if ((c.x > 11 || c.y > 11) ||
      g->board[c.x][c.y].type == EMPTY ||
      g->player != g->board[c.x][c.y].color) {
    printf("Vous avez saisie une case vide ou vous avez saisie la pièce de l'adversaire\n");
    return 0;
  }
  return 1;
}

/** movement_valid_input
 * Permet de valider les coordonnées d'arrivée, Vérifie si les cordoonées sont
 * dans l'échiquier au format 9x9 (Sans la reserve)
 * @params :    coordinate_t  - c
 * @return :    int
 */

int movement_valid_output(coordinate_t c) {
  return (c.x > 0 && c.y < 10 && c.x < 10 && c.y > 0) ? 1 : 0;
}

/** deplacement_valide
 *  Permet de valider les deplacement en fonctiont des coordonne de depart (pour
 * Parachutage) et appelle la fonction deplacement valide adéquate pour les
 * pieces
 *
 * @params:     game_t       - g
 *              coordinate_t - ci
 *              coordinate_t - co
 * @return:     void
 */
void            deplacement_valide(game_t * g, coordinate_t ci, coordinate_t co) {
  int           test, y;
  piece_color_e c;

  test = 0;
  c = g->board[ci.x][ci.y].color;

  /* Si cette condition n'est pas vérifié, alors sa déselectionne la piece
   * selectionné*/

  if ((ci.x == co.x && ci.y == co.y) ||
      (g->board[ci.x][ci.y].color == g->board[co.x][co.y].color)) {
    printf("Le deplacement à été annulée.\n");
    return;
  }

  switch (g->board[ci.x][ci.y].type) {
    {
    case PION:

      /* Develement des Parachutage du PION
        * Algo => Pas deuxieme pion sur la meme colonne
        */

      /* Ce gros if doit vérifier si les coordonnées d'entré sont dans la
        * reserve ou pas */
      if ((ci.x == 0 &&
            (ci.y < 11 && ci.y > -1)) ||
          (ci.y == 0 &&
            (ci.x < 11 && ci.x > -1))) {

        movement_restriction_parachute(g);
        /* Boucle for pour tester si il y a un pion dans la colonne darrivé*/
        for (y = 1; y < 10; y++) {

          if (g->board[co.y][y].type == PION &&
              g->board[co.y][y].color == c) {
            test = 1;
            printf("Erreur, Il y a déjà un pion dans la colonne d'arrivée\n");
            y = 42;
          } else {
            piece_create(EMPTY_PIECE, SELECT, NOT_PROMOTED);
          }
        }
        //        if (test == 0)

        /* Applications des restriction de selections */
        //        movement_restriction_parachute(g);

        /* Si c'est pas le cas , on applique les déplacement */
        if (test == 0 && restriction_detector(g, co)) {
          deplacement_apply(g, ci, co);
        }
        /* Fin du Develement pour l'algo de Parachutage pion */
      } else if (deplacement_valide_pion(g, ci,
                                          co) &&
                  restriction_detector(g, co)) {

        deplacement_apply(g, ci, co);
        printf("Le PION à été deplacé de (%d;%d) à (%d;%d) avec succès.\n",
                ci.x, ci.y,
                co.x, co.y);
      }

      else {
        printf("Le déplacement du PION à échoué.\n");
      }

      break;
    }

    {
    case PION_PROMU:
      if (deplacement_valide_pion_promu(g, ci,
                                        co) &&
          restriction_detector(g, co)) {

        deplacement_apply(g, ci, co);

        printf(
            "Le PION_PROMU à été deplace de (%d;%d) à (%d;%d) avec succès.\n",
            ci.x, ci.y, co.x,
            co.y);
      }

      else {
        printf("Le déplacement du PION_PROMU à échoué\n");
      }
      break;
    }

    {
    case TOUR:
      /* La Coordonée entré reserve... */
      if ((ci.x == 0 &&
            (ci.y < 11 && ci.y > -1)) ||
          (ci.y == 0 &&
            (ci.x < 11 && ci.x > -1))) {

        movement_restriction_parachute(g);
      }

      /* Sinon ...*/

      if (deplacement_valide_tour(g, ci,
                                  co) &&
          restriction_detector(g, co)) {

        deplacement_apply(g, ci, co);

        printf("La tour à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
                ci.x, ci.y,
                co.x, co.y);
      }

      else {
        printf("Le deplacement de la tour à échoué.\n");
      }

      break;
    }
    {
    case TOUR_PROMU:

      if (deplacement_valide_tour_promu(g, ci,
                                        co) &&
          restriction_detector(g, co)) {

        deplacement_apply(g, ci, co);

        printf(
            "La TOUR_PROMU à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
            ci.x, ci.y, co.x,
            co.y);
      }

      else {
        printf("Le déplacement de la TOUR_PROMU à échoué.\n");
      }

      break;
    }
    {
    case CAVALIER:
      /* Ca na pas besoin d'être commenté si vous n'etes pas amnésique */
      if ((ci.x == 0 &&
            (ci.y < 11 && ci.y > -1)) ||
          (ci.y == 0 &&
            (ci.x < 11 && ci.x > -1))) {

        movement_restriction_parachute(g);
      }

      if (deplacement_valide_cavalier(g, ci,
                                      co) &&
          restriction_detector(g, co)) {

        deplacement_apply(g, ci, co);
        printf(
            "Le cavalier à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
            ci.x, ci.y, co.x,
            co.y);
      }

      else {
        printf("Le deplacement du cavalier à échoué.\n");
      }

      break;
    }
    {
    case CAVALIER_PROMU:

      if (deplacement_valide_cavalier_promu(g, ci,
                                            co) &&
          restriction_detector(g, co)) {

        deplacement_apply(g, ci, co);
        printf("Le CAVALIER_PROMU à été déplacé de (%d;%d) a (%d;%d) avec "
                "succès.\n",
                ci.x, ci.y,
                co.x, co.y);
      }

      else {
        printf("Le déplacement du CAVALIER_PROMU à échoué.\n");
      }

      break;
    }
    {
    case FOU:

      if ((ci.x == 0 &&
            (ci.y < 11 && ci.y > -1)) ||
          (ci.y == 0 &&
            (ci.x < 11 && ci.x > -1))) {

        movement_restriction_parachute(g);
      }

      if (deplacement_valide_fou(g, ci,
                                  co) &&
          restriction_detector(g, co)) {

        deplacement_apply(g, ci, co);

        printf("Le FOU à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
                ci.x, ci.y,
                co.x, co.y);
      }

      else {
        printf("Le deplacement du FOU à échoué.\n");
      }

      break;
    }
    {
    case FOU_PROMU:

      if (deplacement_valide_fou_promu(g, ci,
                                        co) &&
          restriction_detector(g, co)) {

        deplacement_apply(g, ci, co);

        printf(
            "Le FOU_PROMU à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
            ci.x, ci.y, co.x,
            co.y);
      }

      else {
        printf("Le deplacement du FOU_PROMU à échoué.\n");
      }

      break;
    }
    {
    case GOLD:

      if ((ci.x == 0 &&
            (ci.y < 11 && ci.y > -1)) ||
          (ci.y == 0 &&
            (ci.x < 11 && ci.x > -1))) {
        movement_restriction_parachute(g);
      }

      if (deplacement_valide_gold(g, ci,
                                  co) &&
          restriction_detector(g, co)) {

        deplacement_apply(g, ci, co);

        printf("Le GOLD à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
                ci.x, ci.y,
                co.x, co.y);
      } else {
        printf("Le déplacement du GOLD à échoué.\n");
      }

      break;
    }
    {
    case SILVER:

      if ((ci.x == 0 &&
            (ci.y < 11 && ci.y > -1)) ||
          (ci.y == 0 &&
            (ci.x < 11 && ci.x > -1))) {

        movement_restriction_parachute(g);
      }

      if (deplacement_valide_silver(g, ci,
                                    co) &&
          restriction_detector(g, co)) {

        deplacement_apply(g, ci, co);
        printf("Le SILVER à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
                ci.x, ci.y,
                co.x, co.y);
      } else {
        printf("Le déplacement du SILVER à échoué.\n");
      }

      break;
    }
    {
    case SILVER_PROMU:

      if (deplacement_valide_gold(g, ci,
                                  co) &&
          restriction_detector(g, co)) {

        deplacement_apply(g, ci, co);

        printf("Le SILVER_PROMU à été déplacé de (%d;%d) a (%d;%d) avec "
                "succès.\n",
                ci.x, ci.y,
                co.x, co.y);
      }

      else {
        printf("Le déplacement du SILVER_PROMU à échoué.\n");
      }

      break;
    }
    {
    case ROI:

      if (deplacement_valide_roi(g, ci,
                                  co) &&
          restriction_detector(g, co)) {

        deplacement_apply(g, ci, co);

        printf("Le ROI à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
                ci.x, ci.y,
                co.x, co.y);
      }

      else {
        printf("Le deplacement du ROI à échoué.\n");
      }

      break;
    }
    {
    case LANCIER:

      if ((ci.x == 0 &&
            (ci.y < 11 && ci.y > -1)) ||
          (ci.y == 0 &&
            (ci.x < 11 && ci.x > -1))) {

        movement_restriction_parachute(g);
      }

      if (deplacement_valide_lancier(g, ci,
                                      co) &&
          restriction_detector(g, co)) {

        deplacement_apply(g, ci, co);

        printf("Le LANCIER à été déplacé de (%d;%d) à (%d;%d) avec succès\n",
                ci.x, ci.y,
                co.x, co.y);
      }

      else {
        printf("Le déplacement du LANCIER à échoué\n");
      }
      break;
    }
    {
    case LANCIER_PROMU:
      if (deplacement_valide_lancier_promu(g, ci,
                                            co) &&
          restriction_detector(g, co)) {

        deplacement_apply(g, ci, co);

        printf("Le LANCIER_PROMU à été déplacé de (%d;%d) à (%d;%d) avec "
                "succès\n",
                ci.x, ci.y,
                co.x, co.y);
      }

      else {
        printf("Le déplacement du LANCIER_PROMU à échoué\n");
      }
    }
    {
    default:
      break;
    }
  }
}

/** movement_valid_win
 * Si les coordonnées d'arrivé contient un roi, la partie se termine
 * @params:    game_t*       -   game_v
 *             coordinate_t  -   coordinate_v
 * @return     int
 */
int movement_valid_win(game_t *game_v, coordinate_t coordinate_v) {
  if (game_v->player == 0) {

    if (game_v->board[coordinate_v.x][coordinate_v.y].type == ROI) {
      printf("La partie est gagné par les BLANCS\n");
      return 0;
    }
  }

  else if (game_v->player == 1) {
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
 *          coordinate_t -   ci
 *          coordinate_t -   co
 * @return: int
 */
int deplacement_valide_pion(game_t *game_v, coordinate_t ci,
                            coordinate_t co) {
  int movement_tmp;

  /* Initialisation par calcul de différence */
  movement_tmp = co.x - ci.x;

  /* Condition vertical, les coordonées d'entré et de sortie doivent être le
   * même */
  if (ci.y == co.y) {

    /* On vérifie la couleur, Si c'est noir et que la différence est -1 ->
     * Déplacement autorisé
     * Si c'est blanc, meme chose mais la différence est 1
     * Sinon 0
     */
    if (game_v->board[ci.x][ci.y].color ==
        BLANC) {
      return (movement_tmp == -1) ? 1 : 0;
    }

    else if (game_v->board[ci.x][ci.y].color ==
             NOIR) {
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
 *        coordinate_t -   ci
 *        coordinate_t -   co
 * @return int
 */
int deplacement_valide_tour(game_t *game_v, coordinate_t ci,
                            coordinate_t co) {
  return (ci.x == co.x ||
          ci.y == co.y)
             ? 1
             : 0;
}

/** deplacement_valide_cavalier
 * Permet de valider le déplacement du cavalier (Non promu supposé)
 * Les conditions : Seulement vers l'avant pour les blanc (resp arriere noir)
 * @params  game_t       -   game_v
 *          coordinate_t -   ci
 *          coordinate_t -   co
 * @return  int
 */
int deplacement_valide_cavalier(game_t *game_v, coordinate_t ci,
                                coordinate_t co) {

  /* On vérifie les conditions pour les noir */

  if (game_v->board[ci.x][ci.y].color == NOIR) {

    /* On vérifie les conditions x+1 et x-1 */
    if (ci.y - 1 == co.y ||
        ci.y + 1 == co.y) {

      /* On vérifie les conditions vers l'avant (haut) soit y+2 */
      if (ci.x + 2 == co.x) {
        return 1;
      }
    }
  }

  /* On vérifie les conditions pour les blanc */

  if (game_v->board[ci.x][ci.y].color ==
      BLANC) {

    /* On vérifie les conditions y+1 et y-1 */
    if (ci.y - 1 == co.y ||
        ci.y + 1 == co.y) {

      /* On vérifie les conditions vers l'arriere (bas) soit x-2 */
      if (ci.x - 2 == co.x) {
        return 1;
      }
    }
  }

  /* Valeur par défaut */

  return 0;
}

/** deplacement_valide_fou
 * Permet de valider le déplacement du fou (Non promu supposé)
 * Les conditions : La différence ou la somme des deux coordonées entré sortie
 * doivent être égales
 * @params  game_t       -   game_v
 *          coordinate_t -   ci
 *          coordinate_t -   co
 * @return int
 */
int deplacement_valide_fou(game_t *game_v, coordinate_t ci,
                           coordinate_t co) {
  int movement_1_tmp;
  int movement_2_tmp;
  int movement_1_bis_tmp;
  int movement_2_bis_tmp;

  /* Initialize */

  /* Addition */
  movement_1_tmp = (co.x + co.y);
  movement_2_tmp = (ci.x + ci.y);

  /* Différence */
  movement_1_bis_tmp = (ci.x - ci.y);
  movement_2_bis_tmp = (co.x - co.y);

  /* On regarde si l'un des deux sont égales */
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
 *              coordinate_t - ci
 *              coordinate_t - co
 * @return      int
 */
int deplacement_valide_roi(game_t *game_v, coordinate_t ci,
                           coordinate_t co) {

  /* vertical checking */
  if (ci.x - 1 == co.x ||
      ci.x + 1 == co.x ||
      ci.x == co.x) {

    /* horizontal checking*/
    if (ci.y - 1 == co.y ||
        ci.y + 1 == co.y ||
        ci.y == co.y) {
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
 *            coordinate_t - ci
 *            coordinate_t - co
 * @return    int
 */
int deplacement_valide_gold(game_t *game_v, coordinate_t ci,
                            coordinate_t co) {
  if (piece_color(
          game_v->board[ci.x][ci.y]) == NOIR) {

    /* Restriction sur les diagonales en arriere */
    if (ci.x - 1 == co.x) {
      if (ci.y == co.y)
        return 1;
    }
    /* Deplacement vers l'avant */
    if (ci.x + 1 == co.x &&
        (ci.y + 1 == co.y ||
         ci.y - 1 == co.y ||
         ci.y == co.y)) {
      return 1;
    }
    /* Deplacement vers la gauche sur la meme ligne */
    if (ci.x == co.x &&
        ci.y - 1 == co.y) {
      return 1;
    }
    /* Deplacement vers la droite sur la meme ligne */
    if (ci.x == co.x &&
        ci.y + 1 == co.y) {
      return 1;
    }
  }

  if (piece_color(
          game_v->board[ci.x][ci.y]) == BLANC) {

    /* Restriction sur les diagonales en arriere */
    if (ci.x + 1 == co.x) {
      if (ci.y == co.y)
        return 1;
    }
    /* Deplacement vers l'avant */
    if (ci.x - 1 == co.x &&
        (ci.y + 1 == co.y ||
         ci.y - 1 == co.y ||
         ci.y == co.y)) {
      return 1;
    }
    /* Deplacement vers la gauche sur la meme ligne */
    if (ci.x == co.x &&
        ci.y - 1 == co.y) {
      return 1;
    }
    /* Deplacement vers la droite sur la meme ligne */
    if (ci.x == co.x &&
        ci.y + 1 == co.y) {
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
 *            coordinate_t - ci
 *            coordinate_t - co
 * @return    int
 */
int deplacement_valide_silver(game_t *game_v, coordinate_t ci,
                              coordinate_t co) {

  /* En faite c'est les noir ici */
  if (piece_color(
          game_v->board[ci.x][ci.y]) == NOIR) {

    /* Restrictions au déplacement ligne +1 et ses diagonales +1 */
    if (ci.x + 1 == co.x &&
        (ci.y + 1 == co.y ||
         ci.y - 1 == co.y ||
         ci.y == co.y)) {
      return 1;
    }

    /* Restrictions aux diagonales arriere */
    if (ci.x - 1 == co.x &&
        (ci.y + 1 == co.y ||
         ci.y - 1 == co.y))
      return 1;
  }

  /* En faite c'est les blanc ici */
  if (piece_color(
          game_v->board[ci.x][ci.y]) == BLANC) {

    /* Restrictions au déplacement ligne +1 et ses diagonales +1 */
    if (ci.x - 1 == co.x &&
        (ci.y + 1 == co.y ||
         ci.y - 1 == co.y ||
         ci.y == co.y)) {
      return 1;
    }

    /* Restrictions aux diagonales arriere */
    if (ci.x + 1 == co.x &&
        (ci.y + 1 == co.y ||
         ci.y - 1 == co.y))
      return 1;
  }

  return 0;
}

/** deplacement_valide_lancier
 *  Le lancier se deplace seulement en vertical, il ne peut pas revenir en
 * arrière
 *  @params:    game_t          -   game_v
 *              coordinate_t    -   ci
 *              coordinate_t    -   co
 *  @return:    int
 */
int deplacement_valide_lancier(game_t *game_v, coordinate_t ci,
                               coordinate_t co) {

  if (ci.y == co.y) {
    if ((ci.x < co.x) &&
        piece_color(
            game_v->board[ci.x][ci.y]) == NOIR)
      return 1;
    else if ((ci.x > co.x) &&
             piece_color(
                 game_v->board[ci.x][ci.y]) ==
                 BLANC)
      return 1;
  }
  return 0;
}

/****************** Fin des validations des déplacements   ******************/
/**************** Debut des validations des déplacements  PROMOTED *************/

/** deplacement_valide_pion_promu
 * Algo de GOLD
 * @params :   game_t          -   game_v
 *             coordinate_t    -   ci
 *             coordinate_t    -   co
 * @return :   int
 */
int deplacement_valide_pion_promu(game_t *game_v,
                                  coordinate_t ci,
                                  coordinate_t co) {
  return deplacement_valide_gold(game_v, ci,
                                 co);
}

/** deplacement_valide_tour_promu
 *  Algo de TOUR + ROI
 *  @params:        game_t          -       game_v
 *                  coordinate_t    -       ci
 *                  coordinate_t    -       co
 *  @return:        int
 */
int deplacement_valide_tour_promu(game_t *game_v,
                                  coordinate_t ci,
                                  coordinate_t co) {
  return (
      deplacement_valide_tour(game_v, ci,
                              co) ||
      deplacement_valide_roi(game_v, ci, co));
}

/** deplacement_valide_cavalier_promu
 *  Algo de GOLD
 *  @params:        game_t          -       game_v
 *                  coordinate_t    -       ci
 *                  coordinate_t    -       co
 *  @return:        int
 */
int deplacement_valide_cavalier_promu(game_t *game_v,
                                      coordinate_t ci,
                                      coordinate_t co) {
  return (
      deplacement_valide_gold(game_v, ci, co));
}

/** deplacement_valide_fou_promu
 *  Algo de FOU + ROI
 *  @params:        game_t          -       game_v
 *                  coordinate_t    -       ci
 *                  coordinate_t    -       co
 *  @return:        int
 */
int deplacement_valide_fou_promu(game_t *game_v,
                                 coordinate_t ci,
                                 coordinate_t co) {
  return (
      deplacement_valide_fou(game_v, ci, co) ||
      deplacement_valide_roi(game_v, ci, co));
}

/** deplacement_valide_silver_promu
 *  Algo de GOLD
 *  @params:        game_t          -       game_v
 *                  coordinate_t    -       ci
 *                  coordinate_t    -       co
 *  @return:        int
 */
int deplacement_valide_silver_promu(game_t *game_v,
                                    coordinate_t ci,
                                    coordinate_t co) {
  return (
      deplacement_valide_gold(game_v, ci, co));
}

/** deplacement_valide_lancier_promu
 *  Le lancier se deplace seulement en vertical
 *  @params:    game_t          -   game_v
 *              coordinate_t    -   ci
 *              coordinate_t    -   co
 *  @return:    int
 */
int deplacement_valide_lancier_promu(game_t *game_v,
                                     coordinate_t ci,
                                     coordinate_t co) {
  return deplacement_valide_gold(game_v, ci,
                                 co);
}
/**************** FIN des validations des déplacements  PROMOTED
 * ****************/

/** movement_valid_helper
 * En fonction de la piece, renvoie si le déplacement est valide ou pas
 * Parameters:
 *     game_t       - game_v
 *     coordinate_t - ci
 *     coordinate_t - co
 *
 * @return int
 */
int movement_valid_helper(game_t *game_v, coordinate_t ci,
                          coordinate_t co) {
  //======================================================================
  // Main
  //======================================================================
  switch (game_v->board[ci.x][ci.y].type) {
    {
    case PION:
      return (deplacement_valide_pion(game_v, ci,
                                      co))
                 ? 1
                 : 0;
      break;
    }
    {
    case PION_PROMU:
      return (deplacement_valide_pion_promu(game_v, ci,
                                            co))
                 ? 1
                 : 0;
      break;
    }
    {
    case TOUR:
      return (deplacement_valide_tour(game_v, ci,
                                      co))
                 ? 1
                 : 0;
      break;
    }
    {
    case TOUR_PROMU:
      return (deplacement_valide_tour_promu(game_v, ci,
                                            co))
                 ? 1
                 : 0;
      break;
    }
    {
    case CAVALIER:

      return (deplacement_valide_cavalier(game_v, ci,
                                          co))
                 ? 1
                 : 0;

      break;
    }
    {
    case CAVALIER_PROMU:
      return (deplacement_valide_cavalier_promu(game_v, ci,
                                                co))
                 ? 1
                 : 0;
      break;
    }
    {
    case FOU:

      return (deplacement_valide_fou(game_v, ci,
                                     co))
                 ? 1
                 : 0;
      break;
    }
    {
    case FOU_PROMU:
      return (deplacement_valide_fou_promu(game_v, ci,
                                           co))
                 ? 1
                 : 0;
      break;
    }
    {
    case GOLD:

      return (deplacement_valide_gold(game_v, ci,
                                      co))
                 ? 1
                 : 0;
      break;
    }
    {
    case ROI:

      return (deplacement_valide_roi(game_v, ci,
                                     co))
                 ? 1
                 : 0;
      break;
    }
    {
    case SILVER:
      return (deplacement_valide_silver(game_v, ci,
                                        co))
                 ? 1
                 : 0;
      break;
    }
    {
    case SILVER_PROMU:
      return (deplacement_valide_silver_promu(game_v, ci,
                                              co))
                 ? 1
                 : 0;
      break;
    }
    {
    case LANCIER:
      return (deplacement_valide_lancier(game_v, ci,
                                         co))
                 ? 1
                 : 0;
    }
    {
    case LANCIER_PROMU:
      return (deplacement_valide_lancier_promu(game_v, ci,
                                               co))
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
 *  d'être promu, renvoie un int pour determiner si la piece à été promu ou non
 *  pour la file.
 *  @params:    game_t          -   game_v
 *              coordinate_t    -   ci
 *              coordinate_t    -   co
 *  @return:    int
 */
int is_promoted(game_t *game_v, coordinate_t ci,
                coordinate_t co) {

  char promotion_confirmation[MAX_CHAR];

  /* On veut pas promouvoir les roi et les gold */

  if (game_v->board[ci.x][ci.y].type == GOLD ||
      game_v->board[ci.x][ci.y].type == ROI) {
    return 0;
  }
  /* Application des règle spécifique de promotion pour le cavalier */

  else if (game_v->board[ci.x][ci.y].type ==
           CAVALIER) {

    /* Pour les Blancs */

    if (game_v->player == 0) {
      if (co.x == 3) {
        printf("Voulez vous promovoir la piece ? (oui/non)\n");

        if (scanf("%s", promotion_confirmation) != 1) {
          printf("Entrez au moins un caractere\n");
        }

        if (strcmp(promotion_confirmation, "oui") == 0) {
          promote_grant(
              &game_v->board[ci.x][ci.y]);
          printf("La pièce à été promu.\n");
          return 1;
        }
      } else if (co.x == 2 || co.x == 1) {
        printf("(Info) Votre pièce a été directement promu\n");
        promote_grant(
            &game_v->board[ci.x][ci.y]);
        return 1;
      }
    }

    /* Pour les noir */

    else if (game_v->player == 1) {
      if (co.x == 7) {
        printf("Voulez vous promovoir la piece ? (oui/non)\n");

        if (scanf("%s", promotion_confirmation) != 1) {
          printf("Entrez au moins un caractere\n");
        }

        if (strcmp(promotion_confirmation, "oui") == 0) {
          promote_grant(
              &game_v->board[ci.x][ci.y]);
          printf("La pièce à été promu.\n");
          return 1;
        }
      } else if (co.x == 8 || co.x == 9) {
        printf("(Info) Votre pièce a été directement promu\n");
        promote_grant(
            &game_v->board[ci.x][ci.y]);
        return 1;
      }
    }
  }

  /* Si la piece selectionné est une piece de la reserve, on arrete la fonction
   */
  else if (((ci.x == 0 && ci.y < 11) ||
            (ci.x == 10 && ci.y < 11))) {
    return 0;
  }

  /* Sinon : Application du cas général */
  else {
    if (game_v->board[ci.x][ci.y].statut ==
        NOT_PROMOTED) {

      /* Teste de promotion pour les Blancs*/

      if (game_v->player == 0) {

        /* Test si la pièce à atteint les deux premiers ligne adverse */
        if (co.x == 3 || co.x == 2) {

          /* Application strict du règlement : Laisser le choix*/
          printf("Voulez vous promovoir la piece ? (oui/non)\n");

          if (scanf("%s", promotion_confirmation) != 1) {
            printf("Entrez au moins un caractere\n");
          }

          if (strcmp(promotion_confirmation, "oui") == 0) {
            promote_grant(
                &game_v->board[ci.x][ci.y]);
            printf("La pièce à été promu.\n");
            return 1;
          }

          /* Application strict du règlement : Promouvoir automatiquement*/
        } else if (co.x == 1) {
          printf("(Info) Votre pièce a été directement promu\n");
          promote_grant(
              &game_v->board[ci.x][ci.y]);
          return 1;
        }

      }

      /*  Teste de promotion pour les noirs  */
      else if (game_v->player == 1) {

        /* Test si la pièce à atteint les deux premiers ligne adverse */
        if (co.x == 7 || co.x == 8) {

          /* Application strict du règlement : Laisser le choix*/
          printf("Voulez vous promovoir la pièce ? (oui/non)\n");

          if (scanf("%19s", promotion_confirmation) != 1) {
            printf("Entrez au moins un caractere\n");
          }

          if (strcmp(promotion_confirmation, "oui") == 0) {
            promote_grant(
                &game_v->board[ci.y][ci.x]);
            printf("La pièce à été promu\n");
            return 1;
          }

          /* Application strict du règlement : Promouvoir automatiquement*/
        } else if (co.x == 9) {
          printf("(Info) Votre pièce a été directement promu\n");
          promote_grant(
              &game_v->board[ci.x][ci.y]);
          return 1;
        }
      }
    }
  }
  return 0;
}

/** promote_grant
 *  Permet de promovoir la piece
 *  @params:    piece_t - p
 *  @return:    void
 */
void promote_grant(piece_t * p) {
  switch (p->type) {
    case PION:
      p->type = PION_PROMU;
      p->statut = PROMOTED;
      break;
    case LANCIER:
      p->type = LANCIER_PROMU;
      p->statut = PROMOTED;
      break;
    case CAVALIER:
      p->type = CAVALIER_PROMU;
      p->statut = PROMOTED;
      break;
    case FOU:
      p->type = FOU_PROMU;
      p->statut = PROMOTED;
      break;
    case TOUR:
      p->type = TOUR_PROMU;
      p->statut = PROMOTED;
      break;
    case SILVER:
      p->type = SILVER_PROMU;
      p->statut = PROMOTED;
      break;
    default:
      break;
  }
}
