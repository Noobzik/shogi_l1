#ifndef SHOGI_PIECE_H
#define SHOGI_PIECE_H

/* Helpers */

typedef enum {
  BLANC,
  NOIR,
  EMPTY_PIECE
} piece_color_e;

typedef enum {
  EMPTY,
  ROI,
  TOUR,
  FOU,
  GOLD,
  SILVER,
  CAVALIER,
  LANCIER,
  PION,
  PION_PROMU,
  LANCIER_PROMU,
  CAVALIER_PROMU,
  FOU_PROMU,
  TOUR_PROMU,
  SILVER_PROMU,
  SELECT
} piece_type_e;

typedef enum {
  NOT_PROMOTED,
  PROMOTED
} piece_statut_e;

typedef struct {
  piece_color_e   color;
  piece_type_e    type;
  piece_statut_e  statut;
}                 piece_t;

/* Usual functions */

piece_t piece_create      (piece_color_e c, piece_type_e t, piece_statut_e s);
int     piece_color       (piece_t p);
piece_t piece_identifier  (char c);
char    piece_caractere   (piece_t p);
void    piece_afficher    (piece_t p);

#endif //SHOGI_PIECE_H