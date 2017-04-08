#include "header/file.h"
#include "header/piece.h"
#include <stdlib.h>

/**file creer Element
 * Permet de creer un element de la liste (Maillon)
 * Parameters :
 * @param movement_t  - m
 *        int         - p
 *        int         - c
 * @return file_element_t
 */
file_element_t *    file_create_element(movement_t m, piece_statut_e p, int c) {
  file_element_t *  res;

  res = malloc(sizeof(file_element_t));
  res->movement = m;
  res->promotion = p;
  res->capture = c;
  res->next = NULL;
  res->precedent = NULL;
  return res;
}

/** File detruire element
 * Permet de detruire simplement l'element
 * @params: file_element_t  - e
 */
void file_destruct_element(file_element_t * e) {
  free(e);
}

/** file_list_add
 * Permet d'ajouter un element dans la liste
 * Avant de l'ajouter, on récup les donénes du mouvement effectué, puis on creer
 * l'élément et on l'on ajoute dans la liste
 * @params: file_list_t     -   l
 *          movement_t      -   m
 *          piece_statut_e  -   p
 *          int             -   c
 */
void                file_list_add(file_list_t * l, movement_t m, piece_statut_e p, int c) {
  file_element_t *  e;

  e = file_create_element(m, p, c);
  if (file_empty_list(l)) l->begin = e;
  else l->end->next = e, e->precedent = l->end;
  l->end = e;
  l->size++;
}

/** file_list_extract
 *  Permet d'extraire un element de la liste
 * @param  file_list_t - l
 * @return  file_element_t
 */
file_element_t *    file_list_extract(file_list_t * l) {
  file_element_t *  res;

  res = NULL;
  if (file_empty_list(l)) l->begin = NULL;
  res = l->end;
  l->end = res->precedent;
  l->size--;
  if (!file_empty_list(l)) res->next = NULL, l->end->next = NULL;
  return res;
}

/** file_create_list
 * Initialize une liste avec un pointeur vers le premier element et le dernier
 * element.
 * La liste étant vide, size  = 0.
 * @return file_list_t
 */
file_list_t *   file_create_list() {
  file_list_t * res;

  res = malloc(sizeof(file_list_t));
  res->begin = NULL;
  res->end = NULL;
  res->size = 0;
  return res;
}

/** file_destruct_list
 *  Permet de detruite simplement une liste non vide
 *  @return file_list_t l
 */
void file_destruct_list(file_list_t * l) {
  while (!file_empty_list(l)) file_destruct_element(file_list_extract(l));
  free(l);
}

/** file liste vide
 * file list vide
 * Teste si la liste est vide
 * Parameters:
 * @param  file_list_t - l
 * @return int
 */
int file_empty_list(file_list_t * l) {
  if (l->size == 0) return 1;
  return 0;
}

/** file_size
 * Retourne tout simplement la size de la liste
 * @param : file_list_t - l
 * @return : int size
 */
int file_size(file_list_t * l) {
  return l->size;
}

/** file_thread
 * Ajoute un element dans la file
 * @param:  file_list_t     -   l
 *          movement_t      -   m
 *          piece_statut_e  -   p
 *          int             -   c
 */
void file_thread(file_list_t * l, movement_t m, piece_statut_e p, int c) {
  file_list_add(l, m, p, c);
}

/**
 * file unthread
 * Extrait le dernier element de la liste
 * @param:    file_list_t     - l
 * @return    file_element_t
 */
file_element_t *    file_unthread(file_list_t * l) {
  file_element_t *  e;

  e = file_list_extract(l);
  file_element_t *res = e;
  return res;
}
