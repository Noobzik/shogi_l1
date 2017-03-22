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

  printf("Test de la file\n");

  coordinate_t coordinate = {42, 42};

  movement_t m1;
  m1.valeur = 42;
  m1.input = coordinate;
  m1.output = coordinate;

  movement_t m2;
  m2.valeur = 43;
  m2.input = coordinate;
  m2.output = coordinate;

  movement_t m3;
  m3.valeur = 44;
  m3.input = coordinate;
  m3.output = coordinate;

  file_list_t *liste = file_creer_list();
  file_list_add(liste, m1);
  file_list_add(liste, m2);
  file_list_add(liste, m3);
  file_list_add(liste, m2);

  printf("Taille de la liste : %d \n Affichage liste -->\n",
         file_taille(liste));

  file_element_t *tmp = liste->debut;
  int i;
  for (i = 0; i < liste->taille; i++) {
    printf("%d \n", tmp->movement.valeur);
    tmp = tmp->suivant;
  }

  tmp = liste->fin;

  printf("Affichage liste <--\n");
  for (i = 0; i < liste->taille; i++) {
    printf("%d \n", tmp->movement.valeur);
    tmp = tmp->precedent;
  }
  file_detruire_list(liste);

  return EXIT_SUCCESS;
}

/*-------------------------------------------------------------------------*/
