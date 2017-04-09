#ifndef DEBUG_H
#define DEBUG_H
#include "file.h"
#include "game.h"
#include "pile.h"

void debug_pile(game_t *g);
void debug_file(game_t *g);
void debug_cell(game_t *g, coordinate_t coordinate_v);
game_t *debug_partie_nouvelle(void);

#endif
