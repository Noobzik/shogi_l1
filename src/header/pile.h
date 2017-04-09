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

pile_element_t *pile_creer_element(piece_t p);
void pile_detruire_element(pile_element_t *e);

void pile_list_add(pile_list_t *l, piece_t p);
pile_element_t *pile_list_extract(pile_list_t *l);

pile_list_t *pile_create(void);
void pile_detruire(pile_list_t *l);
int pile_vide(pile_list_t *l);
int pile_taille(pile_list_t *l);
void pile_stacking(pile_list_t *l, piece_t p);
piece_t pile_unstacking(pile_list_t *l);

#endif
