#include "header/mouvement.h"
#include "header/restriction.h"

#include <stdio.h>
#include <string.h>
#define MAX_CHAR 256

/********************************** INDEX *************************************/
/*    1) Bloc de validation d'entré et de sortie (valid_input et valid_output)
 *    2) Bloc de deplacement_valide et valide_win
 *    3) Bloc de deplacement_valide_($INSERT_TYPE_DE_PIECE)
 *    4) Bloc movement_valid_helper
 *    5) Bloc de is_promoted
 *    6) Bloc de deplacement_apply + annuler
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
int movement_valid_input    (game_t *g, coordinate_t c) {

  if (c.x < 11 && c.y < 11) {

    if (g->board[c.x][c.y].type != VIDE) {
      printf("Player ID %d\n", g->player);
      if (g->player == g->board[c.x][c.y].color) {
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
 * @params :    coordinate_t    -   c
 * @return :    int
 */
int movement_valid_output   (coordinate_t c) {
  if (c.x == 42 && c.y == 42)
    return 1;
  else if (c.x > 0 && c.y < 10 && c.x < 10 &&
           c.y > 0)
    return 1;
  return 0;
}

/** deplacement_valide
 *  Permet de valider les deplacement en fonctiont des coordonne de depart (pour
 * Parachutage) et appelle la fonction deplacement valide adéquate pour les
 * pieces
 *
 * @params:     game_t       - g
 *              coordinate_t - ci
 *              coordinate_t - co
 * @return:     (void)
 */
