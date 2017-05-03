/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 21:03:44 by NoobZik           #+#    #+#             */
/*   Updated: 2017/04/30 21:06:04 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SHOGI_DISPLAY
#define SHOGI_DISPLAY

/* Helpers */

#include "game.h"

void            show_menu              (int game_command_dev);
int             dev_enabler            (int game_command_dev);
coordinate_t    cell_input             (game_t *g,coordinate_t g_i);
void            surrend                (game_t *g);
void            unknow_cmd             (char const *game_command);
void            selected_piece         (game_t *g, coordinate_t g_i);
void            print__select_piece    (void);

#endif //SHOGI_DISPLAY
