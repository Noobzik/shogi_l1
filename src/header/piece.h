/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 21:04:12 by NoobZik           #+#    #+#             */
/*   Updated: 2017/04/30 21:04:16 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SHOGI_PIECE_H
#define SHOGI_PIECE_H

/* Definitions des énumérations */

typedef enum {
    BLANC,
    NOIR,
    VIDE_PIECE
}   piece_color_e;

typedef enum {
  VIDE,
  ROI,
  TOUR,
  FOU,
  GOLD,
  SILVER,
  CAVALIER,
  LANCIER,
  PION,
  PION_PROMU,
  LANCIER_PROMU,
  CAVALIER_PROMU,
  FOU_PROMU,
  TOUR_PROMU,
  SILVER_PROMU,
  SELECT
} piece_type_e;

typedef enum {
    NON_PROMU,
    PROMU
}   piece_statut_e;

/* Definitions des structures */

/** Structure piece
 * Structure piece
 * Color = Joueur (1 ou 0) (Noir ou Blanc)
 * Statut = NON_PROMU ou PROMU
 */
typedef struct      piece_s {
  piece_color_e     color;
  piece_type_e      type;
  piece_statut_e    statut;
}                   piece_t;

/*  Usual functions */

piece_t piece_creer             (piece_color_e c, piece_type_e t, piece_statut_e s);
int     piece_couleur           (piece_t p);
piece_t piece_identifier        (char caracter_v);
char    piece_caractere         (piece_t p);
void    piece_afficher          (piece_t p);

void    promote_grant           (piece_t *p);
piece_t demote_grant_reserve    (piece_t p);
piece_t demote_grant            (piece_t p);
piece_t switch_color            (piece_t p);
int     piece_cmp_reserve       (piece_t p1, piece_t p2);
#endif //SHOGI_PIECE_H
