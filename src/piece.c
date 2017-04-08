#include "header/piece.h"
#include <stdio.h>
#include <stdlib.h>

/** Création de piece
 * La couleur représente soit J1, soit J0
 * Le type de piece est la liste enuméré des type (ex : Fou)
 * Le statut determine si cette piece est promu ou non
 * Complexité : O(1) Temps et Espace
 * Parameters:
 * @param piece_color_e  - c
 *        piece_type_e   - t
 *        piece_statut_e - d
 *
 * @return struct piece_s
 */
piece_t   piece_create(piece_color_e c, piece_type_e t, piece_statut_e d) {
  piece_t res;

  res.color = c;
  res.type = t;
  res.statut = d;
  return res;
}

/** Couleur de piece
 * Renvoie tout simplement la couleur de piece
 * Complexité : O(1) Pour Espace / Temps
 * Parameters:
 * @param    piece_t - p
 * @return int
 */
int piece_color(piece_t p) {
  return p.color;
}

/** Identification de piece
 * piece identifier
 * Description : En fonction du caractère, renvoie la piece associé
 * Complexite : O(1) Espace et Temps
 * Parameters:
 * @param    char - c
 * @return struct piece_s
 */
piece_t piece_identifier(char c) {
  if (c >= 65 && c <= 90)
    switch (c) {
      case 'p':
        return piece_create(BLANC, PION, NOT_PROMOTED);
      case 'l':
        return piece_create(BLANC, LANCIER, NOT_PROMOTED);
      case 'n':
        return piece_create(BLANC, CAVALIER, NOT_PROMOTED);
      case 'b':
        return piece_create(BLANC, FOU, NOT_PROMOTED);
      case 'r':
        return piece_create(BLANC, TOUR, NOT_PROMOTED);
      case 's':
        return piece_create(BLANC, SILVER, NOT_PROMOTED);
      case 'g':
        return piece_create(BLANC, GOLD, NOT_PROMOTED);
      case 'k':
        return piece_create(BLANC, ROI, NOT_PROMOTED);
      case 'd':
        return piece_create(BLANC, PION, PROMU);
      case 'j':
        return piece_create(BLANC, LANCIER, PROMU);
      case 'c':
        return piece_create(BLANC, CAVALIER, PROMU);
      case 'f':
        return piece_create(BLANC, FOU, PROMU);
      case 't':
        return piece_create(BLANC, TOUR, PROMU);
      case 'a':
        return piece_create(BLANC, SILVER, PROMU);
    }
  if (c >= 97 && c <= 122)
    switch (c) {
      case 'P':
        return piece_create(NOIR, PION, NOT_PROMOTED);
      case 'L':
        return piece_create(NOIR, LANCIER, NOT_PROMOTED);
      case 'N':
        return piece_create(NOIR, CAVALIER, NOT_PROMOTED);
      case 'B':
        return piece_create(NOIR, FOU, NOT_PROMOTED);
      case 'R':
        return piece_create(NOIR, TOUR, NOT_PROMOTED);
      case 'S':
        return piece_create(NOIR, SILVER, NOT_PROMOTED);
      case 'G':
        return piece_create(NOIR, GOLD, NOT_PROMOTED);
      case 'K':
        return piece_create(NOIR, ROI, NOT_PROMOTED);
      case 'D':
        return piece_create(NOIR, PION, PROMU);
      case 'J':
        return piece_create(NOIR, LANCIER, PROMU);
      case 'C':
        return piece_create(NOIR, CAVALIER, PROMU);
      case 'F':
        return piece_create(NOIR, FOU, PROMU);
      case 'T':
        piece_create(NOIR, TOUR, PROMU);
      case 'A':
        return piece_create(NOIR, SILVER, PROMU);
    }
  return piece_create(EMPTY_PIECE, EMPTY, NOT_PROMOTED);
}

/** Detections de piece
 * Permet d'associer chaque numéro à chaque piece en fonction du type enuméré
 * et de la couleur de piece
 * Parameters:
 * @param    piece_t - piece_v
 * @return char
 */
char piece_caractere(piece_t p) {
  if (piece_color(p) == BLANC)
    switch (p.type) {
      case ROI:
        return 'k';
      case TOUR:
        return 'r';
      case FOU:
        return 'b';
      case GOLD:
        return 'g';
      case SILVER:
        return 's';
      case CAVALIER:
        return 'n';
      case LANCIER:
        return 'l';
      case PION:
        return 'p';
      case PION_PROMU:
        return 'd'; // PION PROMU
      case LANCIER_PROMU:
        return 'j'; // LANCIER PROMU
      case CAVALIER_PROMU:
        return 'c'; // CAVALIER PROMU
      case FOU_PROMU:
        return 'f'; // FOU PROMU
      case TOUR_PROMU:
        return 't'; // TOUR PROMU
      case SILVER_PROMU:
        return 'a'; // SILVER PROMU
      case SELECT:
        return '*';
      default:
        return '.';
    }
  if (piece_color(p) == NOIR)
    switch (p.type) {
      case ROI:
        return 'K';
      case TOUR:
        return 'R';
      case FOU:
        return 'B';
      case GOLD:
        return 'G';
      case SILVER:
        return 'S';
      case CAVALIER:
        return 'N';
      case LANCIER:
        return 'L';
      case PION:
        return 'P';
      case PION_PROMU:
        return 'D'; // PION PROMU
      case LANCIER_PROMU:
        return 'J'; // LANCIER PROMU
      case CAVALIER_PROMU:
        return 'C'; // CAVALIER PROMU
      case FOU_PROMU:
        return 'F'; // FOU PROMU
      case TOUR_PROMU:
        return 'T'; // TOUR PROMU
      case SILVER_PROMU:
        return 'A'; // SILVER PROMU
      case SELECT:
        return '*';
      default:
        return '.';
    }
  return '.';
}

/** piece displayer
 * piece displayer
 * Permet d'afficher tout simplement la piece sur l'echiquier
 * Complexite : O(1) pour Espace et Temps
 * Parameters:
 * @param    piece_t - p
 * @return NADA
 */
void piece_afficher(piece_t p) {
  printf("%c", piece_caractere(p));
}
