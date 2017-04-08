//#include "src/header/file.h"
#include "src/header/debug.h"
#include "src/header/game.h"
#include "src/header/sauvegardes.h"
#include <stdio.h>  /* printf && scanf */
#include <stdlib.h> /* EXIT_SUCCESS; */

/* Prototype des fontions */

/* Eventuels Variables globales */

/* -----------------------------------------------------------------------*/
/* Fonction principale */

int main(int argc, char *argv[]) {

  /* Enlève le warning de variable pas utilisé*/
  (void) argc;


  if (argv[1] != NULL) {
    printf("Fichier à charger : %s\n", argv[1]);
    game_t *load = partie_charger(argv[1]);
    if(load != NULL)
      partie_jouer(load);
    else
      printf("Fichier inexistant\n");
  }

  else {
    // game_t *game_new = debug_partie_nouvelle();
    game_t *game_new = partie_nouvelle();
    partie_jouer(game_new);
    /* Début du programme principale */
  }
  /* Valeur de fonction */

  return EXIT_SUCCESS;
}

/*-------------------------------------------------------------------------*/
