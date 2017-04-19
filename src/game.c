#include "header/debug.h"
#include "header/mouvement.h"
#include "header/restriction.h"
#include "header/sauvegardes.h"

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
 * 6) game_exit
 * 7) game_selector
 * 8) partie_jouer
 --------------------------------INDEX--------------------------------------*/

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
 * @param :     game_t          -   g
 *              coordinate_t    -   g_i
 * @return :    (void)
 */
void afficher_echiquier     (game_t *g, coordinate_t g_i) {
  int                       x,
                            y;

  /* Les cases de l'aide visuel sont enlevés */
  movement_restriction_destruct(g);

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
      if (g->player == 1) {
        printf("  NOIR->           %d  ", x);
      } else {
        printf("                   %d  ", x);
      }

    } else if (x > 1) {
      /** Player Indicator : BLANC
       *  Premier if = hack pour pas afficher blanc a la 6eme ligne
       */
      if (g->player == 0 && x > 6) {
        printf("  BLANC->          %d  ", x);
      } else
        printf("                   %d  ", x);
    }

    /* Application de l'aide visuel */

    if (g_i.x != 42 || g_i.y != 42) {
      movement_restriction(g, g_i);
    }

    /* Echiquier */
    for (y = 0; y < 11; y++) {
      piece_afficher(g->board[x][y]);
      printf("  ");
    }

    printf("\n");
  }
}

/** partie_creer()
 * Description :
 * Permet de retourner un echiquier initialisé
 * @params: (void)
 * @return: (void)
 */
game_t *partie_creer        () {
  game_t *                  res;
  return res = malloc(sizeof(game_t));
}

/** partie_detruire()
 * Détruit tout simplement l'echiquier
 * @params: (void)
 * @return: game_t
 */
void partie_detruire        (game_t *g) {
    free(g);
}

/** partie_nouvelle
 * Description: Initialize tout les case en piece VIDE
 * Puis Place tout les pieces de debut de partie
 * @params: (void)
 * @return: game_t
 */
game_t *partie_nouvelle     () {
  int                       x,
                            y;
  game_t *                  res;

  /* Initialize */
  res = partie_creer();
  res->capture = pile_create();
  res->file = file_creer_list();

  /** Info
   *  BLANC = 0
   *  NOIR  = 1
   */

  res->player = 0;

  /* Remplissage case vide */
  for (x = 0; x < 11; x++) {

    for (y = 0; y < 11; y++) {
      res->board[y][x] = piece_creer(VIDE_PIECE, VIDE, NON_PROMU);
      res->board[y][x] = piece_creer(VIDE_PIECE, VIDE, NON_PROMU);
    }
  }

  /* Pions */
  for (x = 1; x < 10; x++) {
    res->board[7][x] = piece_creer(BLANC, PION, NON_PROMU);
    res->board[3][x] = piece_creer(NOIR, PION, NON_PROMU);
  }

  /* Tour */

  res->board[8][2] = piece_creer(BLANC, TOUR, NON_PROMU);
  res->board[2][8] = piece_creer(NOIR, TOUR, NON_PROMU);

  /* Roi */

  res->board[9][5] = piece_creer(BLANC, ROI, NON_PROMU);
  res->board[1][5] = piece_creer(NOIR, ROI, NON_PROMU);

  /* Fou */

  res->board[8][8] = piece_creer(BLANC, FOU, NON_PROMU);
  res->board[2][2] = piece_creer(NOIR, FOU, NON_PROMU);

  /* Gold */

  res->board[1][4] = piece_creer(NOIR, GOLD, NON_PROMU);
  res->board[1][6] = piece_creer(NOIR, GOLD, NON_PROMU);
  res->board[9][4] = piece_creer(BLANC, GOLD, NON_PROMU);
  res->board[9][6] = piece_creer(BLANC, GOLD, NON_PROMU);

  /* Sivler */

  res->board[9][3] = piece_creer(BLANC, SILVER, NON_PROMU);
  res->board[9][7] = piece_creer(BLANC, SILVER, NON_PROMU);

  res->board[1][3] = piece_creer(NOIR, SILVER, NON_PROMU);
  res->board[1][7] = piece_creer(NOIR, SILVER, NON_PROMU);

  /* Cavalier */

  res->board[1][2] = piece_creer(NOIR, CAVALIER, NON_PROMU);
  res->board[1][8] = piece_creer(NOIR, CAVALIER, NON_PROMU);
  res->board[9][2] = piece_creer(BLANC, CAVALIER, NON_PROMU);
  res->board[9][8] = piece_creer(BLANC, CAVALIER, NON_PROMU);

  /* Lancier */

  res->board[1][1] = piece_creer(NOIR, LANCIER, NON_PROMU);
  res->board[1][9] = piece_creer(NOIR, LANCIER, NON_PROMU);
  res->board[9][1] = piece_creer(BLANC, LANCIER, NON_PROMU);
  res->board[9][9] = piece_creer(BLANC, LANCIER, NON_PROMU);

  return res;
}

