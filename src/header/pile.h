/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pile.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 21:04:18 by NoobZik           #+#    #+#             */
/*   Updated: 2017/04/30 21:04:22 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SHOGI_PILE_H
#define SHOGI_PILE_H

/* Helpers */

#include "piece.h"

typedef struct              pile_element_s {
  piece_t                   piece;
  struct pile_element_s *   suivant;
}                           pile_element_t;


typedef struct              pile_list_s {
  pile_element_t *          suivant;
  pile_element_t *          last;
  int                       taille;
}                           pile_list_t;

/*  Usual functions */

pile_element_t *            pile_creer_element      (piece_t p);
void                        pile_detruire_element   (pile_element_t *e);

void                        pile_list_add           (pile_list_t *l, piece_t p);
pile_element_t *            pile_list_extract       (pile_list_t *l);

pile_list_t    *            pile_create             (void);
void                        pile_detruire           (pile_list_t *l);
int                         pile_vide               (pile_list_t *l);
int                         pile_taille             (pile_list_t *l);
void                        pile_stacking           (pile_list_t *l, piece_t p);
piece_t                     pile_unstacking         (pile_list_t *l);

#endif //SHOGI_PILE_H
