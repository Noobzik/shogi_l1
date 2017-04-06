/* Rappel, indentation automatique, retour chariot au bout de 80 charactère */
#ifndef MOUVEMENT_H
#define MOUVEMENT_H
#include "game.h"

/********************* Bloc validation des entrés et sortie ******************/

int movement_valid_input(game_t *game_v, coordinate_t coordinate_v);
int movement_valid_output(coordinate_t coordinate_v);
void deplacement_valide(game_t *game_v, coordinate_t coordinate_input_v,
                        coordinate_t coordinate_output_v);
int movement_valid_win(game_t *game_v, coordinate_t coordinate_v);
/****************** Debut des validations des déplacements   ******************/

int deplacement_valide_pion(game_t *game_v, coordinate_t coordinate_input_v,
                            coordinate_t coordinate_output_v);
int deplacement_valide_tour(game_t *game_v, coordinate_t coordinate_input_v,
                            coordinate_t coordinate_output_v);
int deplacement_valide_cavalier(game_t *game_v, coordinate_t coordinate_input_v,
                                coordinate_t coordinate_output_v);
int deplacement_valide_fou(game_t *game_v, coordinate_t coordinate_input_v,
                           coordinate_t coordinate_output_v);

int deplacement_valide_roi(game_t *game_v, coordinate_t coordinate_input_v,
                           coordinate_t coordinate_output_v);
int deplacement_valide_gold(game_t *game_v, coordinate_t coordinate_input_v,
                            coordinate_t coordinate_output_v);
int deplacement_valide_silver(game_t *game_v, coordinate_t coordinate_input_v,
                              coordinate_t coordinate_output_v);
int deplacement_valide_lancier(game_t *game_v, coordinate_t coordinate_input_v,
                               coordinate_t coordinate_output_v);
int deplacement_valide_parachutage(game_t *game_v,
                                   coordinate_t coordinate_input_v,
                                   coordinate_t coordinate_output_v);
/****************** Fin des validations des déplacements   ******************/
/**************** Debut des validations des déplacements  PROMU *************/
int deplacement_valide_pion_promu(game_t *game_v,
                                  coordinate_t coordinate_input_v,
                                  coordinate_t coordinate_output_v);
int deplacement_valide_tour_promu(game_t *game_v,
                                  coordinate_t coordinate_input_v,
                                  coordinate_t coordinate_output_v);
int deplacement_valide_cavalier_promu(game_t *game_v,
                                      coordinate_t coordinate_input_v,
                                      coordinate_t coordinate_output_v);
int deplacement_valide_fou_promu(game_t *game_v,
                                 coordinate_t coordinate_input_v,
                                 coordinate_t coordinate_output_v);
int deplacement_valide_silver_promu(game_t *game_v,
                                    coordinate_t coordinate_input_v,
                                    coordinate_t coordinate_output_v);
int deplacement_valide_lancier_promu(game_t *game_v,
                                     coordinate_t coordinate_input_v,
                                     coordinate_t coordinate_output_v);
/**************** FIN des validations des déplacements  PROMU ****************/

int movement_valid_helper(game_t *game_v, coordinate_t coordinate_input_v,
                          coordinate_t coordinate_output_v);
int is_promoted(game_t *game_v, coordinate_t coordinate_input_v,
                coordinate_t coordinate_output_v);
void promote_grant(piece_t *piece);
#endif
