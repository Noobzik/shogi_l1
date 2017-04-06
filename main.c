//#include "src/header/file.h"
#include "src/header/debug.h"
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
  partie_jouer(game_new);
  /* Début du programme principale */

  /* Valeur de fonction */

  return EXIT_SUCCESS;
}

/*-------------------------------------------------------------------------*/
