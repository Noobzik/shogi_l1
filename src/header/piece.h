#ifndef PIECE_H
#define PIECE_H

/* Definitions des énumérations */

typedef enum { BLANC, NOIR, EMPTY_PIECE } piece_color_e;
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

typedef enum { NOT_PROMOTED, PROMU } piece_statut_e;
/* Definitions des structures */

/** Structure piece
 * Structure piece
 * Color = Joueur (1 ou 0) (Noir ou Blanc)
 * Statut = NOT_PROMOTED ou PROMU
 */
typedef struct piece_s {
  piece_color_e color;
  piece_type_e type;
  piece_statut_e statut;
} piece_t;

/* Prototype des fonctions */
piece_t piece_create(piece_color_e piece_color_v, piece_type_e piece_type_v,
                    piece_statut_e piece_statut_v);
int piece_couleur(piece_t piece_v);
piece_t piece_identifier(char caracter_v);
char piece_caractere(piece_t piece_v);
void piece_afficher(piece_t piece_v);

#endif
