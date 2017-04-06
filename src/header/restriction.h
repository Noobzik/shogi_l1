#ifndef RESTRICTION_H
#define RESTRICTION_H
#include "game.h"

//======================================================================
// Prototype
//======================================================================
void movement_restriction();
void movement_restriction_general();
void movement_restriction_tour();
void movement_restriction_fou();
void movement_restriction_parachute(game_t *game_v);
int restriction_detector(game_t *game_v, coordinate_t coordinate_output_v);
void movement_restriction_destruct();

#endif
