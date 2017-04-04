#include "header/pile.h"
#include <stdio.h>
#include <stdlib.h>

/** pile_creer_element
 * Permet de créer un element
 * @param piece_t - piece_v
 * @return struct file_link_s
 */
pile_element_t *pile_creer_element(piece_t piece_v) {

  /* Variables */

  pile_element_t *res;

  /* Initialize */

  res = malloc(sizeof(pile_element_t));
  res->piece = piece_v;
  res->suivant = NULL;

  return res;
}

/** pile_detruire_element
 * pile_detruire_element
 * Permet de détruire l'element
 * @param pile_element_t - pile_element_v
 */
void pile_detruire_element(pile_element_t *pile_element_v) {

  /* Main */

  free(pile_element_v);
}

/** pile_list_add
 * Peremt d'ajouter un element au début de la liste
 * @param pile_list_t - pile_list_v
 *        piece_t     - piece_v
 */
void pile_list_add(pile_list_t *pile_list_v, piece_t piece_v) {

  /* Variables */

  pile_element_t *pile_element_tmp;

  /* Initialize */

  pile_element_tmp = pile_creer_element(piece_v);

  /* Main */

  if (pile_vide(pile_list_v)) {
    pile_list_v->last = pile_element_tmp;
  } else {
    pile_element_tmp->suivant = pile_list_v->suivant;
  }

  pile_list_v->suivant = pile_element_tmp;
  pile_list_v->taille++;
}

/** pile_list_extract
 * Extrait un element de la pile par le bas de la liste
 * @param pile_list_t - pile_list_v
 * @return pile_element_t
 */
pile_element_t *pile_list_extract(pile_list_t *pile_list_v) {

  /* Variables */

  pile_element_t *res;

  /* Initialize */

  res = NULL;

  /* Main */

  if (!pile_vide(pile_list_v)) {
    res = pile_list_v->suivant;
    pile_list_v->suivant = res->suivant;
    res->suivant = NULL;
    pile_list_v->taille--;
    if (pile_vide(pile_list_v)) {
      pile_list_v->last = NULL;
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
 * @param pile_list_t - pile_list_v
 */
void pile_detruire(pile_list_t *pile_list_v) {

  /* Main */

  while (!pile_vide(pile_list_v)) {
    pile_detruire_element(pile_list_extract(pile_list_v));
  }

  free(pile_list_v);
}

/** pile_vide
 * Teste si la pile est vide ou pas *
 * @return int
 */
int pile_vide(pile_list_t *pile_list_v) {
  return (pile_list_v->taille == 0) ? 1 : 0;
}

/** pile_taille
 * Retourn la taille de la pile
 * @param pile_list_t pile_list_v
 * @return int
 */
int pile_taille(pile_list_t *pile_list_v) {

  /* Main */

  return pile_list_v->taille;
}

/** pile_stacking
 * Ajoute une piece capturé dans la pile
 * @param pile_list_t - pile_list_v
 *        piece_t     - piece_v
 */
void pile_stacking(pile_list_t *pile_list_v, piece_t piece) {

  /* Main */

  pile_list_add(pile_list_v, piece);
}

/** pile_unstacking
 * Permet de retirer une piece capturé
 * @param pile_list_t - pile_list_v
 */
piece_t pile_unstacking(pile_list_t *pile_list_v) {

  /* Variables */

  pile_element_t *pile_element_tmp;

  /* Initialize */

  pile_element_tmp = pile_list_extract(pile_list_v);
  piece_t res = pile_element_tmp->piece;

  /* Main */
  pile_detruire_element(pile_element_tmp);
  return res;
}
