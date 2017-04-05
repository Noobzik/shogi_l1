#include "header/game.h"
#include "header/debug.h"
#include "header/file.h"
#include "header/mouvement.h"
#include "header/piece.h"
#include "header/pile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256
coordinate_t COORDINATE_NULL = {42, 42};
// Rakib

/** Afficher_echiquier
 * Description :
 * La premiere boucle for permet l'espacement et d'afficher le tour actuelle du
 * joueur La deuxieme boucle for affiche le contenue de chaque case de
 * l'échiquier Parameters :
 * @param : game_t - game_v
 * @return : VOID
 */
void afficher_echiquier(game_t *game_v, coordinate_t COORDINATE_NULL) {

  /* Variables de boucles pour les coordonnes*/
  int x, y;

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
  return res = malloc(sizeof(game_t));
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
  res->capture = pile_create();
  res->file = file_creer_list();
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

/** Case vide
 * Permet de savoir si la case est vide ou pas
 * @param piece_t piece_v
 * @return int
 */
int case_vide(piece_t piece_v) { return (piece_v.type == VIDE) ? 1 : 0; }

/** Modifier case
 *  Permet de modifier le contenue de la case
 *  @param game_t *game_v
 *         piece_t piece_v
 *         coordinate_t coordonate_v
 *  @return RIEN
 */
void modifier_case(game_t *game_v, piece_t piece_v, coordinate_t coordinate_v) {
  piece_t res = piece_creer(piece_v.color, piece_v.type, piece_v.statut);
  game_v->board[coordinate_v.x][coordinate_v.y] = res;
}

/** Changer joueur
 * Permet de changer le tour actuelle du joueur
 * @param game_t *game_v
 */
void changer_joueur(game_t *game_v) {
  (game_v->player == 0) ? (game_v->player = 1) : (game_v->player = 0);
}

void deplacement_apply(game_t *game_v, coordinate_t coordinate_input_v,
                       coordinate_t coordinate_output_v) {
  movement_t game_movement_tmp;
  game_movement_tmp.input = coordinate_input_v;
  game_movement_tmp.output = coordinate_output_v;
  int x, y, test = 1, test_bis = 0;

  // A finir, il doit etre utiliser pour stocker dans la file

  int promotion_v =
      is_promoted(game_v, coordinate_input_v, coordinate_output_v);
  if (!case_vide(game_v->board[coordinate_input_v.x][coordinate_input_v.y])) {

    /* Checking présence de piece (Si c'est le cas -> capture) */

    if (!case_vide(
            game_v->board[coordinate_output_v.x][coordinate_output_v.y]) &&
        piece_couleur(
            game_v->board[coordinate_output_v.x][coordinate_output_v.y]) !=
            piece_couleur(
                game_v->board[coordinate_input_v.x][coordinate_input_v.y])) {

      /* TOUJOURS DANS LE IF !CASE VIDE*/

      pile_stacking(
          game_v->capture,
          game_v->board[coordinate_output_v.x][coordinate_output_v.y]);

      /** Ici une fonction qui met la piece capturé dans la reserve
       *  On vérifie que la case est vide pour placer la piece, sinon on passe
       *  au suivant. Si il n'y a plus de place dans l'axe des x, on passe a la
       *  deuxieme boucle le l'axe des y
       */

      /** Noir **/

      if (game_v->player == 1) {
        x = 10;

        while (test == 1) {
          if (case_vide(game_v->board[0][x]) == 1) {
            test = 0;
            game_v->board[0][x] = piece_creer(
                BLANC,
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

        while (test_bis == 1) {
          printf("Suis-je rentrée ici ? je vaux %d\n", y);

          if (case_vide(game_v->board[y][0]) == 1) {
            printf("Youpi je suis vide et je vaux %d\n", y);
            test_bis = 0;
            game_v->board[y][0] = piece_creer(
                BLANC,
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

      /* Ici une fonction qui met dans la reserve */
      /** Blanc **/
      if (game_v->player == 0) {
        x = 0;

        while (test == 1) {
          if (case_vide(game_v->board[0][x]) == 1) {
            test = 0;
            game_v->board[10][x] = piece_creer(
                NOIR,
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
          printf("Suis-je rentrée ici ? je vaux %d\n", y);

          if (case_vide(game_v->board[y][0]) == 1) {
            printf("Youpi je suis vide et je vaux %d\n", y);
            test_bis = 0;
            //    game_v->board[y][0] =
            //        game_v->board[coordinate_output_v.x][coordinate_output_v.y];
            game_v->board[y][0] = piece_creer(
                NOIR,
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

      game_movement_tmp.valeur = 1;

      /* Apply movement */

      game_v->board[coordinate_output_v.x][coordinate_output_v.y] =
          game_v->board[coordinate_input_v.x][coordinate_input_v.y];
      game_v->board[coordinate_input_v.x][coordinate_input_v.y] =
          piece_creer(VIDE_PIECE, VIDE, NON_PROMU);

      /* Piece switch */

      file_thread(game_v->file, game_movement_tmp, promotion_v, 1);
      changer_joueur(game_v);
    } else {
      game_v->board[coordinate_output_v.x][coordinate_output_v.y] =
          game_v->board[coordinate_input_v.x][coordinate_input_v.y];
      game_v->board[coordinate_input_v.x][coordinate_input_v.y] =
          piece_creer(VIDE_PIECE, VIDE, NON_PROMU);

      /* Piece switch */

      //      file_thread(game_v->played, game_movement_tmp);
      changer_joueur(game_v);
    }
  }
}
/** saisie_case
 *  Permet de saisir les coordonnées d'une case
 *  Cette fonction est un substitut du scanf
 *  Complexite : Temps O(p) Espace  O(1)
 *  Parameters :
 *  @param VIDE
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
 */
void game_seperator() {
  //======================================================================
  // Main
  //======================================================================
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
         "\n\n\n\n\n\n");
}
/*-----------------------------------------------------------------------------------------*/
/**
 * game buffer
 */
void game_buffer() {
  //======================================================================
  // Variables
  //======================================================================
  char empty_buffer;
  //======================================================================
  // Variables
  //======================================================================
  do
    empty_buffer = getchar();
  while (empty_buffer != '\n' && empty_buffer != EOF);
}

/**
 * game exit
 */
int game_exit(game_t *game_v) {
  //======================================================================
  // Main
  //======================================================================

  file_detruire_list(game_v->file);
  pile_detruire(game_v->capture);
  partie_detruire(game_v);

  return 0;
}

/**
 * game select
 *
 * Parameters:
 *     char - game_command
 *     char - select_v
 *
 * @return int
 */
int game_selector(char game_command[MAX_CHAR], char select_v[MAX_CHAR]) {
  //======================================================================
  // Main
  //======================================================================
  if (strcmp(game_command, select_v) == 0) {
    return 1;
  } else {
    return 0;
  }
}

void partie_jouer(game_t *game_v) {
  //======================================================================
  // Variables
  //======================================================================
  char game_command[MAX_CHAR] = "";
  char *game_save_name = malloc(MAX_CHAR);
  char *game_save_path = malloc(MAX_CHAR);
  char game_exit_confirmation[MAX_CHAR];

  coordinate_t game_input_tmp, game_output_tmp;

  /* Game setting */
  int game_command_dev = 0;
  int game_play = 1;

  //======================================================================
  // Main
  //======================================================================
  /* First chess board display*/

  printf("Je suis une poire.");
  game_seperator();
  printf("Nouvelle partie.\n");

  /* Enter loop */
  afficher_echiquier(game_v, COORDINATE_NULL);
  printf("\n\n\n");

  /* Main loop */
  while (game_play) {

    /* Command input */
    printf("Entrer une commande: ");

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
        printf("FILE                  Affiche lse donnes contenu dans la "
               "file.\n");
        printf("PILE                  Affiche les donnes contenu dans la "
               "pile.\n");
        printf("CELL                  Inspecter une cellule.\n");
      } else {
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

      //      debug_cell(game_v, game_input_tmp);

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

      /* Input */
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

      /* Output */
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
      //      is_promoted(game_v, game_input_tmp, game_output_tmp);
      game_seperator();
      deplacement_valide(game_v, game_input_tmp, game_output_tmp);

      /* Enter loop */
      afficher_echiquier(game_v, COORDINATE_NULL);
      printf("\n\n\n");

      /* Back command */
    } else if (game_selector(game_command, "back")) {

      /* Separator */
      game_seperator();

      if (!file_list_vide(game_v->file)) {
        printf("L'annulation à été éffectué.\n");
        // annuler_deplacement(game_v);
      } else {
        printf("L'annulation à échoué.\n");
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

        /* Enter loop */
        afficher_echiquier(game_v, COORDINATE_NULL);
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

      /* Unknown command */
    } else {

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
