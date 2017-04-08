#ifndef SHOGI_FILE_H
#define SHOGI_FILE_H

/* Helpers */

#include "piece.h"

typedef struct  coordinate_s {
  int           x;
  int           y;
}               coordinate_t;

typedef struct  movement_s {
  int           valeur;
  coordinate_t  input;
  coordinate_t  output;
}               movement_t;

typedef struct            file_element_s {
  movement_t              movement;
  int                     promotion;
  int                     capture;
  struct file_element_s * next;
  struct file_element_s * precedent;
}                         file_element_t;

typedef struct      file_list_s {
  file_element_t *  begin;
  file_element_t *  end;
  int               size;
}                   file_list_t;

/* Usage functions */

file_element_t *  file_create_element   (movement_t m, piece_statut_e p, int c);
void              file_destruct_element (file_element_t * e);
void              file_list_add         (file_list_t * l, movement_t m, piece_statut_e p, int c);
file_element_t *  file_list_extract     (file_list_t * l);
file_list_t *     file_create_list      ();
void              file_destruct_list    (file_list_t * l);
int               file_empty_list       (file_list_t * l);
int               file_size             (file_list_t * l);
void              file_thread           (file_list_t * l, movement_t m, piece_statut_e p, int c);
file_element_t *  file_unthread         (file_list_t * l);

#endif //SHOGI_FILE_H
