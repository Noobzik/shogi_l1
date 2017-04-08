#include "header/game.h"
#include "header/debug.h"
#include "header/file.h"
#include "header/mouvement.h"
#include "header/piece.h"
#include "header/pile.h"
#include "header/restriction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256

/*--------------------------------INDEX--------------------------------------*/
/* 1) Afficher_echiquier
 * 2) partie_creer
 * 3) partie_detruire
 * 4) partie_nouvelle
 * 5) bloc de gestion de case
 * 6)
 */
/** Info
 *  BLANC = 0
 *  NOIR  = 1
 */

/* Variable globale (Limite du code C, pas d'argument optionnel)*/
coordinate_t COORDINATE_NULL = {42, 42};

/*---------------------------------------------------------------------------*/
/*------------------- BLOC afficher_echiquier -------------------------------*/
/*---------------------------------------------------------------------------*/

/** Afficher_echiquier
 * Description :
 * La premiere boucle for permet l'espacement et d'afficher le tour actuelle du
 * joueur La deuxieme boucle for affiche le contenue de chaque case de
 * l'échiquier
 * Parameters :
 * @param : game_t      - game_v
 *          coordinate_t
 * @return : VOID
 */
void afficher_echiquier(game_t *game_v, coordinate_t game_input_tmp) {

  /* Variables de boucles pour les coordonnes*/
  int x, y;

  /* Les cases de l'aide visuel sont enlevés */
  movement_restriction_destruct(game_v);

  /* Affichage par imprimante */
  printf("\n");
  printf("           x->     y  0  1  2  3  4  5  6  7  8  9  10\n");
  printf("                      _________________________________\n");

  for (x = 0; x < 11; x++) {
    if ((x < 6 && x > 3) || ((x == 0) || x == 10)) {
      if (x == 10)
        printf("                  %d  ", x);
      else
        printf("                   %d  ", x);
    } else if (x < 6) {
      /* Player Indicator */
      if (game_v->player == 1) {
        printf("  NOIR->           %d  ", x);
      } else {
        printf("                   %d  ", x);
      }

    } else if (x > 1) {
      /** Player Indicator : BLANC
       *  Premier if = hack pour pas afficher blanc a la 6eme ligne
       */
      if (game_v->player == 0 && x > 6) {
        printf("  BLANC->          %d  ", x);
      } else
        printf("                   %d  ", x);
    }

    /* Application de l'aide visuel */

    if (game_input_tmp.x != 42 || game_input_tmp.y != 42) {
      movement_restriction(game_v, game_input_tmp);
    }

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
  return res = malloc(sizeof(game_t));
}

/** partie_detruire
 * Détruit tout simplement l'echiquier
 */
void partie_detruire(game_t *game_v) { free(game_v); }

/** partie_nouvelle
 * Description: Initialize tout les case en piece EMPTY
 * Puis Place tout les pieces de begin de partie
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
  res->capture = pile_create();
  res->file = file_create_list();

  /** Info
   *  BLANC = 0
   *  NOIR  = 1
   */

  res->player = 0;

  /* Remplissage case vide */
  for (x = 0; x < 11; x++) {

    for (y = 0; y < 11; y++) {
      res->board[y][x] = piece_create(EMPTY_PIECE, EMPTY, NOT_PROMOTED);
      res->board[y][x] = piece_create(EMPTY_PIECE, EMPTY, NOT_PROMOTED);
    }
  }

  /* Pions */
  for (x = 1; x < 10; x++) {
    res->board[7][x] = piece_create(BLANC, PION, NOT_PROMOTED);
    res->board[3][x] = piece_create(NOIR, PION, NOT_PROMOTED);
  }

  /* Tour */

  res->board[8][2] = piece_create(BLANC, TOUR, NOT_PROMOTED);
  res->board[2][8] = piece_create(NOIR, TOUR, NOT_PROMOTED);

  /* Roi */

  res->board[9][5] = piece_create(BLANC, ROI, NOT_PROMOTED);
  res->board[1][5] = piece_create(NOIR, ROI, NOT_PROMOTED);

  /* Fou */

  res->board[8][8] = piece_create(BLANC, FOU, NOT_PROMOTED);
  res->board[2][2] = piece_create(NOIR, FOU, NOT_PROMOTED);

  /* Gold */

  res->board[1][4] = piece_create(NOIR, GOLD, NOT_PROMOTED);
  res->board[1][6] = piece_create(NOIR, GOLD, NOT_PROMOTED);
  res->board[9][4] = piece_create(BLANC, GOLD, NOT_PROMOTED);
  res->board[9][6] = piece_create(BLANC, GOLD, NOT_PROMOTED);

  /* Sivler */

  res->board[9][3] = piece_create(BLANC, SILVER, NOT_PROMOTED);
  res->board[9][7] = piece_create(BLANC, SILVER, NOT_PROMOTED);

  res->board[1][3] = piece_create(NOIR, SILVER, NOT_PROMOTED);
  res->board[1][7] = piece_create(NOIR, SILVER, NOT_PROMOTED);

  /* Cavalier */

  res->board[1][2] = piece_create(NOIR, CAVALIER, NOT_PROMOTED);
  res->board[1][8] = piece_create(NOIR, CAVALIER, NOT_PROMOTED);
  res->board[9][2] = piece_create(BLANC, CAVALIER, NOT_PROMOTED);
  res->board[9][8] = piece_create(BLANC, CAVALIER, NOT_PROMOTED);

  /* Lancier */

  res->board[1][1] = piece_create(NOIR, LANCIER, NOT_PROMOTED);
  res->board[1][9] = piece_create(NOIR, LANCIER, NOT_PROMOTED);
  res->board[9][1] = piece_create(BLANC, LANCIER, NOT_PROMOTED);
  res->board[9][9] = piece_create(BLANC, LANCIER, NOT_PROMOTED);

  return res;
}