/*---------------------------BLOC DE GESTION DE CASE--------------------------*/

/** Case vide
 * Permet de savoir si la case est vide ou pas, Une case vide est caractisé par VIDE et SELECT
 * @params: piece_t   -    p
 * @return: int
 */
int case_vide               (piece_t p) {
  if (p.type == VIDE) {
    return 1;
  } else if (p.type == SELECT)
    return 1;
  return 0;
}

/** Modifier case
 *  Permet de modifier le contenue de la case
 *  @param game_t *g
 *         piece_t p
 *         coordinate_t coordonate_v
 *  @return (void)
 */
void modifier_case          (game_t *g, piece_t p, coordinate_t c) {
  piece_t res = piece_creer(p.color, p.type, p.statut);
  g->board[c.x][c.y] = res;
}

/** Changer joueur
 * Permet de changer le tour actuelle du joueur
 * @param   game_t *g
 * @return: (void)
 */
/** Info
 *  BLANC = 0
 *  NOIR  = 1
 */
void changer_joueur         (game_t *g) {
  (g->player == 0) ? (g->player = 1) : (g->player = 0);
}

/** saisie_case
 *  Permet de saisir les coordonnées d'une case
 *  Cette fonction est un substitut du scanf, la façon dont elle est écrite n'accepte que les chiffres.
 *  Complexite : Temps O(p) Espace  O(1)
 *  @param VIDE
 *  @return coordinate_t
 */
