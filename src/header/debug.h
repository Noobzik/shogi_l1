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