/*----------------------------------------------------------------------------*/
/*---------------------------BLOC DE GESTION DE CASE--------------------------*/
/*----------------------------------------------------------------------------*/
/** Case vide
 * Permet de savoir si la case est vide ou pas
 * @param piece_t piece_v
 * @return int
 */
int case_vide(piece_t piece_v) {
  if (piece_v.type == EMPTY) {
    return 1;
  } else if (piece_v.type == SELECT)
    return 1;
  return 0;
}

/** Modifier case
 *  Permet de modifier le contenue de la case
 *  @param game_t *game_v
 *         piece_t piece_v
 *         coordinate_t coordonate_v
 *  @return RIEN
 */
void modifier_case(game_t *game_v, piece_t piece_v, coordinate_t coordinate_v) {
  piece_t res = piece_create(piece_v.color, piece_v.type, piece_v.statut);
  game_v->board[coordinate_v.x][coordinate_v.y] = res;
}

/** Changer joueur
 * Permet de changer le tour actuelle du joueur
 * @param game_t *game_v
 */
/** Info
 *  BLANC = 0
 *  NOIR  = 1
 */
void changer_joueur(game_t *game_v) {
  (game_v->player == 0) ? (game_v->player = 1) : (game_v->player = 0);
}
/*----------------------------------------------------------------------------*/
/*---------------------- FIN BLOC DE GESTION DE CASE--------------------------*/
/*----------------------------------------------------------------------------*/
/*-----------------------  deplacement()  ------------------------------------*/
/*----------------------------------------------------------------------------*/
void deplacement_apply(game_t *game_v, coordinate_t coordinate_input_v,
                       coordinate_t coordinate_output_v) {

  movement_t game_movement_tmp;

  game_movement_tmp.input = coordinate_input_v;
  game_movement_tmp.output = coordinate_output_v;

  /* test et test_bis sont des variable servant pour les boucles while un peu
   * plus tard */

  int x, y, test = 1, test_bis = 0;

  /* On regarde si la piece qui doit être jouer peut/doit être promu ou pas*/

  int promotion_v =
      is_promoted(game_v, coordinate_input_v, coordinate_output_v);

  /*------ Checking présence de piece (Si c'est le cas -> capture) -----------*/

  if (!case_vide(game_v->board[coordinate_input_v.x][coordinate_input_v.y])) {

    /*------------------------------------------------------------------------*/
    /* -------------------------------- Debut gestion de Reserve--------------*/
    /*------------------------------------------------------------------------*/

    if (!case_vide(
            game_v->board[coordinate_output_v.x][coordinate_output_v.y]) &&
        piece_couleur(
            game_v->board[coordinate_output_v.x][coordinate_output_v.y]) !=
            piece_couleur(
                game_v->board[coordinate_input_v.x][coordinate_input_v.y])) {

      /* TOUJOURS DANS LE IF !CASE EMPTY*/

      /* On met la piece dans la liste des captures*/
      pile_stacking(
          game_v->capture,
          game_v->board[coordinate_output_v.x][coordinate_output_v.y]);

      /** Ici un bloc d'instruction qui met la piece capturé dans la reserve
       *  On vérifie que la case est vide pour placer la piece, sinon on passe
       *  au next. Si il n'y a plus de place dans l'axe des x, on passe a la
       *  deuxieme boucle le l'axe des y
       */

      /** ---------------- Noir ---------------------**/

      if (game_v->player == 1) {

        x = 10;

        /** Vertical checking, de la droite -> gauche **/

        while (test == 1) {
          if (case_vide(game_v->board[0][x]) == 1) {
            test = 0;
            game_v->board[0][x] = piece_create(
                NOIR,
                game_v->board[coordinate_output_v.x][coordinate_output_v.y]
                    .type,
                game_v->board[coordinate_output_v.x][coordinate_output_v.y]
                    .statut);
          }
          if (x > 0 && test != 0) {
            x--;
          } else if (x == 0) {
            test_bis = 1;
          }
        }

        y = 1;

        /** horizontal checking, de la Haut -> Bas **/

        while (test_bis == 1) {
          if (case_vide(game_v->board[y][0]) == 1) {
            test_bis = 0;
            game_v->board[y][0] = piece_create(
                NOIR,
                game_v->board[coordinate_output_v.x][coordinate_output_v.y]
                    .type,
                game_v->board[coordinate_output_v.x][coordinate_output_v.y]
                    .statut);
          }
          if (y < 10 && test != 0) {
            y++;
          }
        }
      }

      /** ---------------- Noir ---------------------**/

      /** Blanc **/

      if (game_v->player == 0) {

        x = 0;

        /** vertiale checking, de la gauche -> droite **/

        while (test == 1) {
          if (case_vide(game_v->board[10][x]) == 1) {
            test = 0;
            game_v->board[10][x] = piece_create(
                BLANC,
                game_v->board[coordinate_output_v.x][coordinate_output_v.y]
                    .type,
                game_v->board[coordinate_output_v.x][coordinate_output_v.y]
                    .statut);
          }
          if (x < 11 && test != 0) {
            x++;
          } else if (x == 10) {
            test_bis = 1;
          }
        }
        y = 10;

        while (test_bis == 1) {

          /** horizontal checking, de la Bas -> Haut **/

          if (case_vide(game_v->board[y][10]) == 1) {
            test_bis = 0;

            game_v->board[y][0] = piece_create(
                BLANC,
                game_v->board[coordinate_output_v.x][coordinate_output_v.y]
                    .type,
                game_v->board[coordinate_output_v.x][coordinate_output_v.y]
                    .statut);
          }
          if (y > 0 && test_bis != 0) {
            y--;
          }
        }
      }
      /* ----------------------------------------------------------------- */
      /* ------------------------ FIN GESTION DE RESERVE ----------------- */
      /* ----------------------------------------------------------------- */

      /* Initialisateur du compteur de coups */

      if (file_empty_list(game_v->file))
        game_movement_tmp.valeur = 1;
      else
        game_movement_tmp.valeur = game_v->file->size + 1;

      /* Apply movement */

      game_v->board[coordinate_output_v.x][coordinate_output_v.y] =
          game_v->board[coordinate_input_v.x][coordinate_input_v.y];

      /* Changement en piece vide de la position de départ */
      game_v->board[coordinate_input_v.x][coordinate_input_v.y] =
          piece_create(EMPTY_PIECE, EMPTY, NOT_PROMOTED);

      /* Piece switch et ajout dans la file*/

      file_thread(game_v->file, game_movement_tmp, promotion_v, 1);
      changer_joueur(game_v);
    }

    /* ------------ Si il n'y a pas de présence de piece ---------------------*/
    else {

      /* Apply movement */
      game_v->board[coordinate_output_v.x][coordinate_output_v.y] =
          game_v->board[coordinate_input_v.x][coordinate_input_v.y];

      /* Changement en piece vide de la position de départ */
      game_v->board[coordinate_input_v.x][coordinate_input_v.y] =
          piece_create(EMPTY_PIECE, EMPTY, NOT_PROMOTED);

      /* Initialisateur du compteur de coups */

      if (file_empty_list(game_v->file))
        game_movement_tmp.valeur = 1;
      else
        game_movement_tmp.valeur = game_v->file->size + 1;

      /* Piece switch et ajout dans la file*/

      file_thread(game_v->file, game_movement_tmp, promotion_v, 0);
      changer_joueur(game_v);
    }
  }
}
/*----------------------------------------------------------------------------*/
/*-------------------- FIN deplacement()  ------------------------------------*/
/*----------------------------------------------------------------------------*/
/*-------------------- annuler_deplacement  ----------------------------------*/
/*----------------------------------------------------------------------------*/

