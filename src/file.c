#include "header/file.h"
#include "header/piece.h"
#include <stdlib.h>

/**file creer Element
 * Permet de creer un element de la liste (Maillon)
 * Parameters :
 * @param movement_t m
 *        int p
 *        int c
 * @return file_element_t
 */
file_element_t *file_creer_element(movement_t m, piece_statut_e p, int c) {
  file_element_t *res = malloc(sizeof(file_element_t));
  res->movement = m;
  res->promotion = p;
  res->capture = c;
  res->suivant = NULL;
  res->precedent = NULL;
  return res;
}

/** File detruire element
 * Permet de detruire simplement l'element
 * @params: file_element_t      -   *e
 */
void file_detruire_element(file_element_t *e) { free(e); }

/** file_list_add
 * Permet d'ajouter un element dans la liste
 * Avant de l'ajouter, on récup les données du mouvement effectué, puis on creer
 * l'élément et on l'on ajoute dans la liste
 * @params: file_list_t     -   l
 *          movement_t      -   file_element_t
 *          piece_statut_e  -   p
 *          int             -   c
 */
void file_list_add(file_list_t *l, movement_t m, piece_statut_e p, int c) {
  file_element_t *e;

  /* Initialize */
  e = file_creer_element(m, p, c);

  if (file_list_vide(l)) {
    l->debut = e;
  } else {
    l->fin->suivant = e;
    e->precedent = l->fin;
  }

  l->fin = e;
  l->taille++;
}

/** file_list_extract
 *  Permet d'extraire un element de la liste
 * @param  file_list_t - l
 * @return  file_element_t
 */
file_element_t *file_list_extract(file_list_t *l) {

  file_element_t *res;

  /* Initialize */
  res = NULL;

  if (!file_list_vide(l)) {
    res = l->fin;
    l->fin = res->precedent;
    l->taille--;

    if (!file_list_vide(l)) {
      res->suivant = NULL;
      l->fin->suivant = NULL;
    }
  } else {
    l->debut = NULL;
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
  file_list_t *res = malloc(sizeof(file_list_t));
  res->debut = NULL;
  res->fin = NULL;
  res->taille = 0;
  return res;
}

/** file_detruire_list
 *  Permet de detruite simplement une liste non vide
 *  @return file_list_t l
 */
void file_detruire_list(file_list_t *l) {
  while (!file_list_vide(l)) {
    file_detruire_element(file_list_extract(l));
  }
  free(l);
}

/** file liste vide
 * file list vide
 * Teste si la liste est vide
 * Parameters:
 * @param  file_list_t - l
 * @return int
 */
int file_list_vide(file_list_t *l) {
  if (l->taille == 0) {
    return 1;
  }
  return 0;
}

/** file_taille
 * Retourne tout simplement la taille de la liste
 * @param : file_list_t - l
 * @return : int taille
 */
int file_taille(file_list_t *l) { return l->taille; }

/** file_thread
 * Ajoute un element dans la file
 * @param: l      -   l
 *          movement_t      -   m
 *          piece_statut_e  -   p
 *          int             -   c
 */
void file_thread(file_list_t *l, movement_t m, piece_statut_e p, int c) {

  file_list_add(l, m, p, c);
}

/**
 * file unthread
 * Extrait le dernier element de la liste
 * @param:    file_list_t     - l
 * @return    file_element_t
 */
file_element_t *file_unthread(file_list_t *l) {

  file_element_t *e;

  /* Initialize */
  e = file_list_extract(l);
  file_element_t *res = e;

  return res;
}
