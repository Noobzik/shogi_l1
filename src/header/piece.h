#ifndef PIECE_H
#define PIECE_H

/* Definitions des énumérations */

typedef enum { BLANC, NOIR, VIDE_PIECE } piece_color_e;
typedef enum {
  VIDE,
  ROI,
  TOUR,
  FOU,
  GOLD,
  SILVER,
  CAVALIER,
  LANCIER,
  PION,
  SELECT
} piece_type_e;

/* Definitions des structures */

typedef struct piece_s {
  piece_color_e color;
  piece_type_e type;
} piece_t;

/* Prototype des fonctions */
piece_t piece_creer(piece_color_e piece_color_v, piece_type_e piece_type_v);
int piece_couleur(piece_t piece_v);
piece_t piece_identifier(char caracter_v);
char piece_caractere(piece_t piece_v);
void piece_afficher(piece_t piece_v);

#endif
