#include "header/piece.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * Création de piece
 * Parameters:
 * @param piece_color_e - piece_color_v
 *        piece_type_e  - piece_type_v
 *
 * @return struct piece_s
 */
piece_t piece_creer(piece_color_e piece_color_v, piece_type_e piece_type_v) {

  piece_t res;

  /* Initialiser */
  res.color = piece_color_v;
  res.type = piece_type_v;

  return res;
}

/**
 * Couleur de piece
 *
 * Parameters:
 * @param    piece_t - piece_v
 * @return int
 */

int piece_couleur(piece_t piece_v) { return piece_v.color; }

/**
 * piece identifier
 *
 * Parameters:
 * @param    char - caracter_v
 * @return struct piece_s
 */
piece_t piece_identifier(char caracter_v) {
  if (caracter_v <= 90 && caracter_v >= 65) {
    switch (caracter_v) {
      {
      case 'R':
        return piece_creer(NOIR, ROI);
      }
      {
      case 'T':
        return piece_creer(NOIR, TOUR);
      }
      {
      case 'F':
        return piece_creer(NOIR, FOU);
      }
      {
      case 'G':
        return piece_creer(NOIR, GOLD);
      }
      {
      case 'S':
        return piece_creer(NOIR, SILVER);
      }
      {
      case 'N':
        return piece_creer(NOIR, CAVALIER);
      }
      {
      case 'L':
        return piece_creer(NOIR, LANCIER);
      }
      {
      case 'P':
        return piece_creer(NOIR, PION);
      }
    }
  } else {
    switch (caracter_v) {
      {
      case 'r':
        return piece_creer(BLANC, ROI);
      }
      {
      case 't':
        return piece_creer(BLANC, TOUR);
      }
      {
      case 'f':
        return piece_creer(BLANC, FOU);
      }
      {
      case 'g':
        return piece_creer(BLANC, GOLD);
      }
      {
      case 's':
        return piece_creer(BLANC, SILVER);
      }
      {
      case 'c':
        return piece_creer(BLANC, CAVALIER);
      }
      {
      case 'l':
        return piece_creer(BLANC, LANCIER);
      }
      {
      case 'p':
        return piece_creer(BLANC, PION);
      }
    }
  }

  return piece_creer(VIDE_PIECE, VIDE);
}

/**
 * piece type detector
 *
 * Parameters:
 *     piece_t - piece_v
 *
 * @return char
 */
char piece_caractere(piece_t piece_v) {
  //======================================================================
  // Main
  //======================================================================
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

/**
 * piece displayer
 *
 * Parameters:
 * @param    piece_t - piece_v
 */
void piece_afficher(piece_t piece_v) { printf("%c", piece_caractere(piece_v)); }
