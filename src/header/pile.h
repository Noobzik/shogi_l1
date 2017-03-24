#ifndef DEF_STRUCTURE_PILE
#define DEF_STRUCTURE_PILE
#include "piece.h"

/* @section 1. pile link */

typedef struct pile_element_s {
  piece_t piece;
  struct pile_element_s *suivant;
} pile_element_t;

/* @section 2. pile list */

typedef struct pile_list_s {
  pile_element_t *suivant;
  pile_element_t *last;
  int taille;
} pile_list_t;

/**
 * @section 3 prototype
 *
 * 1. pile.c
 *    1.1 pile_list.h
 */

pile_element_t *pile_creer_element(piece_t piece_v);
void pile_detruire_element();

void pile_list_add();
pile_element_t *pile_list_extract();

pile_list_t *pile_create();
void pile_detruire(pile_list_t *pile_list_v);
int pile_vide(pile_list_t *pile_list_v);
int pile_taille();
void pile_stacking();
piece_t pile_unstacking();

#endif
