#include "src/header/file.h"
#include "src/header/game.h"
#include <stdio.h>  /* printf && scanf */
#include <stdlib.h> /* EXIT_SUCCESS; */

/* Prototype des fontions */

/* Eventuels Variables globales */

/* -----------------------------------------------------------------------*/
/* Fonction principale */

int main() {

  /* Déclarations des variables */

  game_t *game_new = partie_nouvelle();

  /* Début du programme principale */

  afficher_echiquier(game_new);
  partie_detruire(game_new);

  /* Valeur de fonction */

  return EXIT_SUCCESS;
}

/*-------------------------------------------------------------------------*/
