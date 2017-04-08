#ifndef SHOGI_MOUVEMENT_H
#define SHOGI_MOUVEMENT_H

/* Helpers */

#include "game.h"

/* Usual functions */

/********************* Bloc validation des entrés et sortie ******************/

int     movement_valid_input                (game_t * g, coordinate_t c);
int     movement_valid_output               (coordinate_t c);
void    deplacement_valide                  (game_t * g, coordinate_t ci, coordinate_t co);
int     movement_valid_win                  (game_t * g, coordinate_t c);

/****************** Debut des validations des déplacements   ******************/

int     deplacement_valide_pion             (game_t * g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_tour             (game_t * g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_cavalier         (game_t * g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_fou              (game_t * g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_roi              (game_t * g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_gold             (game_t * g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_silver           (game_t * g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_lancier          (game_t * g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_parachutage      (game_t * g, coordinate_t ci, coordinate_t co);

/****************** Fin des validations des déplacements   ******************/

/**************** Debut des validations des déplacements  PROMOTED *************/

int     deplacement_valide_pion_promu       (game_t * g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_tour_promu       (game_t * g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_cavalier_promu   (game_t * g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_fou_promu        (game_t * g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_silver_promu     (game_t * g, coordinate_t ci, coordinate_t co);
int     deplacement_valide_lancier_promu    (game_t * g, coordinate_t ci, coordinate_t co);

/**************** FIN des validations des déplacements  PROMOTED ****************/

int     movement_valid_helper               (game_t * g, coordinate_t ci, coordinate_t co);
int     is_promoted                         (game_t * g, coordinate_t ci, coordinate_t co);
void    promote_grant                       (piece_t * p);

#endif //SHOGI_MOUVEMENT_H