void deplacement_valide     (game_t *g, coordinate_t ci, coordinate_t co) {

  /* Si cette condition n'est pas vérifié, alors sa déselectionne la piece
   * selectionné*/

   /* Le contenue du switch_case est assez répétitif
   *  Condition : Vérifier que le déplacement est valide ET que la case
   *  d'arrivé correspond à une case SELECT
   */


  if (((ci.x != co.x || ci.y != co.y) &&
       (g->board[ci.x][ci.y].color != g->board[co.x][co.y].color)) ||
      /* En cas de parachutage impossible */
      (co.x != 42 && co.y != 42)) {

    switch (g->board[ci.x][ci.y].type) {
      {
      case PION:

        if (deplacement_valide_pion(g, ci, co) && restriction_detector(g, co)) {

          deplacement_apply(g, ci, co);
          printf("Le PION à été deplacé de (%d;%d) à (%d;%d) avec succès.\n",
                 ci.x, ci.y, co.x, co.y);
        }

        else {
          printf("Le déplacement du PION à échoué.\n");
        }

        break;
      }

      {
      case PION_PROMU:
        if (deplacement_valide_pion_promu(g, ci, co) &&
            restriction_detector(g, co)) {

          deplacement_apply(g, ci, co);

          printf(
              "Le PION_PROMU à été deplace de (%d;%d) à (%d;%d) avec succès.\n",
              ci.x, ci.y, co.x, co.y);
        }

        else {
          printf("Le déplacement du PION_PROMU à échoué\n");
        }
        break;
      }

      {
      case TOUR:

        /* Sinon ...*/

        if (deplacement_valide_tour(ci, co) && restriction_detector(g, co)) {

          deplacement_apply(g, ci, co);

          printf("La tour à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
                 ci.x, ci.y, co.x, co.y);
        }

        else {
          printf("Le deplacement de la tour à échoué.\n");
        }

        break;
      }
      {
      case TOUR_PROMU:

        if (deplacement_valide_tour_promu(ci, co) &&
            restriction_detector(g, co)) {

          deplacement_apply(g, ci, co);

          printf(
              "La TOUR_PROMU à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
              ci.x, ci.y, co.x, co.y);
        }

        else {
          printf("Le déplacement de la TOUR_PROMU à échoué.\n");
        }

        break;
      }
      {
      case CAVALIER:

        if (deplacement_valide_cavalier(g, ci, co) &&
            restriction_detector(g, co)) {

          deplacement_apply(g, ci, co);
          printf(
              "Le cavalier à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
              ci.x, ci.y, co.x, co.y);
        }

        else {
          printf("Le deplacement du cavalier à échoué.\n");
        }

        break;
      }
      {
      case CAVALIER_PROMU:

        if (deplacement_valide_cavalier_promu(g, ci, co) &&
            restriction_detector(g, co)) {

          deplacement_apply(g, ci, co);
          printf("Le CAVALIER_PROMU à été déplacé de (%d;%d) a (%d;%d) avec "
                 "succès.\n",
                 ci.x, ci.y, co.x, co.y);
        }

        else {
          printf("Le déplacement du CAVALIER_PROMU à échoué.\n");
        }

        break;
      }
      {
      case FOU:

        if (deplacement_valide_fou(ci, co) && restriction_detector(g, co)) {

          deplacement_apply(g, ci, co);

          printf("Le FOU à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
                 ci.x, ci.y, co.x, co.y);
        }

        else {
          printf("Le deplacement du FOU à échoué.\n");
        }

        break;
      }
      {
      case FOU_PROMU:

        if (deplacement_valide_fou_promu(ci, co) &&
            restriction_detector(g, co)) {

          deplacement_apply(g, ci, co);

          printf(
              "Le FOU_PROMU à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
              ci.x, ci.y, co.x, co.y);
        }

        else {
          printf("Le deplacement du FOU_PROMU à échoué.\n");
        }

        break;
      }
      {
      case GOLD:

        if (deplacement_valide_gold(g, ci, co) && restriction_detector(g, co)) {

          deplacement_apply(g, ci, co);

          printf("Le GOLD à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
                 ci.x, ci.y, co.x, co.y);
        } else {
          printf("Le déplacement du GOLD à échoué.\n");
        }

        break;
      }
      {
      case SILVER:

        if (deplacement_valide_silver(g, ci, co) &&
            restriction_detector(g, co)) {

          deplacement_apply(g, ci, co);
          printf("Le SILVER à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
                 ci.x, ci.y, co.x, co.y);
        } else {
          printf("Le déplacement du SILVER à échoué.\n");
        }

        break;
      }
      {
      case SILVER_PROMU:

        if (deplacement_valide_gold(g, ci, co) && restriction_detector(g, co)) {

          deplacement_apply(g, ci, co);

          printf("Le SILVER_PROMU à été déplacé de (%d;%d) a (%d;%d) avec "
                 "succès.\n",
                 ci.x, ci.y, co.x, co.y);
        }

        else {
          printf("Le déplacement du SILVER_PROMU à échoué.\n");
        }

        break;
      }
      {
      case ROI:

        if (deplacement_valide_roi(ci, co) && restriction_detector(g, co)) {

          deplacement_apply(g, ci, co);

          printf("Le ROI à été déplacé de (%d;%d) a (%d;%d) avec succès.\n",
                 ci.x, ci.y, co.x, co.y);
        }

        else {
          printf("Le deplacement du ROI à échoué.\n");
        }

        break;
      }
      {
      case LANCIER:

        if (deplacement_valide_lancier(g, ci, co) &&
            restriction_detector(g, co)) {

          deplacement_apply(g, ci, co);

          printf("Le LANCIER à été déplacé de (%d;%d) à (%d;%d) avec succès\n",
                 ci.x, ci.y, co.x, co.y);
        }

        else {
          printf("Le déplacement du LANCIER à échoué\n");
        }
        break;
      }
      {
      case LANCIER_PROMU:
        if (deplacement_valide_lancier_promu(g, ci, co) &&
            restriction_detector(g, co)) {

          deplacement_apply(g, ci, co);

          printf("Le LANCIER_PROMU à été déplacé de (%d;%d) à (%d;%d) avec "
                 "succès\n",
                 ci.x, ci.y, co.x, co.y);
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

  else {
    printf("Le deplacement à été annulée.\n");
  }
}

/** movement_valid_win
 * Si les coordonnées d'arrivé contient un roi, la partie se termine
 * @params:    game_t*       -   g
 *             coordinate_t  -   c
 * @return     int
 */
int movement_valid_win      (game_t *g, coordinate_t c) {

  /* Obliger de tester cette condtion pour eviter les erreurs de mémoires*/

  if (c.x == 42 && c.y == 42)
    return 1;
  if (g->player == 0) {

    if (g->board[c.x][c.y].type == ROI && g->board[c.x][c.y].color == NOIR) {
      printf("La partie est gagné par les BLANCS\n");
      return 0;
    }
  }

  if (g->player == 1) {
    if (g->board[c.x][c.y].type == ROI && g->board[c.x][c.y].color == BLANC) {
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
 * @params: game_t       -   g
 *          coordinate_t -   ci
 *          coordinate_t -   co
 * @return: int
 */
int deplacement_valide_pion             (game_t *g, coordinate_t ci, coordinate_t co) {
  int                                   movement_tmp;

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
    if (g->board[ci.x][ci.y].color == BLANC) {
      return (movement_tmp == -1) ? 1 : 0;
    }

    else if (g->board[ci.x][ci.y].color == NOIR) {
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
 * @param game_t       -   g
 *        coordinate_t -   ci
 *        coordinate_t -   co
 * @return int
 */
int deplacement_valide_tour             (coordinate_t ci, coordinate_t co) {
  return (ci.x == co.x || ci.y == co.y) ? 1 : 0;
}

/** deplacement_valide_cavalier
 * Permet de valider le déplacement du cavalier (Non promu supposé)
 * Les conditions : Seulement vers l'avant pour les blanc (resp arriere noir)
 * @params  game_t       -   g
 *          coordinate_t -   ci
 *          coordinate_t -   co
 * @return  int
 */
int deplacement_valide_cavalier         (game_t *g, coordinate_t ci, coordinate_t co) {

  /* On vérifie les conditions pour les noir */

  if (g->board[ci.x][ci.y].color == NOIR) {

    /* On vérifie les conditions x+1 et x-1 */
    if (ci.y - 1 == co.y || ci.y + 1 == co.y) {

      /* On vérifie les conditions vers l'avant (haut) soit y+2 */
      if (ci.x + 2 == co.x) {
        return 1;
      }
    }
  }

  /* On vérifie les conditions pour les blanc */

  if (g->board[ci.x][ci.y].color == BLANC) {

    /* On vérifie les conditions y+1 et y-1 */
    if (ci.y - 1 == co.y || ci.y + 1 == co.y) {

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
 * @params  game_t       -   g
 *          coordinate_t -   ci
 *          coordinate_t -   co
 * @return int
 */
int deplacement_valide_fou              (coordinate_t ci, coordinate_t co) {
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
 * @params:     game_t       - g
 *              coordinate_t - ci
 *              coordinate_t - co
 * @return      int
 */
int deplacement_valide_roi              (coordinate_t ci, coordinate_t co) {

  /* vertical checking */
  if (ci.x - 1 == co.x || ci.x + 1 == co.x || ci.x == co.x) {

    /* horizontal checking*/
    if (ci.y - 1 == co.y || ci.y + 1 == co.y || ci.y == co.y) {
      return 1;
    }
  }

  return 0;
}

/** deplacement_valide_gold
 * Permet de valider les déplacement du gold
 * Reprends le Prototype du roi, mais avec une Restrictions y-1 pour les blanc
 * et y+1 pour les noir
 * @params :  game_t       - g
 *            coordinate_t - ci
 *            coordinate_t - co
 * @return    int
 */
int deplacement_valide_gold             (game_t *g, coordinate_t ci, coordinate_t co) {
  if (piece_couleur(g->board[ci.x][ci.y]) == NOIR) {

    /* Restriction sur les diagonales en arriere */
    if (ci.x - 1 == co.x) {
      if (ci.y == co.y)
        return 1;
    }
    /* Deplacement vers l'avant */
    if (ci.x + 1 == co.x &&
        (ci.y + 1 == co.y || ci.y - 1 == co.y || ci.y == co.y)) {
      return 1;
    }
    /* Deplacement vers la gauche sur la meme ligne */
    if (ci.x == co.x && ci.y - 1 == co.y) {
      return 1;
    }
    /* Deplacement vers la droite sur la meme ligne */
    if (ci.x == co.x && ci.y + 1 == co.y) {
      return 1;
    }
  }

  if (piece_couleur(g->board[ci.x][ci.y]) == BLANC) {

    /* Restriction sur les diagonales en arriere */
    if (ci.x + 1 == co.x) {
      if (ci.y == co.y)
        return 1;
    }
    /* Deplacement vers l'avant */
    if (ci.x - 1 == co.x &&
        (ci.y + 1 == co.y || ci.y - 1 == co.y || ci.y == co.y)) {
      return 1;
    }
    /* Deplacement vers la gauche sur la meme ligne */
    if (ci.x == co.x && ci.y - 1 == co.y) {
      return 1;
    }
    /* Deplacement vers la droite sur la meme ligne */
    if (ci.x == co.x && ci.y + 1 == co.y) {
      return 1;
    }
  }

  return 0;
}

/** deplacement_valide_silver
 * Permet de valider les déplacement du silver
 * Reprends le Prototype du roi et gold, mais avec une Restrictions de pas de
 * déplacement sur x et y+1 pour les noir
 * @params :  game_t       - g
 *            coordinate_t - ci
 *            coordinate_t - co
 * @return    int
 */
int deplacement_valide_silver           (game_t *g, coordinate_t ci, coordinate_t co) {

  /* En faite c'est les noir ici */
  if (piece_couleur(g->board[ci.x][ci.y]) == NOIR) {

    /* Restrictions au déplacement ligne +1 et ses diagonales +1 */
    if (ci.x + 1 == co.x &&
        (ci.y + 1 == co.y || ci.y - 1 == co.y || ci.y == co.y)) {
      return 1;
    }

    /* Restrictions aux diagonales arriere */
    if (ci.x - 1 == co.x && (ci.y + 1 == co.y || ci.y - 1 == co.y))
      return 1;
  }

  /* En faite c'est les blanc ici */
  if (piece_couleur(g->board[ci.x][ci.y]) == BLANC) {

    /* Restrictions au déplacement ligne +1 et ses diagonales +1 */
    if (ci.x - 1 == co.x &&
        (ci.y + 1 == co.y || ci.y - 1 == co.y || ci.y == co.y)) {
      return 1;
    }

    /* Restrictions aux diagonales arriere */
    if (ci.x + 1 == co.x && (ci.y + 1 == co.y || ci.y - 1 == co.y))
      return 1;
  }

  return 0;
}

/** deplacement_valide_lancier
 *  Le lancier se deplace seulement en vertical, il ne peut pas revenir en
 * arrière
 *  @params:    game_t          -   g
 *              coordinate_t    -   ci
 *              coordinate_t    -   co
 *  @return:    int
 */
int deplacement_valide_lancier          (game_t *g, coordinate_t ci, coordinate_t co) {

  if (ci.y == co.y) {
    if ((ci.x < co.x) && piece_couleur(g->board[ci.x][ci.y]) == NOIR)
      return 1;
    else if ((ci.x > co.x) && piece_couleur(g->board[ci.x][ci.y]) == BLANC)
      return 1;
  }
  return 0;
}

/* **************** Fin des validations des déplacements   ****************** */
/* ************** Debut des validations des déplacements  PROMU ************* */

/** deplacement_valide_pion_promu
 * Algo de GOLD
 * @params :   game_t          -   g
 *             coordinate_t    -   ci
 *             coordinate_t    -   co
 * @return :   int
 */
int deplacement_valide_pion_promu       (game_t *g, coordinate_t ci, coordinate_t co) {
  return deplacement_valide_gold(g, ci, co);
}

/** deplacement_valide_tour_promu
 *  Algo de TOUR + ROI
 *  @params:        game_t          -       g
 *                  coordinate_t    -       ci
 *                  coordinate_t    -       co
 *  @return:        int
 */
int deplacement_valide_tour_promu       (coordinate_t ci, coordinate_t co) {
  return (deplacement_valide_tour(ci, co) || deplacement_valide_roi(ci, co));
}

/** deplacement_valide_cavalier_promu
 *  Algo de GOLD
 *  @params:        game_t          -       g
 *                  coordinate_t    -       ci
 *                  coordinate_t    -       co
 *  @return:        int
 */
int deplacement_valide_cavalier_promu   (game_t *g, coordinate_t ci,
                                      coordinate_t co) {
  return (deplacement_valide_gold(g, ci, co));
}

/** deplacement_valide_fou_promu
 *  Algo de FOU + ROI
 *  @params:        game_t          -       g
 *                  coordinate_t    -       ci
 *                  coordinate_t    -       co
 *  @return:        int
 */
int deplacement_valide_fou_promu        (coordinate_t ci, coordinate_t co) {
  return (deplacement_valide_fou(ci, co) || deplacement_valide_roi(ci, co));
}

/** deplacement_valide_silver_promu
 *  Algo de GOLD
 *  @params:        game_t          -       g
 *                  coordinate_t    -       ci
 *                  coordinate_t    -       co
 *  @return:        int
 */
int deplacement_valide_silver_promu     (game_t *g, coordinate_t ci,
                                    coordinate_t co) {
  return (deplacement_valide_gold(g, ci, co));
}

/** deplacement_valide_lancier_promu
 *  Le lancier se deplace seulement en vertical
 *  @params:    game_t          -   g
 *              coordinate_t    -   ci
 *              coordinate_t    -   co
 *  @return:    int
 */
int deplacement_valide_lancier_promu    (game_t *g, coordinate_t ci,
                                     coordinate_t co) {
  return deplacement_valide_gold(g, ci, co);
}
/* ************** FIN des validations des déplacements  PROMU *************** */
/* ************** FIN des validations des déplacements  ********************* */
/* ************************ movement_valid_helper *************************** */

/** movement_valid_helper
 * En fonction de la piece, renvoie si le déplacement est valide ou pas
 * Parameters:
 *     game_t       - g
 *     coordinate_t - ci
 *     coordinate_t - co
 *
 * @return int
 */
int movement_valid_helper               (game_t *g, coordinate_t ci, coordinate_t co) {
  switch (g->board[ci.x][ci.y].type) {
    {
    case PION:
      return (deplacement_valide_pion(g, ci, co)) ? 1 : 0;
      break;
    }
    {
    case PION_PROMU:
      return (deplacement_valide_pion_promu(g, ci, co)) ? 1 : 0;
      break;
    }
    /* Je ne pense pas que ce cas est nécessaire */
    {
    case TOUR:
      return (deplacement_valide_tour(ci, co)) ? 1 : 0;
      break;
    }
    {
    case TOUR_PROMU:
      return (deplacement_valide_roi(ci, co)) ? 1 : 0;
      break;
    }
    {
    case CAVALIER:

      return (deplacement_valide_cavalier(g, ci, co)) ? 1 : 0;

      break;
    }
    {
    case CAVALIER_PROMU:
      return (deplacement_valide_cavalier_promu(g, ci, co)) ? 1 : 0;
      break;
    }
    /* Je ne pense pas que ce cas est nécessaire */
    {
    case FOU:

      return (deplacement_valide_fou(ci, co)) ? 1 : 0;
      break;
    }
    {
    case FOU_PROMU:
      return (deplacement_valide_roi(ci, co)) ? 1 : 0;
      break;
    }
    {
    case GOLD:

      return (deplacement_valide_gold(g, ci, co)) ? 1 : 0;
      break;
    }
    {
    case ROI:

      return (deplacement_valide_roi(ci, co)) ? 1 : 0;
      break;
    }
    {
    case SILVER:
      return (deplacement_valide_silver(g, ci, co)) ? 1 : 0;
      break;
    }
    {
    case SILVER_PROMU:
      return (deplacement_valide_silver_promu(g, ci, co)) ? 1 : 0;
      break;
    }
    {
    case LANCIER:
      return (deplacement_valide_lancier(g, ci, co)) ? 1 : 0;
    }
    {
    case LANCIER_PROMU:
      return (deplacement_valide_lancier_promu(g, ci, co)) ? 1 : 0;
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
 *  @params:    game_t          -   g
 *              coordinate_t    -   ci
 *              coordinate_t    -   co
 *  @return:    int
 */
int is_promoted                         (game_t *g, coordinate_t ci, coordinate_t co) {
  char                                  promotion_confirmation[MAX_CHAR];

  /* On veut pas promouvoir les roi et les gold */

  if (g->board[ci.x][ci.y].type == GOLD || g->board[ci.x][ci.y].type == ROI) {
    return 0;
  }
  /* Application des règle spécifique de promotion pour le cavalier */

  else if (g->board[ci.x][ci.y].type == CAVALIER) {

    /* Pour les Blancs */

    if (g->player == 0) {
      if (co.x == 3) {
        printf("Voulez vous promovoir la piece ? (oui/non)\n");

        if (scanf("%s", promotion_confirmation) != 1) {
          printf("Entrez au moins un caractere\n");
        }

        if (strcmp(promotion_confirmation, "oui") == 0) {
          promote_grant(&g->board[ci.x][ci.y]);
          printf("La pièce à été promu.\n");
          return 1;
        }
      } else if (co.x == 2 || co.x == 1) {
        printf("(Info) Votre pièce a été directement promu\n");
        promote_grant(&g->board[ci.x][ci.y]);
        return 1;
      }
    }

    /* Pour les noir */

    else if (g->player == 1) {
      if (co.x == 7) {
        printf("Voulez vous promovoir la piece ? (oui/non)\n");

        if (scanf("%s", promotion_confirmation) != 1) {
          printf("Entrez au moins un caractere\n");
        }

        if (strcmp(promotion_confirmation, "oui") == 0) {
          promote_grant(&g->board[ci.x][ci.y]);
          printf("La pièce à été promu.\n");
          return 1;
        }
      } else if (co.x == 8 || co.x == 9) {
        printf("(Info) Votre pièce a été directement promu\n");
        promote_grant(&g->board[ci.x][ci.y]);
        return 1;
      }
    }
  }

  /* Si la piece selectionné est une piece de la reserve, on arrete la fonction
   */
  else if (((ci.x == 0 && ci.y < 11) || (ci.x == 10 && ci.y < 11))) {
    return 0;
  }

  /* Sinon : Application du cas général */
  else {
    if (g->board[ci.x][ci.y].statut == NON_PROMU) {

      /* Teste de promotion pour les Blancs*/

      if (g->player == 0) {

        /* Test si la pièce à atteint les deux premiers ligne adverse */
        if (co.x == 3 || co.x == 2) {

          /* Application strict du règlement : Laisser le choix*/
          printf("Voulez vous promovoir la piece ? (oui/non)\n");

          if (scanf("%s", promotion_confirmation) != 1) {
            printf("Entrez au moins un caractere\n");
          }

          if (strcmp(promotion_confirmation, "oui") == 0) {
            promote_grant(&g->board[ci.x][ci.y]);
            printf("La pièce à été promu.\n");
            return 1;
          }

          /* Application strict du règlement : Promouvoir automatiquement*/
        } else if (co.x == 1) {
          printf("(Info) Votre pièce a été directement promu\n");
          promote_grant(&g->board[ci.x][ci.y]);
          return 1;
        }

      }

      /*  Teste de promotion pour les noirs  */
      else if (g->player == 1) {

        /* Test si la pièce à atteint les deux premiers ligne adverse */
        if (co.x == 7 || co.x == 8) {

          /* Application strict du règlement : Laisser le choix*/
          printf("Voulez vous promovoir la pièce ? (oui/non)\n");

          if (scanf("%19s", promotion_confirmation) != 1) {
            printf("Entrez au moins un caractere\n");
          }

          if (strcmp(promotion_confirmation, "oui") == 0) {
            promote_grant(&g->board[ci.y][ci.x]);
            printf("La pièce à été promu\n");
            return 1;
          }

          /* Application strict du règlement : Promouvoir automatiquement*/
        } else if (co.x == 9) {
          printf("(Info) Votre pièce a été directement promu\n");
          promote_grant(&g->board[ci.x][ci.y]);
          return 1;
        }
      }
    }
  }
  return 0;
}
/* *********************** Debut deplacement()  ***************************** */

/** deplacement_apply()
 *  Permet d'appliquer les déplacements de pièces
 *  @param:   game_t        -   g
 *            coordinate_t  -   ci
 *            coordinate_t  -   co
 *  @return:  VOID
 */
void deplacement_apply                  (game_t *g, coordinate_t ci, coordinate_t co) {
  movement_t                            gm_tmp;
  piece_t                               p_tmp;

  gm_tmp.input = ci;
  gm_tmp.output = co;

  /* test et test_bis sont des variable servant pour les boucles while un peu
   * plus tard */

  int x, y, test = 1, test_bis = 0;

  /* On regarde si la piece qui doit être jouer peut/doit être promu ou pas*/

  int promotion_v = is_promoted(g, ci, co);

  /*------ Checking présence de piece (Si c'est le cas -> capture) -----------*/

  if (!case_vide(g->board[ci.x][ci.y])) {

    /*------------------------------------------------------------------------*/
    /* -------------------------------- Debut gestion de Reserve--------------*/
    /*------------------------------------------------------------------------*/

    if (!case_vide(g->board[co.x][co.y]) &&
        piece_couleur(g->board[co.x][co.y]) !=
            piece_couleur(g->board[ci.x][ci.y])) {

      /* TOUJOURS DANS LE IF !CASE VIDE*/

      /* On met la piece dans la liste des captures*/
      pile_stacking(g->capture, g->board[co.x][co.y]);

      /** Ici un bloc d'instruction qui met la piece capturé dans la reserve
       *  On vérifie que la case est vide pour placer la piece, sinon on passe
       *  au suivant. Si il n'y a plus de place dans l'axe des x, on passe a la
       *  deuxieme boucle le l'axe des y
       */
      p_tmp = g->board[co.x][co.y];
      if (p_tmp.statut == PROMU)
        p_tmp = demote_grant_reserve(p_tmp);
      else
        p_tmp = switch_color(p_tmp);
      /** ---------------- Noir ---------------------**/

      if (g->player == 1) {

        x = 10;

        /** Vertical checking, de la droite -> gauche **/

        while (test == 1) {
          if (case_vide(g->board[0][x]) == 1) {
            g->board[0][x] = p_tmp;
            break;
          }
          if (x > 0 && test != 0) x--;
          else if (x == 0) {
            test_bis = 1;
            break;
          }
        }

        y = 1;

        /** horizontal checking, de la Haut -> Bas **/

        while (test_bis == 1) {
          if (case_vide(g->board[y][0]) == 1) {
            g->board[y][0] = p_tmp;
            break;
          }
          if (y < 10 && test != 0) y++;
          else break;
        }
      }

      /** ---------------- Blanc ---------------------**/

      /** Blanc **/

      if (g->player == 0) {

        x = 0;
        /** vertiale checking, de la gauche -> droite **/

        while (test == 1) {
          if (case_vide(g->board[10][x]) == 1) {
            g->board[10][x] = p_tmp;
            break;
          }
          if (x < 11 && test != 0) x++;
          else if (x == 10  || x == 11) {
            test_bis = 1;
            test = 0;
            break;
          }
        }
        y = 9;

        //Counter infinite boucle
        while (test_bis == 1) {
          /** horizontal checking, de la Bas -> Haut **/
          if (case_vide(g->board[y][10]) == 1) {
            test_bis = 0;
            g->board[y][10] = p_tmp;
          }
          if (y > 0 && test_bis != 0) y--;
          else break;
        }
      }
      /* ----------------------------------------------------------------- */
      /* ------------------------ FIN GESTION DE RESERVE ----------------- */
      /* ----------------------------------------------------------------- */

      /* Initialisateur du compteur de coups */

      if (file_list_vide(g->file))
        gm_tmp.valeur = 1;
      else
        gm_tmp.valeur = g->file->taille + 1;

      /* Apply movement */

      g->board[co.x][co.y] = g->board[ci.x][ci.y];

      /* Changement en piece vide de la position de départ */
      g->board[ci.x][ci.y] = piece_creer(VIDE_PIECE, VIDE, NON_PROMU);

      /* Piece switch et ajout dans la file*/

      file_thread(g->file, gm_tmp, promotion_v, 1);
      changer_joueur(g);
    }

    /* ------------ Si il n'y a pas de présence de piece ---------------------*/
    else {

      /* Apply movement */
      g->board[co.x][co.y] = g->board[ci.x][ci.y];

      /* Changement en piece vide de la position de départ */
      g->board[ci.x][ci.y] = piece_creer(VIDE_PIECE, VIDE, NON_PROMU);

      /* Initialisateur du compteur de coups */

      if (file_list_vide(g->file))
        gm_tmp.valeur = 1;
      else
        gm_tmp.valeur = g->file->taille + 1;

      /* Piece switch et ajout dans la file*/

      file_thread(g->file, gm_tmp, promotion_v, 0);
      changer_joueur(g);
    }
  }
}
/* *********************** Fin deplacement()  ******************************* */
/* *********************** Debut annuler_deplacement() ********************** */

/** annuler_deplacement
 *  Permet d'annuler un deplacement
 *  Chemin inverse de deplacement_apply normalement
 *  @param:     game_t    -   g
 *  @return:    VOID
 */
void annuler_deplacement                (game_t *g) {
  coordinate_t                          mo_tmp;
  coordinate_t                          mi_tmp;
  piece_t                               p_r_tmp;

  file_element_t *be_tmp;

  /* Comme pour la reserve, ces deux Variables vont servir de sortir ou entrer
   * dans la boucle */
  int x, y, test = 1, test_bis = 0;

  /* Extraction du dernier coup joué de la file et initialisation */

  be_tmp = file_unthread(g->file);
  mo_tmp = be_tmp->movement.output;
  mi_tmp = be_tmp->movement.input;

  /* Verfication si le mouvement precedent à une promotion */

  if (be_tmp->promotion) {
    g->board[mo_tmp.x][mo_tmp.y] = demote_grant(g->board[mo_tmp.x][mo_tmp.y]);
  }

  /* Vérification s'il le mouvement precedent est un mouvement de capture*/

  /* Remise en place de la piece en position de départ */
  g->board[mi_tmp.x][mi_tmp.y] = g->board[mo_tmp.x][mo_tmp.y];

  /*--------------------- Verification capture -------------------------------*/
  if (be_tmp->capture == 1) {

    /* Remise en place de la piece capturé sur l'echiquier et suppression de la
     * piece capturé de la pile*/
    g->board[mo_tmp.x][mo_tmp.y] = pile_unstacking(g->capture);

    /* Création de variable de comparaison réserve */
    p_r_tmp = demote_grant_reserve(g->board[mo_tmp.x][mo_tmp.y]);

    /* --------------------Enlevement de la piece de la reserve ------------- */

    /* Si le tour actuelle est 0 (Blanc), on regarde la reserve de
     * l'adversaire*/

    if (g->player == 0) {
      y = 9;

      /** horizontal checking, de la Bas -> Haut **/

      /** On doit vérifier chaque case de la réserve pour enlever la pièce concernée **/

      while (test == 1) {

        if ((case_vide(g->board[y][0]) == 0) &&
             piece_cmp_reserve(g->board[y][0], p_r_tmp)) {
          test = 0;
          g->board[y][0] = piece_creer(VIDE_PIECE, VIDE, NON_PROMU);
        }

        if (y > 0 && test != 0) {
          y--;
        } else if (y == 0) {
          test_bis = 1;
          test = 0;
        }
      }

      /** vertiale checking, de la gauche -> droite **/

      x = 0;
      while (test_bis == 1) {
        if ((case_vide(g->board[0][x]) == 0) &&
             piece_cmp_reserve(g->board[0][x], p_r_tmp)) {
          test_bis = 0;
          g->board[0][x] = piece_creer(VIDE_PIECE, VIDE, NON_PROMU);
        }
        if (x < 11 && test_bis != 0)
          x++;
        else {
          test_bis = 0;
        }
      }
    }

    /* Si le tour actuelle est 1 (noir), on regarde la reserve de l'adversaire*/

    if (g->player == 1) {

      /** horizontal checking, de la Haut -> Bas **/

      y = 1;

      while (test == 1) {
        if ((case_vide(g->board[y][10]) == 0) &&
             piece_cmp_reserve(g->board[y][10], p_r_tmp)) {
          test = 0;
          g->board[y][10] = piece_creer(VIDE_PIECE, VIDE, NON_PROMU);
        }
        if (y < 10 && test != 0)
          y++;
        else if (y == 10) {
          test_bis = 1;
          test = 0;
        }
      }

      /** Vertical checking, de la droite -> gauche **/

      x = 10;

      while (test_bis == 1) {
        if ((case_vide(g->board[10][x]) == 0) &&
             piece_cmp_reserve(g->board[10][x], p_r_tmp)) {
          test_bis = 0;
          g->board[10][x] = piece_creer(VIDE_PIECE, VIDE, NON_PROMU);
        }
        if (x > 0 && test_bis != 0) {
          x--;
        } else {
          test_bis = 0;
        }
      }
    }
  }

  /* Si il n'y pas eu de capture de piece au tour precedent ------------------*/
  else {
    g->board[mo_tmp.x][mo_tmp.y] = piece_creer(VIDE_PIECE, VIDE, NON_PROMU);
  }

  /* Destruction du maillon et changement de joueur*/

  file_detruire_element(be_tmp);

  changer_joueur(g);
}
/* *********************** Fin annuler_deplacement() ************************ */
