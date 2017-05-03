/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sauvegardes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 21:04:34 by NoobZik           #+#    #+#             */
/*   Updated: 2017/04/30 21:04:35 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SHOGI_SAUVEGARDES_H
#define SHOGI_SAUVEGARDES_H

/* Helpers */

#include "game.h"

void        partie_sauvegarder  (game_t *g, char *game_save_name);
void        game_save_board     (game_t *g, char *save_name, char *cwd);
void        game_save_meta      (game_t *g, char *save_name, char *cwd);

game_t *    partie_charger(char *path);

#endif //SHOGI_SAUVEGARDES_H
