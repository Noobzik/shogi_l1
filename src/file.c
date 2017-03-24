#include "header/file.h"
#include "header/piece.h"
#include <stdlib.h>

/**file creer Element
 * Permet de creer un element de la liste (Maillon)
 * Parameters :
 * @param movement_t movement_v
 *        int promotion_v
 *        int capture_v
 * @return file_element_t
 */
file_element_t *file_creer_element(movement_t movement_v,
                                   piece_statut_e promotion_v, int capture_v) {
  file_element_t *res = (file_element_t *)malloc(sizeof(file_element_t));
  res->movement = movement_v;
  res->promotion = promotion_v;
  res->capture = capture_v;
  res->suivant = NULL;
  res->precedent = NULL;
  return res;
}

/** File detruire element
 * Permet de detruire simplement l'element
 */
void file_detruire_element(file_list_t *file_element_v) {
  free(file_element_v);
}

/** file_list_add
 * Permet d'ajouter un element dans la liste
 * Avant de l'ajouter, on récup les donénes du mouvement effectué, puis on creer
 *l'élément et on l'on ajoute dans la liste
 */
void file_list_add(file_list_t *file_list_v, movement_t movement_v,
                   piece_statut_e promotion_v, int capture_v) {
  file_element_t *file_element_tmp;

  /* Initialize */
  file_element_tmp = file_creer_element(movement_v, promotion_v, capture_v);

  if (file_list_vide(file_list_v)) {
    file_list_v->debut = file_element_tmp;
  } else {
    file_list_v->fin->suivant = file_element_tmp;
    file_element_tmp->precedent = file_list_v->fin;
  }

  file_list_v->fin = file_element_tmp;
  file_list_v->taille++;
}

/** file_list_extract
 *  Permet d'extraire un element de la liste
 * @param  file_list_t - file_list_v
 * @return  file_element_t
 */
file_element_t *file_list_extract(file_list_t *file_list_v) {
  //======================================================================
  // Variables
  //======================================================================
  file_element_t *res;

  /* Initialize */
  res = NULL;

  //======================================================================
  // Main
  //======================================================================
  if (!file_list_vide(file_list_v)) {
    res = file_list_v->debut;

    file_list_v->debut = res->suivant;
    res->suivant = NULL;
    file_list_v->taille--;

    if (file_list_vide(file_list_v)) {
      file_list_v->fin = NULL;
    }
  }

  return res;
}

/** file_creer_list
 * Initialize une liste avec un pointeur vers le premier element et le dernier
 * element.
 * La liste étant vide, taille  = 0.
 * @return file_list_t
 */
file_list_t *file_creer_list() {
  file_list_t *res = (file_list_t *)malloc(sizeof(file_list_t));
  res->debut = NULL;
  res->fin = NULL;
  res->taille = 0;
  return res;
}

/** file_detruire_list
 *  Permet de detruite simplement une liste non vide
 *  @return file_list_t file_list_v
 */
void file_detruire_list(file_list_t *file_list_v) {
  while (!file_list_vide(file_list_v)) {
    file_detruire_element((file_list_t *)file_list_extract(file_list_v));
  }
  free(file_list_v);
}

/** file liste vide
 * file list vide
 * Teste si la liste est vide
 * Parameters:
 * @param  file_list_t - file_list_v
 * @return int
 */
int file_list_vide(file_list_t *file_list_v) {
  if (file_list_v->taille == 0) {
    return 1;
  }
  return 0;
}

/** file_taille
 * Retourne tout simplement la taille de la liste
 * @param : file_list_t - file_list_v
 * @return : int taille
 */
int file_taille(file_list_t *file_list_v) { return file_list_v->taille; }
