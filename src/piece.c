#include "header/piece.h"
#include <stdio.h>
#include <stdlib.h>

/** Création de piece
 * La couleur représente soit J1, soit J0
 * Le type de piece est la liste enuméré des type (ex : Fou)
 * Le statut determine si cette piece est promu ou non
 * Complexité : O(1) Temps et Espace
 * Parameters:
 * @param piece_color_e  - piece_color_v
 *        piece_type_e   - piece_type_v
 *        piece_statut_e - piece_statut_v
 *
 * @return struct piece_s
 */
piece_t piece_creer(piece_color_e piece_color_v, piece_type_e piece_type_v,
                    piece_statut_e piece_statut_v) {

  piece_t res;

  /* Initialiser */
  res.color = piece_color_v;
  res.type = piece_type_v;
  res.statut = piece_statut_v;

  return res;
}

/** Couleur de piece
 * Renvoie tout simplement la couleur de piece
 * Complexité : O(1) Pour Espace / Temps
 * Parameters:
 * @param    piece_t - piece_v
 * @return int
 */
int piece_couleur(piece_t piece_v) { return piece_v.color; }

/** Identification de piece
 * piece identifier
 * Description : En fonction du caractère, renvoie la piece associé
 * Complexite : O(1) Espace et Temps
 * Parameters:
 * @param    char - caracter_v
 * @return struct piece_s
 */
piece_t piece_identifier(char caracter_v) {
  if (caracter_v <= 90 && caracter_v >= 65) {
    switch (caracter_v) {
      // Non promu joueur 0
      {
      case 'P':
        return piece_creer(NOIR, PION, NON_PROMU);
      }
      {
      case 'L':
        return piece_creer(NOIR, LANCIER, NON_PROMU);
      }
      {
      case 'N':
        return piece_creer(NOIR, CAVALIER, NON_PROMU);
      }
      {
      case 'B':
        return piece_creer(NOIR, FOU, NON_PROMU);
      }
      {
      case 'R':
        return piece_creer(NOIR, TOUR, NON_PROMU);
      }
      {
      case 'S':
        return piece_creer(NOIR, SILVER, NON_PROMU);
      }
      {
      case 'G':
        return piece_creer(NOIR, GOLD, NON_PROMU);
      }
      {
      case 'K':
        return piece_creer(NOIR, ROI, NON_PROMU);
      }
      // Promu Joueur 1
      {
      case 'D':
        return piece_creer(NOIR, PION, PROMU);
      }
      {
      case 'J':
        return piece_creer(NOIR, LANCIER, PROMU);
      }
      {
      case 'C':
        return piece_creer(NOIR, CAVALIER, PROMU);
      }
      {
      case 'F':
        return piece_creer(NOIR, FOU, PROMU);
      }
      {
      case 'T':
        piece_creer(NOIR, TOUR, PROMU);
      }
      {
      case 'A':
        return piece_creer(NOIR, SILVER, PROMU);
      }
    }
  } else {
    switch (caracter_v) {
      // Non Promu Joueur 1
      {
      case 'p':
        return piece_creer(BLANC, PION, NON_PROMU);
      }
      {
      case 'l':
        return piece_creer(BLANC, LANCIER, NON_PROMU);
      }
      {
      case 'n':
        return piece_creer(BLANC, CAVALIER, NON_PROMU);
      }
      {
      case 'b':
        return piece_creer(BLANC, FOU, NON_PROMU);
      }
      {
      case 'r':
        return piece_creer(BLANC, TOUR, NON_PROMU);
      }
      {
      case 's':
        return piece_creer(BLANC, SILVER, NON_PROMU);
      }
      {
      case 'g':
        return piece_creer(BLANC, GOLD, NON_PROMU);
      }
      {
      case 'k':
        return piece_creer(BLANC, ROI, NON_PROMU);
      }
      // Promu Joueur 2
      {
      case 'd':
        return piece_creer(BLANC, PION, PROMU);
      }
      {
      case 'j':
        return piece_creer(BLANC, LANCIER, PROMU);
      }
      {
      case 'c':
        return piece_creer(BLANC, CAVALIER, PROMU);
      }
      {
      case 'f':
        return piece_creer(BLANC, FOU, PROMU);
      }
      {
      case 't':
        return piece_creer(BLANC, TOUR, PROMU);
      }
      {
      case 'a':
        return piece_creer(BLANC, SILVER, PROMU);
      }
    }
  }

  return piece_creer(VIDE_PIECE, VIDE, NON_PROMU);
}

/** Detections de piece
 * Permet d'associer chaque numéro à chaque piece en fonction du type enuméré
 * et de la couleur de piece
 * Parameters:
 *     piece_t - piece_v
 *
 * @return char
 */
char piece_caractere(piece_t piece_v) {
  if (!piece_couleur(piece_v)) {
    switch (piece_v.type) {
      {
      case 1:
        return 'R';
      }
      {
      case 2:
        return 'T';
      }
      {
      case 3:
        return 'F';
      }
      {
      case 4:
        return 'G';
      }
      {
      case 5:
        return 'S';
      }
      {
      case 6:
        return 'C';
      }
      {
      case 7:
        return 'L';
      }
      {
      case 8:
        return 'P';
      }
      {
      case 9:
        return 'D'; // PION PROMU
      }
      {
      case 10:
        return 'J'; // LANCIER PROMU
      }
      {
      case 11:
        return 'C'; // CAVALIER PROMU
      }
      {
      case 12:
        return 'F'; // FOU PROMU
      }
      {
      case 13:
        return 'T'; // TOUR PROMU
      }
      {
      case 14:
        return 'A'; // SILVER PROMU
      }
      {
      case 15:
        return '*';
      }
      {
      default:
        return '.';
      }
    }
  } else {
    switch (piece_v.type) {
      {
      case 1:
        return 'r';
      }
      {
      case 2:
        return 't';
      }
      {
      case 3:
        return 'f';
      }
      {
      case 4:
        return 'g';
      }
      {
      case 5:
        return 's';
      }
      {
      case 6:
        return 'c';
      }
      {
      case 7:
        return 'l';
      }
      {
      case 8:
        return 'p';
      }
      {
      case 9:
        return 'd'; // PION PROMU
      }
      {
      case 10:
        return 'j'; // LANCIER PROMU
      }
      {
      case 11:
        return 'c'; // CAVALIER PROMU
      }
      {
      case 12:
        return 'f'; // FOU PROMU
      }
      {
      case 13:
        return 't'; // TOUR PROMU
      }
      {
      case 14:
        return 'a'; // SILVER PROMU
      }
      {
      case 15:
        return '*';
      }
      {
      default:
        return '.';
      }
    }
  }

  return '.';
}

/** piece displayer
 * piece displayer
 * Permet d'afficher tout simplement la piece sur l'echiquier
 * Complexite : O(1) pour Espace et Temps
 * Parameters:
 * @param    piece_t - piece_v
 * @return NADA
 */
void piece_afficher(piece_t piece_v) { printf("%c", piece_caractere(piece_v)); }