#ifndef SHOGI_RESTRICTION_H
#define SHOGI_RESTRICTION_H

/* Helpers */

#include "game.h"

/*  Usual functions */

void    movement_restriction                    (game_t *g, coordinate_t ci);
void    movement_restriction_general            (game_t *g, coordinate_t ci);
void    movement_restriction_tour               (game_t *g, coordinate_t ci);
void    movement_restriction_pion               (game_t *g, coordinate_t ci);
void    movement_restriction_lancier            (game_t *g, coordinate_t ci);
void    movement_restriction_fou                (game_t *g, coordinate_t ci);
void    movement_restriction_parachute          (game_t *g);
void    movement_restriction_pion_parachute     (game_t *g);
int     restriction_detector                    (game_t *g, coordinate_t ci);
void    movement_restriction_destruct           (game_t *g);

#endif //SHOGI_RESTRICTION_H
