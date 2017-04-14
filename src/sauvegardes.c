#include "header/sauvegardes.h"
#include "header/game.h"
#include "header/piece.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

struct stat st = {0};

void partie_sauvegarder(game_t *g, char *game_save_name) {
  char cwd[10000];

  /* Hack pour supprimer les warning: ignoring return value of 'getcwd'*/
  if (getcwd(cwd, sizeof(cwd)) == NULL) {
    perror("getcwd :");
  }

  printf("CWD : %s\n", cwd);

  game_save_board(g, game_save_name, cwd);
  printf("\n\n\n");
  game_save_meta(g, game_save_name, cwd);
  printf("Les donénes de la pile et de la file ont été enrengistré\n");
}
/** game_save_board
 *  Sauvegarde le positionnement des pieces de l'echiquier dans un fichier
 *  @params   :   game_t    -   g
 *                char*     -   save_name
 *                char      -   cwd
 *  @return   :   VOID
 */
void game_save_board(game_t *g, char *save_name, char *cwd) {

  int x, y;

  FILE *fp = NULL;

  /* Chemin du sauvegarde*/
  char game_plt_tmp[500] = "";

  printf("Sauvegarde de l'échiquier en cours ...\n");
  /* Concatenation du chemin absolue et du dossier partie */
  strcpy(game_plt_tmp, cwd);
  strcat(game_plt_tmp, "/plateaux");

  printf("Current Working Directory : %s\n", game_plt_tmp);

  /* Création du répertoire si le dossier n'existe pas */
  if (stat(game_plt_tmp, &st) == -1) {
    printf("Dossier absent\nmkdir : %s\n", game_plt_tmp);
    mkdir(game_plt_tmp, 0777);
  }

  /* Concatenation du nom de la sauvegardes + extension */
  strcat(game_plt_tmp, "/");
  strcat(game_plt_tmp, save_name);
  strcat(game_plt_tmp, ".plt");

  fp = fopen(game_plt_tmp, "w+");

  /* Test d'ouverture de fichier, retourne le type d'erreur */
  if (!fp)
    perror("fopen");

  /* Debut ecriture (fprintf est cassé) */
  else {
    fputs("PL\n", fp);

    for (x = 0; x < 11; x++) {
      for (y = 0; y < 11; y++) {
        fputc(piece_caractere(g->board[x][y]), fp);
      }
      fputs("\n", fp);
    }

    /* Fermeture du fichier */
    fclose(fp);
    printf("Echiquier sauvegardé\nChemin de la sauvegarde : %s\n",
           game_plt_tmp);
  }
}

void game_save_meta(game_t *g, char *game_save_name, char *cwd) {

  file_element_t *file_tmp;
  pile_element_t *pile_tmp;

  /* Chemin de Sauvegarde*/
  char game_part_tmp[500] = "";
  FILE *fp = NULL;

  printf("Sauvegarde de pile / file en cours ...\n");
  printf("CWD : %s\n", cwd);
  strcpy(game_part_tmp, cwd);
  strcat(game_part_tmp, "/partie");
  printf("Current Working Directory : %s\n", game_part_tmp);

  if (stat(game_part_tmp, &st) == -1) {
    printf("Dossier absent\nmkdir : %s\n", game_part_tmp);
    mkdir(game_part_tmp, 0777);
  }

  strcat(game_part_tmp, "/");
  strcat(game_part_tmp, game_save_name);
  strcat(game_part_tmp, ".part");

  fp = fopen(game_part_tmp, "w+");
  if (!fp)
    perror("fopen");
  else {
    fputs("PR\n", fp);
    while (!file_list_vide(g->file)) {
      file_tmp = file_list_extract(g->file);

      fprintf(fp, " %d :", file_tmp->movement.input.x);
      fprintf(fp, " %d :", file_tmp->movement.input.y);
      fprintf(fp, " %d :", file_tmp->movement.output.x);
      fprintf(fp, " %d :", file_tmp->movement.output.y);
      fprintf(fp, " %d :", file_tmp->movement.valeur);
      fprintf(fp, " %d :", file_tmp->promotion);
      fprintf(fp, " %d :", file_tmp->capture);
      fprintf(fp, "\n");
      free(file_tmp);
    }

    /* Valeur de séparation */
    fprintf(fp, "42 :\n");

    while (!pile_vide(g->capture)) {
      pile_tmp = pile_list_extract(g->capture);
      fprintf(fp, " %d :", pile_tmp->piece.color);
      fprintf(fp, " %d :", pile_tmp->piece.type);
      fprintf(fp, " %d :", pile_tmp->piece.statut);
      fprintf(fp, "\n");
      free(pile_tmp);
    }

    /* Valeur de séparation */
    fprintf(fp, "42 :\n");

    fclose(fp);
    printf("Les coups on été enrengistré\n Chemin de la sauvegarde : %s\n",
           game_part_tmp);
  }
}

game_t *partie_charger(char *path) {

  game_t *res = NULL;

  char load[500];
  int game_piece_check;
  char game_check[50];
  int x, y;

  if (getcwd(load, sizeof(load)) == NULL) {
    perror("getcwd");
    return NULL;
  }

  strcat(load, "/plateaux");
  strcat(load, "/");
  strcat(load, path);
  strcat(load, ".plt");

  FILE *fp = fopen(load, "r");

  if (!fp) {
    perror("fopen");
    printf("Erreur de chargement du plateaux\n");
    return NULL;
  }

  else {
    printf("Le fichier %s est ouvert avec succès\n", path);

    if (fscanf(fp, "%s\n", game_check) != 1) {
      perror("fscanf :");
    }

    if (strcmp(game_check, "PL") == 0) {
      printf("Je suis rentré ici ?\n");
      res = partie_creer();
      res->capture = pile_create();
      res->file = file_creer_list();
      res->player = 0;

      /* Chargement du fichier */

      fseek(fp, 3, SEEK_SET);

      for (x = 0; x < 11; x++) {
        for (y = 0; y < 12; y++) {
          game_piece_check = fgetc(fp);
          if (game_piece_check != '\n') {
            res->board[x][y] = piece_identifier((char)game_piece_check);
          }
        }
      }

      fseek(fp, 3, SEEK_SET);

      for (x = 0; x < 11; x++) {
        for (y = 0; y < 12; y++) {
          game_piece_check = fgetc(fp);
          if (game_piece_check != '\n') {
            piece_afficher(res->board[x][y]);
          }
        }
        printf("\n");
      }

    }

    else
      printf("Ce fichier est corrompu\n");

    fclose(fp);
  }
  return res;
}