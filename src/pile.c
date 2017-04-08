#include "header/pile.h"
#include <stdio.h>
#include <stdlib.h>

/** pile_creer_element
 * Permet de créer un element
 * @param piece_t - p
 * @return struct file_link_s
 */
pile_element_t *    pile_creer_element(piece_t p) {
  pile_element_t *  res;

  res = malloc(sizeof(res));
  res->piece = p;
  res->next = NULL;
  return res;
}

/** pile_destuct_element
 * pile_destuct_element
 * Permet de détruire l'element
 * @param pile_element_t - pile_element_v
 */
void pile_destuct_element(pile_element_t * e) {
  free(e);
}

/** pile_list_add
 * Peremt d'ajouter un element au début de la liste
 * @param pile_list_t - l
 *        piece_t     - p
 */
void                pile_list_add(pile_list_t * l, piece_t p) {
  pile_element_t *  e;

  e = pile_creer_element(p);
  if (pile_empty(l)) l->last = e;
  else e->next = l->next;
  l->next = e;
  l->size++;
}

/** pile_list_extract
 * Extrait un element de la pile par le bas de la liste
 * @param pile_list_t - l
 * @return pile_element_t
 */
pile_element_t *    pile_list_extract(pile_list_t * l) {
  pile_element_t *  res;

  res = NULL;
  if (pile_empty(l)) return res;
  res = l->next;
  l->next = res->next;
  res->next = NULL;
  l->size--;
  if (pile_empty(l)) l->last = NULL;
  return res;
}

/** pile_create
 * Créer tout simplement une liste de pile
 * @return pile_element_t
 */
pile_list_t *   pile_create() {
  pile_list_t * res;

  res = malloc(sizeof(res));
  res->next = NULL;
  res->last = NULL;
  res->size = 0;
  return res;
}

/** pile_destuct
 * Vide la pile puis la détruit
 * @param pile_list_t - l
 */
void pile_destuct(pile_list_t * l) {
  while (!pile_empty(l)) pile_destuct_element(pile_list_extract(l));
  free(l);
}

/** pile_empty
 * Teste si la pile est vide ou pas *
 * @return int
 */
int pile_empty(pile_list_t * l) {
  return (l->size == 0) ? 1 : 0;
}

/** pile_size
 * Retourn la size de la pile
 * @param pile_list_t l
 * @return int
 */
int pile_size(pile_list_t * l) {
  return l->size;
}

/** pile_stacking
 * Ajoute une piece capturé dans la pile
 * @param pile_list_t - pile_list_v
 *        piece_t     - piece_v
 */
void pile_stacking(pile_list_t * l, piece_t p) {
  pile_list_add(l, p);
}

/** pile_unstacking
 * Permet de retirer une piece capturé
 * @param pile_list_t - pile_list_v
 */
piece_t             pile_unstacking(pile_list_t * l) {
  pile_element_t *  e;

  e = pile_list_extract(l);
  piece_t res = e->piece;
  pile_destuct_element(e);
  return res;
}