/** annuler_deplacement
 *  Permet d'annuler un deplacement
 *  @param:     game_t    -   game_v
 *  @return:    VOID
 */

void annuler_deplacement(game_t *game_v) {

  /* Variables */
  coordinate_t movement_output_tmp;
  coordinate_t movement_input_tmp;

  file_element_t *back_element_tmp;

  /* Comme pour la reserve, ces deux Variables vont servir de sortir ou entrer
   * dans la boucle */
  int x, y, test = 1, test_bis = 0;

  /* Extraction du dernier coup joué de la file et initialisation */

  back_element_tmp = file_unthread(game_v->file);
  movement_output_tmp = back_element_tmp->movement.output;
  movement_input_tmp = back_element_tmp->movement.input;

  /* Vérification s'il le mouvement precedent est un mouvement de capture*/

  /* Remise en place de la piece en position de départ */
  game_v->board[movement_input_tmp.x][movement_input_tmp.y] =
      game_v->board[movement_output_tmp.x][movement_output_tmp.y];

  /*--------------------- Verification capture -------------------------------*/
  if (back_element_tmp->capture == 1) {

    /* Remise en place de la piece capturé sur l'echiquier et suppression de la
     * piece capturé de la pile*/
    game_v->board[movement_output_tmp.x][movement_output_tmp.y] =
        pile_unstacking(game_v->capture);

    /* --------------------Enlevement de la piece de la reserve ------------- */

    /* Si le tour actuelle est 0 (Blanc), on regarde la reserve de
     * l'adversaire*/

    if (game_v->player == 0) {
      y = 9;

      /** horizontal checking, de la Bas -> Haut **/

      while (test == 1) {

        if (case_vide(game_v->board[y][0]) == 0) {
          test = 0;
          game_v->board[y][0] = piece_create(EMPTY_PIECE, EMPTY, NOT_PROMOTED);
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

        if (case_vide(game_v->board[0][x]) == 0) {
          test_bis = 0;
          game_v->board[0][x] = piece_create(EMPTY_PIECE, EMPTY, NOT_PROMOTED);
        }
        if (x < 11 && test_bis != 0)
          x++;
        else {
          test_bis = 0;
        }
      }
    }

    /* Si le tour actuelle est 1 (noir), on regarde la reserve de l'adversaire*/

    if (game_v->player == 1) {

      /** horizontal checking, de la Haut -> Bas **/

      y = 1;

      while (test == 1) {
        printf("Je suis rentré dans cette boucle %d\n", y);
        if (case_vide(game_v->board[y][10]) == 0) {
          test = 0;
          game_v->board[y][10] = piece_create(EMPTY_PIECE, EMPTY, NOT_PROMOTED);
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
        if (case_vide(game_v->board[10][x]) == 0) {
          test_bis = 0;
          game_v->board[10][x] = piece_create(EMPTY_PIECE, EMPTY, NOT_PROMOTED);
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
    game_v->board[movement_output_tmp.x][movement_output_tmp.y] =
        piece_create(EMPTY_PIECE, EMPTY, NOT_PROMOTED);
  }

  /* Destruction du maillon et changement de joueur*/

  file_destruct_element(back_element_tmp);

  changer_joueur(game_v);
}
/** saisie_case
 *  Permet de saisir les coordonnées d'une case
 *  Cette fonction est un substitut du scanf
 *  Complexite : Temps O(p) Espace  O(1)
 *  Parameters :
 *  @param EMPTY
 *  @return coordinate_t
 */
coordinate_t saisie_case() {

  coordinate_t res;
  char *p;
  char s[100];

  printf("x: ");

  while (fgets(s, sizeof(s), stdin)) {
    res.y = strtol(s, &p, 10);

    if (p == s || *p != '\n') {
      printf("x: ");
    } else {
      break;
    }
  }

  printf("y: ");
  /* Le fgets marche comme un scanf*/
  while (fgets(s, sizeof(s), stdin)) {
    res.x = strtol(s, &p, 10);
    if (p == s || *p != '\n') {
      printf("y: ");
    } else {
      break;
    }
  }

  if (res.x > 0 && res.x < 11) {
    if (res.y > 0 && res.y < 11) {
      return res;
    }
  }
  return res;
}

/** game_seperator
 * Espace tout simplement
 */
void game_seperator() {
  //======================================================================
  // Main
  //======================================================================
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
         "\n\n\n\n\n\n");
}
/*----------------------------------------------------------------------------*/
/**
 * game buffer
 */
void game_buffer() {

  char empty_buffer;

  do
    empty_buffer = getchar();
  while (empty_buffer != '\n' && empty_buffer != EOF);
}

/** game_exit
 * game exit
 * Il a vraiment besoin de commentaire lui ?
 * @param:    game_t    -   game_v
 * @return:   int
 */
int game_exit(game_t *game_v) {

  file_destruct_list(game_v->file);
  pile_destuct(game_v->capture);
  partie_detruire(game_v);

  return 0;
}

/** game_selector
 * Cette fonction compare la commande entré à la commande assosicé *
 * @params:   char - game_command
 *            char - select_v
 * @return int
 */
int game_selector(char game_command[MAX_CHAR], char select_v[MAX_CHAR]) {
  if (strcmp(game_command, select_v) == 0) {
    return 1;
  } else {
    return 0;
  }
}

/*---------------------------------------------------------------------------*/
/*-------------------------partie_jouer()------------------------------------*/
/*---------------------------------------------------------------------------*/

/** partie_jouer()
 * Description : voir commentaire au fur et à mesure...
 * @params: game_t    -   game_v
 * @return: void
 */
void partie_jouer(game_t *game_v) {

  char game_command[MAX_CHAR] = "";
  char *game_save_name = malloc(MAX_CHAR);
  char *game_save_path = malloc(MAX_CHAR);
  char game_exit_confirmation[MAX_CHAR];

  coordinate_t game_input_tmp, game_output_tmp;

  /* Game setting */
  int game_command_dev = 0;
  int game_play = 1;

  /* First chess board display*/

  printf("IM A GENIUUUUUUUUUUUUUUUUUUUUUUUUUS (Luis Suarez)");
  game_seperator();
  printf("Nouvelle partie.\n");

  /* Enter loop */
  afficher_echiquier(game_v, COORDINATE_NULL);
  printf("\n\n\n");

  /* Main loop */
  while (game_play) {

    /* Command input */
    printf("Entrez une commande: ");

    if (scanf("%19s", game_command) != 1) {

      /* Separator */
      game_seperator();

      printf("Entrer au moins un caractere.\n");

      /* Enter loop */
      afficher_echiquier(game_v, COORDINATE_NULL);
      printf("\n\n\n");
    }

    game_buffer();

    /** Help command
     *  Permet d'afficher la liste des éventuels commandes disponible
     */
    if (game_selector(game_command, "help")) {

      /* Separator */
      game_seperator();

      /** Advanced commands
       *   Si les commands de developpeur sont activées
       */
      if (game_command_dev) {
        printf("PASS                  Passe le tour du joueur.\n");
        printf("FILE                  Affiche les donnes contenu dans la "
               "file.\n");
        printf("PILE                  Affiche les donnes contenu dans la "
               "pile.\n");
        printf("CELL                  Inspecter une cellule.\n");
      }

      else {
        printf("DEV                   Pour activer les command developpeur.\n");
      }
      printf("\n");

      /* Classic command */
      printf("SURREND               Declarer forfait.\n");
      printf(
          "MOVE                  Selectionner le deplacement d'une piece.\n");
      printf("BACK                  Restaurer le deplacement precedent.\n");
      printf("SAVE                  Sauvegarder la partie.\n");
      printf("EXIT                  Quitter le jeu.\n");

      /* Enter loop */
      afficher_echiquier(game_v, COORDINATE_NULL);
      printf("\n\n\n");

      /** Developper command
       *  Permet d'activer les commandes de developpeur ou de les désactiver
       */
    } else if (game_selector(game_command, "dev")) {

      /* Separator */
      game_seperator();

      if (game_command_dev == 0) {
        printf("Les commandes developpeur sont active,\nSaisissez 'help' pour "
               "en savoir plus sur les commandes.\n");
        game_command_dev = 1;
      } else {
        printf("Les commandes developpeur ont été désactivé.\n");
        game_command_dev = 0;
      }

      /* Enter loop */
      afficher_echiquier(game_v, COORDINATE_NULL);
      printf("\n\n\n");

      /* Developper command pass le tour*/
    } else if (game_selector(game_command, "pass") && game_command_dev) {

      /* Separator */
      game_seperator();

      changer_joueur(game_v);

      /* Enter loop */
      afficher_echiquier(game_v, COORDINATE_NULL);
      printf("\n\n\n");

      /* Developper command file */
    } else if (game_selector(game_command, "file") && game_command_dev) {

      /* Separator */
      game_seperator();

      debug_file(game_v);

      /* Enter loop */
      afficher_echiquier(game_v, COORDINATE_NULL);
      printf("\n\n\n");

      /* Developper command pile */
    } else if (game_selector(game_command, "pile") && game_command_dev) {

      /* Separator */
      game_seperator();

      debug_pile(game_v);

      /* Enter loop */
      afficher_echiquier(game_v, COORDINATE_NULL);
      printf("\n\n\n");

      /* Developper command clear */
    } else if (game_selector(game_command, "cell") && game_command_dev) {

      /* Input */
      /* Separator */
      game_seperator();
      printf("Saisir les coordonnees d'une piece:\n");

      /* Enter loop */
      afficher_echiquier(game_v, COORDINATE_NULL);
      printf("\n\n\n");
      game_input_tmp = saisie_case();

      /* Separator */
      game_seperator();

      debug_cell(game_v, game_input_tmp);

      /* Enter loop */
      afficher_echiquier(game_v, COORDINATE_NULL);
      printf("\n\n\n");

      /* Surrend command */
    } else if (game_selector(game_command, "surrend")) {

      /* Separator */
      game_seperator();

      changer_joueur(game_v);
      printf("Le joueur ");

      if (game_v->player == 0) {
        printf("Blanc");
      } else if (game_v->player == 1) {
        printf("Noir");
      }

      printf(" a gagner la partie par abandon.\n");

      /* Exit loop */
      afficher_echiquier(game_v, COORDINATE_NULL);
      game_play = 0;

      /* Move command */
    } else if (game_selector(game_command, "move")) {

      /* Input : Tant que les coordonées d'entrée ne sont pas correcte, on reste
       * dans la boucle*/
      do {
        /* Separator */
        game_seperator();
        printf("Saisir les coordonnées d'une piece:\n");

        /* Enter loop */
        afficher_echiquier(game_v, COORDINATE_NULL);
        printf("\n\n\n");
        game_input_tmp = saisie_case();
      } while (!movement_valid_input(game_v, game_input_tmp));

      printf("\n");

      /* Output : Logiquement c'est le meme commentaire d'avant...*/
      do {
        /* Separator */
        game_seperator();
        printf("Vous avez selectionner la piece '");
        piece_afficher(game_v->board[game_input_tmp.x][game_input_tmp.y]);
        printf("' de coordonnees (%d;%d) du joueur ", game_input_tmp.x,
               game_input_tmp.y);
        printf("%d.", game_v->board[game_input_tmp.x][game_input_tmp.y].color);
        printf("\nSaisir les coordonnees du movement:\n");

        /* Enter loop */
        afficher_echiquier(game_v, game_input_tmp);
        printf("\n\n\n");
        game_output_tmp = saisie_case();
      } while (!movement_valid_output(game_output_tmp));

      /* Separator */

      game_seperator();

      /* On fait ou ne fait pas les deplacements...*/
      deplacement_valide(game_v, game_input_tmp, game_output_tmp);

      /* On regarde si il y a un roi qui s'est fait victimisé */
      game_play = movement_valid_win(game_v, game_output_tmp);

      /* Enter loop */
      afficher_echiquier(game_v, COORDINATE_NULL);
      printf("\n\n\n");

      /* Back command */
    } else if (game_selector(game_command, "back")) {

      /* Separator */
      game_seperator();

      if (!file_empty_list(game_v->file)) {
        annuler_deplacement(game_v);
        printf("L'annulation à été éffectué.\n");

      } else {
        printf(
            "L'annulation à échoué.(Peut être aucun mouvement dans la file)\n");
      }

      /* Enter loop */
      afficher_echiquier(game_v, COORDINATE_NULL);
      printf("\n\n\n");

      /* Save command */
    } else if (game_selector(game_command, "exit")) {

      /* Separator */
      game_seperator();

      printf("Quitter.\n");

      /* Enter loop */
      afficher_echiquier(game_v, COORDINATE_NULL);
      printf("\n\n");
      printf("Etes vous sur de quitter sans sauvegarder? (oui/non)\n");

      if (scanf("%19s", game_exit_confirmation) != 1) {
        /* Separator */
        game_seperator();

        printf("Entrer au moins un caractere.\n");

        /* Enter loop */
        afficher_echiquier(game_v, COORDINATE_NULL);
        printf("\n\n\n");
      }

      if (strcmp(game_exit_confirmation, "oui") == 0) {

        /* Separator */
        game_seperator();
        printf("Merci d'avoir jouer a ce jeu.\n");

        /* Exit loop */
        free(game_save_name);
        free(game_save_path);

        game_play = game_exit(game_v);
      } else {
        /* Separator */
        game_seperator();

        printf("Sauvegarde.\n");

        /* Enter loop */
        afficher_echiquier(game_v, COORDINATE_NULL);
        printf("\n\n\n");

        printf("Entrer le nom de la partie:");
        fgets(game_save_name, MAX_CHAR, stdin);

        /* Separator */
        game_seperator();

        /* Enter loop */
        afficher_echiquier(game_v, COORDINATE_NULL);
        printf("\n\n\n");

        printf("Entrer l'emplacement de la sauvegarder:");

        fgets(game_save_path, MAX_CHAR, stdin);

        /* Separator */
        game_seperator();

        printf("La partie a ete sauvergardé.");

        //        partie_sauvegarder(game_v, game_save_name, game_save_path);

        /* Enter loop */
        afficher_echiquier(game_v, COORDINATE_NULL);

        game_play = game_exit(game_v);
        free(game_save_name);
        free(game_save_path);
      }

      /* Unknown command : Quand vous savez pas écrire des commandes, il y a ce
       * message*/
    }

    else {

      /* Separator */
      game_seperator();

      printf("'%s' n'est pas reconnu comme une commande,\nsaisissez 'help' "
             "pour en savoir plus sur les commandes.\n",
             game_command);

      /* Enter loop */
      afficher_echiquier(game_v, COORDINATE_NULL);
      printf("\n\n\n");
    }
  }
}
