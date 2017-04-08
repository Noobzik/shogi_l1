#include "game.h"
#ifndef SAUVEGARDES_H
#define SAUVEGARDES_H

void partie_sauvegarder(game_t *game_v, char *game_save_name);
void game_save_board(game_t *game_v, char *save_name, char *cwd);
void game_save_meta(game_t *game_v, char *save_name, char *cwd);

#endif