coordinate_t saisie_case    () {

  coordinate_t res;
  char *p;
  char s[100];

  printf("x: ");

  while (fgets(s, sizeof(s), stdin)) {
    res.y = (int)strtol(s, &p, 10);

    if (p == s || *p != '\n') {
      printf("x: ");
    } else {
      break;
    }
  }

  printf("y: ");
  /* Le fgets marche comme un scanf*/
  while (fgets(s, sizeof(s), stdin)) {
    res.x = (int)strtol(s, &p, 10);
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
/*---------------------------FIN DE GESTION DE CASE---------------------------*/

/** game_seperator
 * Espace tout simplement
 *  @param:     (void)
 *  @return:    (void)
 */
void game_seperator         () {
  //======================================================================
  // Main
  //======================================================================
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
         "\n\n\n\n\n\n");
}
/*----------------------------------------------------------------------------*/

/** game_exit
 * game exit
 * Il a vraiment besoin d'être commenté lui ?
 * Faut vraiment le faire pour ne pas comprendre
 * @param:    game_t    -   g
 * @return:   int
 */
int game_exit               (game_t *g) {

  file_detruire_list(g->file);
  pile_detruire(g->capture);
  partie_detruire(g);

  return 0;
}

/** game_selector
 * Cette fonction compare la commande entré à la commande assosicé
 * (Comparaison de deux chaine de caractères)
 * @params:   char - game_command
 *            char - select_v
 * @return    int
 */
int game_selector           (char *game_command, const char *select_v) {
  if (strcmp(game_command, select_v) == 0) {
    return 1;
  } else {
    return 0;
  }
}

/*-------------------------partie_jouer()------------------------------------*/

/** partie_jouer()
 * Description : voir commentaire au fur et à mesure...
 * @params: game_t    -   g
 * @return: void
 */
void partie_jouer           (game_t *g) {
  char                      game_command[MAX_CHAR] = "";
  char                      game_save_name[MAX_CHAR] = "";
  char                      game_exit_confirmation[MAX_CHAR];
  coordinate_t              g_i, g_o;

  /* Game setting */
  int game_command_dev = 0;
  int game_play = 1;

  /* Premier affichage de l'échiquier*/

  printf("IM A GENIUUUUUUUUUUUUUUUUUUUUUUUUUS");
  game_seperator();
  printf("Nouvelle partie.\n");

  /* Enter loop */
  afficher_echiquier(g, COORDINATE_NULL);
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
      afficher_echiquier(g, COORDINATE_NULL);
      printf("\n\n\n");
    }

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
      printf("MOVE                  Selectionner le deplacement d'une piece.\n");
      printf("BACK                  Restaurer le deplacement precedent.\n");
      printf("SAVE                  Sauvegarder la partie.\n");
      printf("EXIT                  Quitter le jeu.\n");
      printf("42,42                 Pour désélectionner une pièce,(Seulement quand on demande des coordonées)\n");

      /* Enter loop */
      afficher_echiquier(g, COORDINATE_NULL);
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
      afficher_echiquier(g, COORDINATE_NULL);
      printf("\n\n\n");

      /* Developper command pass le tour*/
    } else if (game_selector(game_command, "pass") && game_command_dev) {

      /* Separator */
      game_seperator();

      changer_joueur(g);

      /* Enter loop */
      afficher_echiquier(g, COORDINATE_NULL);
      printf("\n\n\n");

      /* Developper command file, affiche le contenu de la file */
    } else if (game_selector(game_command, "file") && game_command_dev) {

      /* Separator */
      game_seperator();

      debug_file(g);

      /* Enter loop */
      afficher_echiquier(g, COORDINATE_NULL);
      printf("\n\n\n");

      /* Developper command pile, affiche le contenu de la pile */
    } else if (game_selector(game_command, "pile") && game_command_dev) {

      /* Separator */
      game_seperator();

      debug_pile(g);

      /* Enter loop */
      afficher_echiquier(g, COORDINATE_NULL);
      printf("\n\n\n");

      /* Developper command cell, permet d'inspecter les données de la case */
    } else if (game_selector(game_command, "cell") && game_command_dev) {

      /* Input */
      /* Separator */
      game_seperator();
      printf("Saisir les coordonnees d'une piece:\n");

      /* Enter loop */
      afficher_echiquier(g, COORDINATE_NULL);
      printf("\n\n\n");
      g_i = saisie_case();

      /* Separator */
      game_seperator();

      debug_cell(g, g_i);

      /* Enter loop */
      afficher_echiquier(g, COORDINATE_NULL);
      printf("\n\n\n");

      /* Surrend command */
    } else if (game_selector(game_command, "surrend")) {

      /* Separator */
      game_seperator();

      changer_joueur(g);
      printf("Le joueur ");

      if (g->player == 0) {
        printf("Blanc");
      } else if (g->player == 1) {
        printf("Noir");
      }

      printf(" a gagner la partie par abandon.\n");

      /* Exit loop */
      afficher_echiquier(g, COORDINATE_NULL);
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
        afficher_echiquier(g, COORDINATE_NULL);
        printf("\n\n\n");
        g_i = saisie_case();
      } while (!movement_valid_input(g, g_i));

      printf("\n");

      /* Output : Logiquement c'est le meme commentaire d'avant...*/
      do {
        /* Separator */
        game_seperator();
        printf("Vous avez selectionner la piece '");
        piece_afficher(g->board[g_i.x][g_i.y]);
        printf("' de coordonnees (%d;%d) du joueur ", g_i.x, g_i.y);
        printf("%d.", g->board[g_i.x][g_i.y].color);
        printf("\n\nSi vous voulez parachuter un pion et qu'il n'y a pas "
               "d'étoile, "
               "saisissez 42, 42\n");
        printf("\nSaisir les coordonnees du movement:\n");

        /* Enter loop */
        afficher_echiquier(g, g_i);
        printf("\n\n\n");
        g_o = saisie_case();
      } while (!movement_valid_output(g_o));

      /* Separator */

      game_seperator();

      game_play = movement_valid_win(g, g_o);

      /* On fait ou ne fait pas les deplacements...*/
      deplacement_valide(g, g_i, g_o);

      if (game_play == 0) {

        afficher_echiquier(g, COORDINATE_NULL);
        printf("\n\n\n");
        printf(
            "Fin de partie.\nVoulez-vous sauvegarder la partie? (oui/non)\n");

        if (scanf("%19s", game_exit_confirmation) != 1) {
          /* Separator */
          game_seperator();

          printf("Entrer au moins un caractere.\n");

          /* Enter loop */
          afficher_echiquier(g, COORDINATE_NULL);
          printf("\n\n\n");
        }

        if (strcmp(game_exit_confirmation, "non") == 0) {

          /* Separator */
          game_seperator();
          printf("Merci d'avoir jouer a ce jeu.\n");
        } else {
          printf("Entrer le nom de la partie: ");

          // Hack pour warning: ignoring return value of 'scanf'
          // On rappel que un scanf revoie un entier !
          // fgets(game_save_name, MAX_CHAR, stdin);

          if (scanf("%s", game_save_name) != 1) {

            /* Separator */
            game_seperator();

            printf("Entrer au moins un caractere.\n");

            /* Enter loop */
            afficher_echiquier(g, COORDINATE_NULL);
            printf("\n\n\n");
          }

          strtok(game_save_name, "\n");

          /* Separator */
          game_seperator();

          partie_sauvegarder(g, game_save_name);

          printf("La partie a ete sauvergarder.\n");
          printf("Merci d'avoir joué à ce jeu\n\n\n");
        }
      }

      /* On regarde si il y a un roi qui s'est fait victimisé */

      /* Enter loop */
      afficher_echiquier(g, COORDINATE_NULL);
      printf("\n\n\n");

      /* Back command */
    } else if (game_selector(game_command, "back")) {

      /* Separator */
      game_seperator();

      if (!file_list_vide(g->file)) {
        annuler_deplacement(g);
        printf("L'annulation à été éffectué.\n");

      } else {
        printf(
            "L'annulation à échoué.(Peut être aucun mouvement dans la file)\n");
      }

      /* Enter loop */
      afficher_echiquier(g, COORDINATE_NULL);
      printf("\n\n\n");

    }
    /* Save command */

    else if (game_selector(game_command, "save")) {
      /* Separator */
      game_seperator();

      printf("Sauvegarde.\n");

      /* Enter loop */
      afficher_echiquier(g, COORDINATE_NULL);
      printf("\n\n\n");

      printf("Entrer le nom de la partie: ");

      //  scanf("%s", game_save_name);
      // Hack pour warning: ignoring return value of 'scanf'

      // fgets(game_save_name, MAX_CHAR, stdin);

      if (scanf("%s", game_save_name) != 1) {

        /* Separator */
        game_seperator();

        printf("Entrer au moins un caractere.\n");

        /* Enter loop */
        afficher_echiquier(g, COORDINATE_NULL);
        printf("\n\n\n");
      }

      strtok(game_save_name, "\n");

      /* Separator */
      game_seperator();

      partie_sauvegarder(g, game_save_name);

      printf("La partie a ete sauvergarder.\n");

      /* Exit loop */
      afficher_echiquier(g, COORDINATE_NULL);
      printf("\n\n\n");

      /* Exit command */
    } else if (game_selector(game_command, "exit")) {

      /* Separator */
      game_seperator();

      printf("Quitter.\n");

      /* Enter loop */
      afficher_echiquier(g, COORDINATE_NULL);
      printf("\n\n");
      printf("Etes vous sur de quitter sans sauvegarder? (oui/non)\n");

      if (scanf("%19s", game_exit_confirmation) != 1) {
        /* Separator */
        game_seperator();

        printf("Entrer au moins un caractere.\n");

        /* Enter loop */
        afficher_echiquier(g, COORDINATE_NULL);
        printf("\n\n\n");
      }

      if (strcmp(game_exit_confirmation, "oui") == 0) {

        /* Separator */
        game_seperator();
        printf("Merci d'avoir jouer a ce jeu.\n");

        /* Exit loop */
        //  free(game_save_name);

        game_play = game_exit(g);
      } else {
        /* Separator */
        game_seperator();

        printf("Sauvegarde.\n");

        /* Enter loop */
        afficher_echiquier(g, COORDINATE_NULL);
        printf("\n\n\n");

        printf("Entrer le nom de la partie:");

        if (scanf("%s", game_save_name) != 1) {

          /* Separator */
          game_seperator();

          printf("Entrer au moins un caractere.\n");

          /* Enter loop */
          afficher_echiquier(g, COORDINATE_NULL);
          printf("\n\n\n");
        }

        /* Separator */
        game_seperator();

        /* Enter loop */
        afficher_echiquier(g, COORDINATE_NULL);

        /* Separator */
        game_seperator();

        partie_sauvegarder(g, game_save_name);

        printf("La partie a ete sauvergardé.");

        /* Enter loop */
        afficher_echiquier(g, COORDINATE_NULL);

        game_play = game_exit(g);
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
      afficher_echiquier(g, COORDINATE_NULL);
      printf("\n\n\n");
    }
  }
}
