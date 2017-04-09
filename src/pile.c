#include "header/pile.h"
#include <stdio.h>
#include <stdlib.h>

/** pile_creer_element
 * Permet de créer un element
 * @param piece_t - piece_v
 * @return struct file_link_s
 */
pile_element_t *pile_creer_element(piece_t p) {

  /* Variables */

  pile_element_t *res;

  /* Initialize */

  res = malloc(sizeof(pile_element_t));
  res->piece = p;
  res->suivant = NULL;

  return res;
}

/** pile_detruire_element
 * pile_detruire_element
 * Permet de détruire l'element
 * @param pile_element_t - e
 */
void pile_detruire_element(pile_element_t *e) {

  /* Main */

  free(e);
}

/** pile_list_add
 * Peremt d'ajouter un element au début de la liste
 * @param pile_list_t - l
 *        piece_t     - piece_v
 */
void pile_list_add(pile_list_t *l, piece_t p) {

  /* Variables */

  pile_element_t *e;

  /* Initialize */

  e = pile_creer_element(p);

  /* Main */

  if (pile_vide(l)) {
    l->last = e;
  } else {
    e->suivant = l->suivant;
  }

  l->suivant = e;
  l->taille++;
}

/** pile_list_extract
 * Extrait un element de la pile par le bas de la liste
 * @param pile_list_t - l
 * @return pile_element_t
 */
pile_element_t *pile_list_extract(pile_list_t *l) {

  /* Variables */

  pile_element_t *res;

  /* Initialize */

  res = NULL;

  /* Main */

  if (!pile_vide(l)) {
    res = l->suivant;
    l->suivant = res->suivant;
    res->suivant = NULL;
    l->taille--;
    if (pile_vide(l)) {
      l->last = NULL;
    }
  }

  return res;
}

/** pile_create
 * Créer tout simplement une liste de pile
 * @return pile_element_t
 */
pile_list_t *pile_create() {

  /* Variables */

  pile_list_t *res;

  /* Initialize */

  res = malloc(sizeof(pile_list_t));
  res->suivant = NULL;
  res->last = NULL;
  res->taille = 0;

  /* Main */

  return res;
}

/** pile_detruire
 * Vide la pile puis la détruit
 * @param pile_list_t - l
 */
void pile_detruire(pile_list_t *l) {

  /* Main */

  while (!pile_vide(l)) {
    pile_detruire_element(pile_list_extract(l));
  }

  free(l);
}

/** pile_vide
 * Teste si la pile est vide ou pas *
 * @return int
 */
int pile_vide(pile_list_t *l) { return (l->taille == 0) ? 1 : 0; }

/** pile_taille
 * Retourn la taille de la pile
 * @param pile_list_t l
 * @return int
 */
int pile_taille(pile_list_t *l) {

  /* Main */

  return l->taille;
}

/** pile_stacking
 * Ajoute une piece capturé dans la pile
 * @param pile_list_t - l
 *        piece_t     - piece_v
 */
void pile_stacking(pile_list_t *l, piece_t p) {

  /* Main */

  pile_list_add(l, p);
}

/** pile_unstacking
 * Permet de retirer une piece capturé
 * @param pile_list_t - l
 */
piece_t pile_unstacking(pile_list_t *l) {

  /* Variables */

  pile_element_t *e;

  /* Initialize */

  e = pile_list_extract(l);
  piece_t res = e->piece;

  /* Main */
  pile_detruire_element(e);
  return res;
}
