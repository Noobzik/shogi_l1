/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 21:03:40 by NoobZik           #+#    #+#             */
/*   Updated: 2017/04/30 21:03:40 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SHOGI_DEBUG_H
#define SHOGI_DEBUG_H

/* Helpers */

#include "game.h"

/*  Usual functions */

void        debug_pile              (game_t *g);
void        debug_file              (game_t *g);
void        debug_cell              (game_t *g, coordinate_t coordinate_v);
game_t      *debug_partie_nouvelle  (void);

#endif  // SHOGI_DEBUG_H
