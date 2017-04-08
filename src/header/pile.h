#ifndef SHOGI_PILE_H
#define SHOGI_PILE_H

/* Helpers */

#include "piece.h"

typedef struct            pile_element_s {
  piece_t                 piece;
  struct pile_element_s * next;
}                         pile_element_t;

typedef struct      pile_list_s {
  pile_element_t *  next;
  pile_element_t *  last;
  int               size;
}                   pile_list_t;

/* Usage functions */

pile_element_t *  pile_creer_element    (piece_t p);
void              pile_destuct_element  ();
void              pile_list_add         ();
pile_element_t *  pile_list_extract     ();
pile_list_t *     pile_create           ();
void              pile_destuct          (pile_list_t * l);
int               pile_empty            (pile_list_t * l);
int               pile_lenght           ();
void              pile_stacking         ();
piece_t           pile_unstacking       ();

#endif //SHOGI_PILE_H
