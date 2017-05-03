/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 21:05:00 by NoobZik           #+#    #+#             */
/*   Updated: 2017/04/30 21:05:00 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "header/pile.h"
#include <stdio.h>
#include <stdlib.h>

/** pile_creer_element
 * Permet de créer un element
 * @param piece_t - piece_v
 * @return struct file_link_s
 */
pile_element_t *pile_creer_element  (piece_t p) {
  pile_element_t *                  res;

  res = malloc(sizeof(pile_element_t));
  res->piece = p;
  res->suivant = NULL;

  return res;
}

/** pile_detruire_element
 * pile_detruire_element
 * Permet de détruire l'element
 * @param:   pile_element_t - e
 * @return:  (void)
 */
void pile_detruire_element  (pile_element_t *e) {
  free(e);
}

/** pile_list_add
 * Peremt d'ajouter un element au début de la liste
 * @param   pile_list_t - l
 *          piece_t     - piece_v
 * @return: (void)
 */
void pile_list_add          (pile_list_t *l, piece_t p) {
  pile_element_t *          e;

  e = pile_creer_element(p);
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
pile_element_t *pile_list_extract   (pile_list_t *l) {
  pile_element_t *                  res;

  res = NULL;

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
 * @param: (void)
 * @return pile_element_t
 */
pile_list_t *pile_create    () {
  pile_list_t *             res;

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
 * @return (void)
 */
void pile_detruire          (pile_list_t *l) {
  while (!pile_vide(l)) {
    pile_detruire_element(pile_list_extract(l));
  }
  free(l);
}

/** pile_vide
 * Teste si la pile est vide ou pas *
 * @param: pile_list_t      -   -l
 * @return int
 */
int pile_vide               (pile_list_t *l) {
    return (l->taille == 0) ? 1 : 0;
}

/** pile_taille
 * Retourn la taille de la pile
 * @param pile_list_t l
 * @return int
 */
int pile_taille             (pile_list_t *l) {
  return l->taille;
}

/** pile_stacking
 * Ajoute une piece capturé dans la pile
 * @param   pile_list_t - l
 *          piece_t     - piece_v
 * @return: (void)
 */
void pile_stacking          (pile_list_t *l, piece_t p) {
  pile_list_add(l, p);
}

/** pile_unstacking
 * Permet de retirer une piece capturé
 * @param   pile_list_t - l
 * @return: (void)
 */
piece_t pile_unstacking     (pile_list_t *l) {
  pile_element_t            *e;

  e = pile_list_extract(l);
  piece_t res = e->piece;
  pile_detruire_element(e);
  return res;
}
