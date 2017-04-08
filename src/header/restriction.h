#ifndef RESTRICTION_H
#define RESTRICTION_H
#include "game.h"

//======================================================================
// Prototype
//======================================================================
void movement_restriction(game_t *game_v, coordinate_t coordinate_input_v);
void movement_restriction_general(game_t *game_v, coordinate_t coordinate_input_v);
void movement_restriction_tour(game_t *game_v, coordinate_t coordinate_input_v);
void movement_restriction_pion(game_t *game_v,coordinate_t coordinate_input_v);
void movement_restriction_lancier(game_t *game_v, coordinate_t coordinate_input_v);
void movement_restriction_fou(game_t *game_v, coordinate_t coordinate_input_v);
void movement_restriction_parachute(game_t *game_v);
int restriction_detector(game_t *game_v, coordinate_t coordinate_output_v);
void movement_restriction_destruct(game_t *game_v);

#endif
