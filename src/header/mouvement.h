/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 21:04:06 by NoobZik           #+#    #+#             */
/*   Updated: 2017/05/10 03:35:59 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SHOGI_MOUVEMENT_H
#define SHOGI_MOUVEMENT_H

/* Helpers */

#include "game.h"

/*
** p_list
** Servant de variables pour afficher les textes
*/

/*  Usual functions */

/********************* Bloc validation des entrés et sortie *******************/

int     check_reserve                       (coordinate_t ci);
int     movement_valid_input                (game_t *g, coordinate_t coordinate_v);
int     movement_valid_output               (coordinate_t coordinate_v);
void    deplacement_valide                  (game_t *g, coordinate_t ci, coordinate_t co);
int     movement_valid_win                  (game_t *g, coordinate_t coordinate_v);

/****************** Bloc des validations des déplacements   *****************-*/

int     deplacement_valide_pion             (game_t *g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_tour             (game_t *g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_cavalier         (game_t *g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_fou              (game_t *g, coordinate_t ci, coordinate_t co);

int     deplacement_valide_roi              (game_t *g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_gold             (game_t *g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_silver           (game_t *g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_lancier          (game_t *g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_parachutage      (game_t *g, coordinate_t ci, coordinate_t co);

/**************** Debut des validations des déplacements  PROMU *************/

int     deplacement_valide_pion_promu       (game_t *g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_tour_promu       (game_t *g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_cavalier_promu   (game_t *g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_fou_promu        (game_t *g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_silver_promu     (game_t *g, coordinate_t ci,coordinate_t co);
int     deplacement_valide_lancier_promu    (game_t *g, coordinate_t ci,coordinate_t co);

/**************** FIN des validations des déplacements  PROMU ****************/

int     movement_valid_helper               (game_t *g, coordinate_t ci, coordinate_t co);
int     is_promoted                         (game_t *g, coordinate_t ci, coordinate_t co);

void    annuler_deplacement                 (game_t *g);
void    deplacement_apply                   (game_t *g, coordinate_t ci, coordinate_t co);

#endif // SHOGI_GAME_H
