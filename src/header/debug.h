#ifndef SHOGI_DEBUG_H
#define SHOGI_DEBUG_H

/* Helpers */

#include "file.h"
#include "game.h"
#include "pile.h"

/* Usage functions */

void        debug_pile      (game_t * g);
void        debug_file      (game_t * g);
void        debug_cell      (game_t * g, coordinate_t c);
game_t *    debug_new_game  ();

#endif //SHOGI_DEBUG_H
