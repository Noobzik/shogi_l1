#include "header/sauvegardes.h"
#include "header/piece.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

struct stat st = {0};

void partie_sauvegarder(game_t *game_v, char *game_save_name) {
  char cwd[10000];

  /* Hack pour supprimer les warning: ignoring return value of 'getcwd'*/
  if (getcwd(cwd, sizeof(cwd)))
    ;

  printf("CWD : %s\n", cwd);

  game_save_board(game_v, game_save_name, cwd);
  printf("\n\n\n");
  game_save_meta(game_v, game_save_name, cwd);
  printf("Les donénes de la pile et de la file ont été enrengistré\n");
}
/** game_save_board
 *  Sauvegarde le positionnement des pieces de l'echiquier dans un fichier
 *  @params   :   game_t    -   game_v
 *                char*     -   save_name
 *                char      -   cwd
 *  @return   :   VOID
 */
void game_save_board(game_t *game_v, char *save_name, char *cwd) {

  int x, y;

  FILE *game_plt_file_tmp = NULL;

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

  game_plt_file_tmp = fopen(game_plt_tmp, "w+");

  /* Test d'ouverture de fichier, retourne le type d'erreur */
  if (!game_plt_file_tmp)
    perror("fopen");

  /* Debut ecriture (fprintf est cassé) */
  else {
    fputs("PL\n", game_plt_file_tmp);

    for (x = 0; x < 11; x++) {
      for (y = 0; y < 11; y++) {
        fputc(piece_caractere(game_v->board[x][y]), game_plt_file_tmp);
      }
      fputs("\n", game_plt_file_tmp);
    }

    /* Fermeture du fichier */
    fclose(game_plt_file_tmp);
    printf("Echiquier sauvegardé\nChemin de la sauvegarde : %s\n",
           game_plt_tmp);
  }
}

void game_save_meta(game_t *game_v, char *game_save_name, char *cwd) {

  file_element_t *file_tmp;
  pile_element_t *pile_tmp;

  /* Chemin de Sauvegarde*/
  char game_part_tmp[500] = "";
  FILE *game_part_file_tmp = NULL;

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

  game_part_file_tmp = fopen(game_part_tmp, "w+");
  if (!game_part_file_tmp)
    perror("fopen");
  else {
    fputs("PR\n", game_part_file_tmp);
    while (!file_list_vide(game_v->file)) {
      file_tmp = file_list_extract(game_v->file);

      fprintf(game_part_file_tmp, " %d :", file_tmp->movement.input.x);
      fprintf(game_part_file_tmp, " %d :", file_tmp->movement.input.y);
      fprintf(game_part_file_tmp, " %d :", file_tmp->movement.output.x);
      fprintf(game_part_file_tmp, " %d :", file_tmp->movement.output.y);
      fprintf(game_part_file_tmp, " %d :", file_tmp->movement.valeur);
      fprintf(game_part_file_tmp, " %d :", file_tmp->promotion);
      fprintf(game_part_file_tmp, " %d :", file_tmp->capture);
      fprintf(game_part_file_tmp, "\n");
      free(file_tmp);
    }

    /* Valeur de séparation */
    fprintf(game_part_file_tmp, "42 :\n");

    while (!pile_vide(game_v->capture)) {
      pile_tmp = pile_list_extract(game_v->capture);
      fprintf(game_part_file_tmp, " %d :", pile_tmp->piece.color);
      fprintf(game_part_file_tmp, " %d :", pile_tmp->piece.type);
      fprintf(game_part_file_tmp, " %d :", pile_tmp->piece.statut);
      fprintf(game_part_file_tmp, "\n");
      free(pile_tmp);
    }

    /* Valeur de séparation */
    fprintf(game_part_file_tmp, "42 :\n");

    fclose(game_part_file_tmp);
    printf("Les coups on été enrengistré\n Chemin de la sauvegarde : %s\n",
           game_part_tmp);
  }
}
